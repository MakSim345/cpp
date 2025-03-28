
#ifndef MSF_SYSTEMMONITOR_WATCHDOGDRVIF_HPP
#define MSF_SYSTEMMONITOR_WATCHDOGDRVIF_HPP
/**
 * Copyright (c) 2023 General Electric Company. All rights reserved.
 */

namespace Msf {
namespace SystemMonitor {

/**
 * A general interface for a watchdog driver.
 */
class WatchdogDrvIf
{
public:
    WatchdogDrvIf() = default;
    virtual ~WatchdogDrvIf() = default;

    WatchdogDrvIf(const WatchdogDrvIf&) = delete;
    WatchdogDrvIf& operator=(const WatchdogDrvIf&) = delete;

    /**
     * Refresh the watchdog timer so it doesn't trigger a reset.
     *
     * @return true if the watchdog is refreshed successfully, otherwise false.
     */
    virtual bool refresh() = 0;
};

} // namespace SystemMonitor
} // namespace Msf

#endif // MSF_SYSTEMMONITOR_WATCHDOGDRVIF_HPP