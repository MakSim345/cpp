
/**
 */

#include "OutputPin.hpp"

// #include "Msf/Common/Log/DebugApi.hpp"

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

OutputPin::OutputPin(
    IoPinUtils::IoPort portP,
    uint16_t pinP)
  : pPortM(IoPinUtils::enumIoPortToHalIoPort(portP)),
    halPinM(IoPinUtils::numberedIoPinToHalIoPin(pinP)),
    portNameM(IoPinUtils::enumIoPortToIoPortName(portP)),
    pinNumberM(pinP)
{
    // MSF_ASSERT(IoPinUtils::isPinModeOutput(portP, pinNumberM));
}

OutputPin::~OutputPin()
{
}

void OutputPin::set()
{
    HAL_GPIO_WritePin(pPortM, halPinM, GPIO_PIN_SET);
}

void OutputPin::clear()
{
    HAL_GPIO_WritePin(pPortM, halPinM, GPIO_PIN_RESET);
}

void OutputPin::set(bool bValueP)
{
    const GPIO_PinState state = bValueP ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(pPortM, halPinM, state);
}

void OutputPin::toggle()
{
    // todo:
    // HAL_GPIO_TogglePin(pPortM, halPinM);
}

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf
