
/**
 *
 */

#include "Iwdg.hpp"

// #include "Cots/STM32L496/Libraries/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
//#include "Msf/Common/Log/DebugApi.hpp"
//#include "Msf/Common/Primitives/Elements.hpp"

#include <cstring> // memset
#include <map>

namespace Msf {
namespace MicroController {
namespace Stm32L4 {

Iwdg* Iwdg::pIwdgS{nullptr};
IWDG_HandleTypeDef* Iwdg::pHandleS{nullptr};

Iwdg& Iwdg::getInstance()
{
    if (!pHandleS)
    {
        pHandleS = new IWDG_HandleTypeDef;
    }

    if (!pIwdgS)
    {
        pIwdgS = new Iwdg();
    }

    return *pIwdgS;
}

bool Iwdg::halIwdgInit(uint32_t reloadP)
{
    pHandleS->Instance = IWDG;
    pHandleS->Init.Prescaler = IWDG_PRESCALER_256;
    pHandleS->Init.Reload = reloadP;
    pHandleS->Init.Window = IWDG_WINDOW_DISABLE;
    return HAL_OK == HAL_IWDG_Init(pHandleS);
}

bool Iwdg::halIwdgRefresh()
{
    return HAL_OK == HAL_IWDG_Refresh(pHandleS);
}

void Iwdg::halDbgMcuFreezeIwdg()
{
    __HAL_DBGMCU_FREEZE_IWDG();
}

void Iwdg::halDbgMcuUnfreezeIwdg()
{
    __HAL_DBGMCU_UNFREEZE_IWDG();
}

} // namespace Stm32L4
} // namespace MicroController
} // namespace Msf