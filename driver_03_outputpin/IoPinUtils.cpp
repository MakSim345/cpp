
#include "IoPinUtils.hpp"
// #include "Msf/Hardware/MicroController/Stm32L4/IoPinUtils.hpp"

// #include "Msf/Common/Log/DebugApi.hpp"

#include <cstdint>

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

namespace {

    GPIO_TypeDef* GPIOA; // IoPin::IoPort::IO_PORT_A
    GPIO_TypeDef* GPIOB; // IoPin::IoPort::IO_PORT_B
    GPIO_TypeDef* GPIOC; // IoPin::IoPort::IO_PORT_C
    GPIO_TypeDef* GPIOD; // IoPin::IoPort::IO_PORT_D
    GPIO_TypeDef* GPIOE; // IoPin::IoPort::IO_PORT_E
    GPIO_TypeDef* GPIOF; // IoPin::IoPort::IO_PORT_F
    GPIO_TypeDef* GPIOG; // IoPin::IoPort::IO_PORT_G
    GPIO_TypeDef* GPIOH; // IoPin::IoPort::IO_PORT_H
    GPIO_TypeDef* GPIOI; // IoPin::IoPort::IO_PORT_I

GPIO_TypeDef* const DEFINED_IO_PORT[] = {
    GPIOA, // IoPin::IoPort::IO_PORT_A
    GPIOB, // IoPin::IoPort::IO_PORT_B
    GPIOC, // IoPin::IoPort::IO_PORT_C
    GPIOD, // IoPin::IoPort::IO_PORT_D
    GPIOE, // IoPin::IoPort::IO_PORT_E
    GPIOF, // IoPin::IoPort::IO_PORT_F
    GPIOG, // IoPin::IoPort::IO_PORT_G
    GPIOH, // IoPin::IoPort::IO_PORT_H
    GPIOI  // IoPin::IoPort::IO_PORT_I
};

const uint16_t DEFINED_IO_PIN[] = {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15
};

// The pin mode bit combinations as defined in the reference manual:
enum PinMode
{
    PIN_MODE_INPUT              = 0b00,
    PIN_MODE_OUTPUT             = 0b01,
    PIN_MODE_ALTERNATE_FUNCTION = 0b10,
    PIN_MODE_ANALOG             = 0b11
};

} // unnamed namespace

bool IoPinUtils::convertToEnumIoPort(char inputIoPortP, IoPort& rIoPortP)
{
    switch (inputIoPortP)
    {
    case 'A':
        rIoPortP = IoPort::IO_PORT_A;
        break;
    case 'B':
        rIoPortP = IoPort::IO_PORT_B;
        break;
    case 'C':
        rIoPortP = IoPort::IO_PORT_C;
        break;
    case 'D':
        rIoPortP = IoPort::IO_PORT_D;
        break;
    case 'E':
        rIoPortP = IoPort::IO_PORT_E;
        break;
    case 'F':
        rIoPortP = IoPort::IO_PORT_F;
        break;
    case 'G':
        rIoPortP = IoPort::IO_PORT_G;
        break;
    case 'H':
        rIoPortP = IoPort::IO_PORT_H;
        break;
    case 'I':
        rIoPortP = IoPort::IO_PORT_I;
        break;
    default:
        return false;
    };
    return true;
}

char IoPinUtils::enumIoPortToIoPortName(IoPort portP)
{
    //MSF_ASSERT(portP <= IoPort::IO_PORT_I);
    return 'A' + static_cast<int>(portP);
}

GPIO_TypeDef* IoPinUtils::enumIoPortToHalIoPort(IoPort portP)
{
    //MSF_ASSERT(portP <= IoPort::IO_PORT_I);
    return DEFINED_IO_PORT[static_cast<unsigned int>(portP)];
}

uint16_t IoPinUtils::numberedIoPinToHalIoPin(uint16_t pinP)
{
    //MSF_ASSERT(pinP <= IoPinUtils::MAX_IO_PIN_NUMBER);
    return DEFINED_IO_PIN[pinP];
}

bool IoPinUtils::isPinModeOutput(IoPort portP, uint16_t pinP)
{
    return getPinMode(portP, pinP) == PinMode::PIN_MODE_OUTPUT;
}

bool IoPinUtils::isPinModeInput(IoPort portP, uint16_t pinP)
{
    return getPinMode(portP, pinP) == PinMode::PIN_MODE_INPUT;
}

uint32_t IoPinUtils::getPinMode(IoPort portP, uint16_t pinP)
{
    GPIO_TypeDef* const pPort = enumIoPortToHalIoPort(portP);
    return (pPort->MODER >> (pinP * 2)) & 0b11;
}

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf
