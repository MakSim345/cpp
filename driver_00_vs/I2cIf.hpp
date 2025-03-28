
#ifndef MSF_MICROCONTROLLER_STM32L4_I2CIF_HPP
#define MSF_MICROCONTROLLER_STM32L4_I2CIF_HPP
/**
 */

#include <cstdint>

namespace Msf {
    namespace MicroController {
        namespace Stm32L4 {

            /**
             * This interface wraps the STM HAL I2C library. The purpose of the wrapping
             * is to enable mocking in unit tests.
             */
            class I2cIf
            {
            public:
                I2cIf() = default;
                virtual ~I2cIf() = default;

                I2cIf(const I2cIf&) = delete;
                I2cIf& operator=(const I2cIf&) = delete;

                /**
                 * Wrapper for function HAL_I2C_Mem_Read_IT()
                 *
                 * @return true if HAL_I2C_Mem_Read_IT() returns HAL_OK, false otherwise
                 */
                virtual bool halI2cMemReadIt(
                    uint16_t deviceAddressP,
                    uint16_t memoryAddressP,
                    uint16_t memoryAddressSizeP,
                    uint8_t* pDataP,
                    uint16_t dataSizeP) = 0;

                /**
                 * Wrapper for function HAL_I2C_Mem_Write_IT()
                 *
                 * @return true if HAL_I2C_Mem_Write_IT() returns HAL_OK, false otherwise
                 */
                virtual bool halI2cMemWriteIt(
                    uint16_t deviceAddressP,
                    uint16_t memoryAddressP,
                    uint16_t memoryAddressSizeP,
                    const uint8_t* pDataP,
                    uint16_t dataSizeP) = 0;

                /**
                 * Interface for a class which implements I2C callbacks.
                 *
                 * NOTE: All callbacks are called from interrupt handlers.
                 */
                class CallbacksIf
                {
                public:
                    virtual void memRxCpltCallback() = 0;
                    virtual void memTxCpltCallback() = 0;
                    virtual void errorCallback() = 0;
                };

                /** Set I2C callback handler. */
                virtual void setCallbacks(CallbacksIf& rCallbacksIfP) = 0;

                /** Reset I2C callback handler. */
                virtual void resetCallbacks(CallbacksIf& rCallbacksIfP) = 0;
            };

        } // namespace Stm32L4
    } // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_STM32L4_I2CIF_HPP

