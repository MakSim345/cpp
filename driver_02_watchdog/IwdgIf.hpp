
#ifndef MSF_MICROCONTROLLER_STM32L4_IWDGIF
#define MSF_MICROCONTROLLER_STM32L4_IWDGIF
/**
 */

#include <cstdint>

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

/**
 * This interface wraps the STM HAL Independent watchdog (IWDG) library.
 */
class IwdgIf
{
public:
    IwdgIf() = default;
    virtual ~IwdgIf() = default;

    IwdgIf(const IwdgIf&) = delete;
    IwdgIf& operator=(const IwdgIf&) = delete;

    /**
     * Wrapper for function HAL_IWDG_Init()
     *
     * @return true if HAL_IWDG_Init returns() HAL_OK, false otherwise
     */
    virtual bool halIwdgInit(uint32_t reloadP) = 0;

    /**
     * Wrapper for function HAL_IWDG_Refresh()
     *
     * @return true if HAL_IWDG_Refresh() HAL_OK, false otherwise
     */
    virtual bool halIwdgRefresh() = 0;

    /** Wrapper for macro __HAL_DBGMCU_FREEZE_IWDG */
    virtual void halDbgMcuFreezeIwdg() = 0;

    /** Wrapper for macro __HAL_DBGMCU_UNFREEZE_IWDG */
    virtual void halDbgMcuUnfreezeIwdg() = 0;
};

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_STM32L4_IWDGIF
