
#include "gen.h"
#include "utils.hpp"
#include "IoPinUtils.hpp"
#include "OutputPin.hpp"
/*
*/

using namespace Msf::MicroController::Stm32L4;

void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    std::cout << "HAL_GPIO_WritePin called\n";
    std::cout << "GPIO_Pin " << GPIO_Pin <<  "\n";
    std::cout << "PinState " << PinState <<  "\n";
}

int main()
{
    constexpr unsigned int GREEN_LED_PIN = 7;
    constexpr unsigned int YELLOW_LED_PIN = 9;

    for (auto i = 0; i < 10; i++)
    {
        std::cout << "GetRandom: " << GetRandom(9999) << endl;
    }

    // testPersonMobile();

    static OutputPin yellowLedPinS(IoPinUtils::IoPort::IO_PORT_C, YELLOW_LED_PIN);
    yellowLedPinS.set();

    // static InverseOutputPin yellowLedS(yellowLedPinS);

    system("PAUSE");
    return 0;
}
