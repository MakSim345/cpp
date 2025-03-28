
#ifndef MSF_MICROCONTROLLER_STM32L4_IOPINUTILS_HPP
#define MSF_MICROCONTROLLER_STM32L4_IOPINUTILS_HPP

#include "stm32xx.h"
// #include <Cots/STM32L496/Libraries/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h>

#include <cstdint>

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

/** This class supports some common methods and definitions of I/O pins */
class IoPinUtils
{
public:
    /**
     * The maximum I/O pin number.
     *
     * @note The range of I/O pin is [0..15].
     */
    static constexpr unsigned int MAX_IO_PIN_NUMBER = 15;

    /** Represent the IO Port name */
    enum class IoPort
    {
        IO_PORT_A,
        IO_PORT_B,
        IO_PORT_C,
        IO_PORT_D,
        IO_PORT_E,
        IO_PORT_F,
        IO_PORT_G,
        IO_PORT_H,
        IO_PORT_I
    };

    /** Convert the I/O Port character to enum I/O Port */
    static bool convertToEnumIoPort(char inputIoPortP, IoPort& rIoPortP);

    /** Convert enum I/O Port to I/O Port name */
    static char enumIoPortToIoPortName(IoPort portP);

    /** Convert enum I/O Port to Hal I/O Port name */
    static GPIO_TypeDef* enumIoPortToHalIoPort(IoPort portP);

    /** Convert I/O Pin Number to Hal I/O Pin number */
    static uint16_t numberedIoPinToHalIoPin(uint16_t pinP);

    /** Check if it is an input pin */
    static bool isPinModeInput(IoPort portP, uint16_t pinP);

    /** Check if it is an output pin */
    static bool isPinModeOutput(IoPort portP, uint16_t pinP);

private:
    static uint32_t getPinMode(IoPort portP, uint16_t pinP);
};

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_STM32L4_IOPINUTILS_HPP

