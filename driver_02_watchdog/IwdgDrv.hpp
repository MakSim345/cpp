
#ifndef MSF_MICROCONTROLLER_STM32L4_IWDGDRV_HPP
#define MSF_MICROCONTROLLER_STM32L4_IWDGDRV_HPP
/**
 * @copyright Copyright (c) 2023 General Electric Company. All rights reserved.
 */

#include "Msf/Common/SystemMonitor/WatchdogDrvIf.hpp"
#include "Msf/Hardware/MicroController/Stm32L4/Wrappers/IwdgIf.hpp"

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

/**
 * This is an implementation for the STM32L4 independent watchdog timer driver.
 */
class IwdgDrv : public Msf::SystemMonitor::WatchdogDrvIf
{
public:
    IwdgDrv(IwdgIf& rIwdgIfP);
    ~IwdgDrv() = default;

    IwdgDrv(const IwdgDrv&) = delete;
    IwdgDrv& operator=(const IwdgDrv&) = delete;

    /**
     * Initialize and enable the independent watchdog timer
     *
     * @param timeMsP: refresh window time
     * @return true if the independent watchdog is initialized successfully, otherwise false.
     */
    bool init(uint32_t timeMsP);

    /** @see Msf::SystemMonitor::WatchdogDrvIf::refresh */
    bool refresh() override;

    /** Freeze the IWDG counter when the device enters Debug mode (core halted) */
    void enableDebugMode();

    /** Make the IWDG to work normally when the device enters Debug mode (core halted)*/
    void disableDebugMode();

private:
    /** Wrapper for STM HAL IWDG library. */
    IwdgIf& rIwdgIfM;
};

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_STM32L4_IWDGDRV_HPP