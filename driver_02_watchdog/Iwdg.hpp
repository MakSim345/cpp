
#ifndef MSF_MICROCONTROLLER_STM32L4_IWDG_HPP
#define MSF_MICROCONTROLLER_STM32L4_IWDG_HPP
/**
 *
 */

#include "gen.h"
// #include "Msf/Hardware/MicroController/Stm32L4/Wrappers/IwdgIf.hpp"

#include "IwdgIf.hpp"
// #include "Cots/STM32L496/Libraries/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_iwdg.h"

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

/**
 * This class implements IwdgIf by calling the actual library functions.
 */

class Iwdg : public IwdgIf
{
public:
    Iwdg(const Iwdg&) = delete;
    Iwdg& operator=(const Iwdg&) = delete;

    /** @see IwdgIf::halIwdgInit */
    bool halIwdgInit(uint32_t reloadP) override;

    /** @see IwdgIf::halIwdgRefresh */
    bool halIwdgRefresh() override;

    /** @see IwdgIf::halDbgMcuFreezeIwdg */
    void halDbgMcuFreezeIwdg() override;

    /** @see IwdgIf::halDbgMcuUnfreezeIwdg */
    void halDbgMcuUnfreezeIwdg() override;

    /**
     * Create the Iwdg singleton instance and return it.
     *
     * @return Iwdg singleton instance.
     */
    static Iwdg& getInstance();

private:
    /** Constructor */
    Iwdg() = default;
    static IWDG_HandleTypeDef* pHandleS;
    static Iwdg* pIwdgS;
};
};

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_STM32L4_IWDG_HPP
