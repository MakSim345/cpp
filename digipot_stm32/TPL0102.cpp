
/**
 * @copyright Copyright (c) 2020 General Electric Company. All rights reserved.
 */

#include "Msf/Hardware/Sensors/TPL0102.hpp"

#include "Msf/Common/Log/DebugApi.hpp"
#include "Msf/Common/Os/FreeRtos/FreeRtosIf.hpp"
#include "Msf/Event/KppEventPool.hpp"

#include "Cots/STM32L496/Libraries/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_i2c.h"

#include <algorithm>

#if TARGET_DEVICE==TARGET_DEVICE_SENSOR
extern I2C_HandleTypeDef hi2c3;
#elif TARGET_DEVICE==TARGET_DEVICE_DISCOVERY_KIT
extern I2C_HandleTypeDef hi2c1;
#endif

namespace Msf {
namespace Sensors {
namespace {

#if TARGET_DEVICE==TARGET_DEVICE_SENSOR
I2C_HandleTypeDef* const pI2cS = &hi2c3;
#elif TARGET_DEVICE==TARGET_DEVICE_DISCOVERY_KIT
I2C_HandleTypeDef* const pI2cS = &hi2c1;
#endif

constexpr uint16_t ACCELEROMETER_DATASHEET_ADDRESS_BASE = 0x18;

// Least significant bit depends on how SA0 pin is wired.
constexpr uint16_t ACCELEROMETER_DATASHEET_ADDRESS_LSB = 0x1;

constexpr uint16_t ACCELEROMETER_DATASHEET_ADDRESS =
    ACCELEROMETER_DATASHEET_ADDRESS_BASE | ACCELEROMETER_DATASHEET_ADDRESS_LSB;

// Shift by one because HAL library expects the address to be in the higher bits.
constexpr uint16_t ACCELEROMETER_HAL_ADDRESS = ACCELEROMETER_DATASHEET_ADDRESS << 1;

Lis2Dw12* pAccelerometerInstanceS = nullptr;

static uint8_t aReceiveBufferS[Lis2Dw12::RECEIVE_BUFFER_SIZE];

} // Unnamed namespace

Lis2Dw12::Lis2Dw12(Os::FunctorThread& rFunctorHandlerThreadP, KppEventQueue& rEventQueueP)
  : KppStateMachine{rEventQueueP, static_cast<KppEvtHandler>(&Lis2Dw12::eventHandlerTopState), "LIS2DW12"},
    whoAmIStateM{
        &topStateM,
        static_cast<KppEvtHandler>(&Lis2Dw12::eventHandlerWhoAmIState)},
    idleStateM{
        &topStateM,
        static_cast<KppEvtHandler>(&Lis2Dw12::eventHandlerIdleState)},
    valueObtainStateM{
        &topStateM,
        static_cast<KppEvtHandler>(&Lis2Dw12::eventHandlerValueObtainState)},
    timerHandlerFunctorM{*this, &Lis2Dw12::startValueObtain},
    measurementTimerM{"LIS2DW12", rFunctorHandlerThreadP, timerHandlerFunctorM},
    aWhoAmISubAddressM{ 0x0F },
    aAccelerationValuesSubAddressM{ 0x28 }
{
    pAccelerometerInstanceS = this;
}

Lis2Dw12::~Lis2Dw12() = default;

RetVal Lis2Dw12::initialize(uint32_t valueObtainPeriodMsP)
{
    return measurementTimerM.initialize(valueObtainPeriodMsP);
}

void Lis2Dw12::startValueObtain()
{
    postEvent(KPP_NEW_BASE_EVT_REF(EVT_ACCELEROMETER_START_SUB_ADDRESS_WRITE ));
}

const KppEvent* Lis2Dw12::eventHandlerTopState(const KppEvent& rEventP)
{
    switch (rEventP.id())
    {
    case EVT_START:
        startTransition(whoAmIStateM);
        return nullptr;

    default:
        // Event ignored
        break;
    }

    return &rEventP;
}

const KppEvent* Lis2Dw12::eventHandlerWhoAmIState(const KppEvent& rEventP)
{
    switch (rEventP.id())
    {
    case EVT_ENTRY:
        return nullptr;

    case EVT_START:
        if (startSubAddressWrite(aWhoAmISubAddressM) != HAL_OK)
        {
            MSF_LOG_ERROR("Accelerometer: WHO_AM_I sub-address write failed");
            KPP_STATE_TRANSITION(idleStateM);
        }
        return nullptr;

    case EVT_EXIT:
        return nullptr;

    case EVT_ACCELEROMETER_TX_COMPLETE:
        if (HAL_I2C_Master_Seq_Receive_IT(
            pI2cS, ACCELEROMETER_HAL_ADDRESS, aReceiveBufferS, sizeof(aReceiveBufferS), I2C_LAST_FRAME) !=
                HAL_OK)
        {
            MSF_LOG_ERROR("Accelerometer: Values read failed");
            KPP_STATE_TRANSITION(idleStateM);
        }
        return nullptr;

    case EVT_ACCELEROMETER_RX_COMPLETE:
        {
            constexpr uint8_t EXPECTED_WHO_AM_I_VALUE = 0x44;

            const AccelerometerResponseEvent& rEvent = static_cast<const AccelerometerResponseEvent&>(rEventP);

            uint8_t response = rEvent.aReceivedBytesM[0];

            if (response == EXPECTED_WHO_AM_I_VALUE)
            {
                startMeasurements();
                measurementTimerM.enable();
                KPP_STATE_TRANSITION(idleStateM);
            }
            else
            {
                MSF_LOG_ERROR("Unexpected WHO_AM_I value from accelerometer");
            }
        }
        return nullptr;

    default:
        break;

    }

    return &rEventP;
}

const KppEvent* Lis2Dw12::eventHandlerIdleState(const KppEvent& rEventP)
{
    switch (rEventP.id())
    {
    case EVT_ENTRY:
    case EVT_START:
    case EVT_EXIT:
        return nullptr;

    case EVT_ACCELEROMETER_START_SUB_ADDRESS_WRITE:
        KPP_STATE_TRANSITION(valueObtainStateM);
        return nullptr;

    default:
        break;
    }

    return &rEventP;
}

const KppEvent* Lis2Dw12::eventHandlerValueObtainState(const KppEvent& rEventP)
{
    switch (rEventP.id())
    {
    case EVT_ENTRY:
        return nullptr;

    case EVT_START:
        if (startSubAddressWrite(aAccelerationValuesSubAddressM) != HAL_OK)
        {
            MSF_LOG_ERROR("Accelerometer: Output values sub-address write failed");
            KPP_STATE_TRANSITION(idleStateM);
        }
        break;

    case EVT_EXIT:
        return nullptr;

    case EVT_ACCELEROMETER_TX_COMPLETE:
        if (HAL_I2C_Master_Seq_Receive_IT(
            pI2cS, ACCELEROMETER_HAL_ADDRESS, aReceiveBufferS, sizeof(aReceiveBufferS), I2C_LAST_FRAME) !=
                HAL_OK)
        {
            MSF_LOG_ERROR("Accelerometer: Values read failed");
            KPP_STATE_TRANSITION(idleStateM);
        }
        return nullptr;

    case EVT_ACCELEROMETER_RX_COMPLETE:
        {
            const AccelerometerResponseEvent& rEvent = static_cast<const AccelerometerResponseEvent&>(rEventP);

            // @todo Pass values for actual processing.
            logReceivedValues(rEvent.aReceivedBytesM);
        }
        KPP_STATE_TRANSITION(idleStateM);
        return nullptr;

    default:
        break;
    }

    return &rEventP;
}

HAL_StatusTypeDef Lis2Dw12::startSubAddressWrite(uint8_t* pSubAddressP)
{
    // According to the accelerometer documentation, values are read by
    // writing the sub-address, using a repeated start condition, and then
    // doing I2C read.
    //
    // Repeated start condition is possible by using a "Seq" variant of the
    // transmit functions.
    return HAL_I2C_Master_Seq_Transmit_IT(
        pI2cS, ACCELEROMETER_HAL_ADDRESS, pSubAddressP, SUB_ADDRESS_LENGTH, I2C_FIRST_FRAME);
}

void Lis2Dw12::startMeasurements()
{
    constexpr uint8_t CTRL1_SUB_ADDRESS = 0x20;

    // Four highest bits determine power mode and data rate:
    // 0000 Power-down
    // 0001 12.5/1.6 Hz
    // 0010 12.5 Hz
    // 0011 25 Hz
    // 0100 50 Hz
    // 0101 100 Hz
    // 0110 200 Hz
    // 0111 400/200 Hz
    // 1000 800/200 Hz
    // 1001 1600/200 Hz
    constexpr uint8_t CTRL1_VALUE = 0x10;

    uint8_t data[] = { CTRL1_SUB_ADDRESS, CTRL1_VALUE };

    if (HAL_I2C_Master_Transmit(pI2cS, ACCELEROMETER_HAL_ADDRESS, data, sizeof(data), HAL_MAX_DELAY) != HAL_OK)
    {
        MSF_LOG_ERROR("Accelerometer: Setting data rate failed.");
    }
}

void Lis2Dw12::logReceivedValues(const uint8_t* pAccelerationValuesP)
{
    const int x = combineValueBytes(pAccelerationValuesP, X_HIGH_BYTE, X_LOW_BYTE);
    const int y = combineValueBytes(pAccelerationValuesP, Y_HIGH_BYTE, Y_LOW_BYTE);
    const int z = combineValueBytes(pAccelerationValuesP, Z_HIGH_BYTE, Z_LOW_BYTE);

    MSF_LOG_INFO("Accelerometer values: x = %d, y = %d, z = %d", x, y, z);
}

int Lis2Dw12::combineValueBytes(const uint8_t* pAccelerationValuesP, size_t highByteOffsetP, size_t lowByteOffsetP)
{
    constexpr unsigned int BITS_PER_BYTE = 8;

    const unsigned int highByte = pAccelerationValuesP[highByteOffsetP];
    const unsigned int lowByte = pAccelerationValuesP[lowByteOffsetP];

    const unsigned int highByteValueBits = highByte & 0x7F;
    const bool isSignBitSet = highByte & 0x80;

    const unsigned int valueBits = (highByteValueBits << BITS_PER_BYTE) | lowByte;

    if (isSignBitSet)
    {
        unsigned int value = valueBits;

        value = value ^ 0x7FFF;  // Flip bits.
        value += 1;

        // Using 32-bit type here ensures that special case value == 0x8000 is
        // handled correctly, even if 'int' would be a 16-bit type.
        return -static_cast<int32_t>(value);
    }

    return valueBits;
}

} // namespace Sensors
} // namespace Msf

/*
 * This function uses link-time override for function of the same name from HAL library.
 * The override enables us to handle transmit complete event.
 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef*)
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;

    Msf::Sensors::pAccelerometerInstanceS->postEventFromIsr(
        KPP_NEW_BASE_EVT_REF(Msf::Sensors::Lis2Dw12::EVT_ACCELEROMETER_TX_COMPLETE),
        higherPriorityTaskWoken);

    // Request context switch as per postEventFromIsr() documentation.
    Msf::Os::FreeRtosIf::instance().portYieldFromIsr(higherPriorityTaskWoken);
}

/*
 * This function uses link-time override for function of the same name from HAL library.
 * The override enables us to handle receive complete event.
 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef*)
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;

    Msf::Sensors::Lis2Dw12::AccelerometerResponseEvent& rEvent =
        KPP_NEW_EVT_REF(
            Msf::Sensors::Lis2Dw12::AccelerometerResponseEvent,
            Msf::Sensors::Lis2Dw12::EVT_ACCELEROMETER_RX_COMPLETE);

    std::copy(
        Msf::Sensors::aReceiveBufferS,
        Msf::Sensors::aReceiveBufferS + Msf::Sensors::Lis2Dw12::RECEIVE_BUFFER_SIZE,
        rEvent.aReceivedBytesM);

    Msf::Sensors::pAccelerometerInstanceS->postEventFromIsr(rEvent, higherPriorityTaskWoken);

    // Request context switch as per postEventFromIsr() documentation.
    Msf::Os::FreeRtosIf::instance().portYieldFromIsr(higherPriorityTaskWoken);
}
