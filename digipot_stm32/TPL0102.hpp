
#ifndef MSF_SENSORS_TPL0102_HPP
#define MSF_SENSORS_TPL0102_HPP
/**
 * @copyright Copyright (c) 2020 General Electric Company. All rights reserved.
 */

#include "Msf/Common/Os/Functors/MemberFunctor0.hpp"
#include "Msf/Common/Os/Functors/PluggableTimer.hpp"
#include "Msf/Event/KppEvent.hpp"
#include "Msf/Event/KppEventQueue.hpp"
#include "Msf/Event/KppStateMachine.hpp"

namespace Msf {
namespace Sensors {

/**
 * Low-level driver for accelerometer LIS2DW12. Produces X, Y and Z axis linear
 * acceleration readings.
 *
 * @todo: The driver does not currently support tap, double tap and free fall
 * detection, the temperature measurement, nor the self-test, provided by the
 * IC.
 */
class Lis2Dw12 : public KppStateMachine
{
public:
    enum EventId
    {
        EVT_ACCELEROMETER_START_SUB_ADDRESS_WRITE,
        EVT_ACCELEROMETER_TX_COMPLETE,
        EVT_ACCELEROMETER_RX_COMPLETE
    };

    enum AccelerationValueSubAddressOffset
    {
        X_LOW_BYTE,
        X_HIGH_BYTE,
        Y_LOW_BYTE,
        Y_HIGH_BYTE,
        Z_LOW_BYTE,
        Z_HIGH_BYTE,
        ACCELERATION_VALUES_DATA_LENGTH
    };

    /**
     * Buffer size is intended to be large enough so that it can hold all the
     * needed response messages we are interested in. The largest buffer is
     * needed for the acceleration values, so set the buffer size so that
     * acceleration values will fit.
     */
    static constexpr size_t RECEIVE_BUFFER_SIZE = ACCELERATION_VALUES_DATA_LENGTH;

    /** response from accelerometer */
    class AccelerometerResponseEvent : public KppEvent
    {
    public:
        AccelerometerResponseEvent(short evtIdP, KppEventHandlerAbs* pEventHandlerP)
          : KppEvent(evtIdP, pEventHandlerP)
        {
        }

        ~AccelerometerResponseEvent() override = default;

        AccelerometerResponseEvent(const AccelerometerResponseEvent&) = delete;
        AccelerometerResponseEvent& operator=(const AccelerometerResponseEvent&) = delete;

        uint8_t aReceivedBytesM[RECEIVE_BUFFER_SIZE];
    };

    Lis2Dw12(Os::FunctorThread& rFunctorHandlerThreadP, KppEventQueue& rEventQueueP);
    ~Lis2Dw12() override;

    Lis2Dw12(const Lis2Dw12&) = delete;
    Lis2Dw12& operator=(const Lis2Dw12&) = delete;

    /**
     * initialization
     *
     * @param valueObtainPeriodMsP Indicates how often acceleration values are to be obtained.
     * Unit is milliseconds.
     *
     * @return status of initialization
     */
    RetVal initialize(uint32_t valueObtainPeriodMsP);

private:
    static constexpr size_t SUB_ADDRESS_LENGTH = 1;

    void startValueObtain();

    const KppEvent* eventHandlerTopState(const KppEvent& rEventP);
    const KppEvent* eventHandlerWhoAmIState(const KppEvent& rEventP);
    const KppEvent* eventHandlerIdleState(const KppEvent& rEventP);
    const KppEvent* eventHandlerValueObtainState(const KppEvent& rEventP);

    HAL_StatusTypeDef startSubAddressWrite(uint8_t* pSubAddressP);

    /**
     * Sends an I2C command to accelerometer to start measuring.
     *
     * This method returns after transmit of the command has finished.
     */
    void startMeasurements();

    static void logReceivedValues(const uint8_t* pAccelerationValuesP);

    /** Interprets value bytes as 16-bit two's complement. */
    static int combineValueBytes(const uint8_t* pAccelerationValuesP, size_t highByteOffsetP, size_t lowByteOffsetP);

    KppState whoAmIStateM;
    KppState idleStateM;
    KppState valueObtainStateM;

    Os::MemberFunctor0<Lis2Dw12, void> timerHandlerFunctorM;
    Os::PluggableTimer measurementTimerM;

    uint8_t aWhoAmISubAddressM[SUB_ADDRESS_LENGTH];
    uint8_t aAccelerationValuesSubAddressM[SUB_ADDRESS_LENGTH];  // Accelerometer output values start from this sub-address.
};

} // namespace Sensors
} // namespace Msf

#endif // MSF_SENSORS_TPL0102_HPP
