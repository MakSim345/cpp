
#ifndef MSF_MICROCONTROLLER_I2CDRVIF_HPP
#define MSF_MICROCONTROLLER_I2CDRVIF_HPP
/** 
 */

#include <cstddef>

namespace Msf {
    namespace MicroController {

        /**
         * A general interface for I2C driver
         *
         * The user must always ensure that the driver is not used before the previous operation
         * has successfully finished. The correct way is to use the built-in lock() / unlock() methods.
         * In other words, read() or write() shall NEVER be called without locking the driver first!
         *
         * Note, it is allowed to perform several sequential read() / write() operations within a single
         * lock, but this should be used carefully because all the operations are blocking (they do not
         * return until they finish or time out). Therefore the time spent blocked could become an issue
         * for real-time operation.
        */
        class I2cDrvIf
        {
        public:
            virtual ~I2cDrvIf() = default;

            /**
             * Mutex-lock the driver (it is a shared resource).
             */
            virtual void lock() = 0;

            /**
             * Mutex-unlock the driver.
             */
            virtual void unlock() = 0;

            /**
             * Read from an I2C device in blocking mode.
             *
             * @param[in]   deviceAddressP          I2C device address.
             * @param[in]   internalAddressP        Read address inside the device.
             * @param[in]   internalAddressSizeP    Size of the internal address, in bytes.
             * @param[out]  pDataBufferP            Receiving buffer for the data.
             * @param[in]   dataSizeP               How many bytes to read.
             * @return      true if successful, false if something went wrong.
            */
            virtual bool read(
                unsigned int  deviceAddressP,
                unsigned int  internalAddressP,
                size_t        internalAddressSizeP,
                void* pDataBufferP,
                size_t        dataSizeP) = 0;

            /**
             * Write to an I2C device in blocking mode.
             *
             * @param[in]   deviceAddressP          I2C device address.
             * @param[in]   internalAddressP        Read address inside the device.
             * @param[in]   internalAddressSizeP    Size of the internal address, in bytes.
             * @param[in]   pDataBufferP            Data to write.
             * @param[in]   dataSizeP               How many bytes to write.
             * @return      true if successful, false if something went wrong.
            */
            virtual bool write(
                unsigned int  deviceAddressP,
                unsigned int  internalAddressP,
                size_t        internalAddressSizeP,
                const void* pDataBufferP,
                size_t        dataSizeP) = 0;
        };

    } //namespace MicroController
} //namespace Msf

#endif /* MSF_MICROCONTROLLER_I2CDRVIF_HPP */

