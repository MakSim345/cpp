
#ifndef MSF_MICROCONTROLLER_STM32L4_OUTPUTPIN_HPP
#define MSF_MICROCONTROLLER_STM32L4_OUTPUTPIN_HPP

/**
 * Copyright (c) 2019-2022 General Electric Company. All rights reserved.
 */
#include "stm32xx.h"

#include "OutputPinIf.hpp"
// #include "Msf/Hardware/MicroController/OutputPinIf.hpp"
 
#include "IoPinUtils.hpp"
// #include "Msf/Hardware/MicroController/Stm32L4/IoPinUtils.hpp"

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

/**
 * STM32L4 implementation for output pins on the micro controller.
 * Methods should be self-evident even without comments.
 */
class OutputPin : public OutputPinIf
{
public:
    /**
     * Constructs the output pin object but does not perform the HAL GPIO initialization.
     * Can be used for already initialized output pins
     */
    OutputPin(IoPinUtils::IoPort portP, uint16_t pinP);
    virtual ~OutputPin();
    void set() override;
    void clear() override;
    void set(bool bValueP) override;
    void toggle() override;

private:
    GPIO_TypeDef* const pPortM;
    const uint16_t halPinM;
    const char portNameM;
    const uint16_t pinNumberM;
};

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_STM32L4_OUTPUTPIN_HPP

