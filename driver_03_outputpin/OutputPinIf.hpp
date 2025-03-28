
#ifndef MSF_MICROCONTROLLER_OUTPUTPINIF_HPP
#define MSF_MICROCONTROLLER_OUTPUTPINIF_HPP

namespace Msf {
namespace MicroController {

/**
An interface for output pins of the MCU.
Methods should be self-evident even without comments.

@idea: If needed, add a new interface OuputPinConfIf, which could have methods like:
       void setAsOutput(bool bValueP)
       void setPullUpResistor(bool bEnableP)
       etc...
*/
class OutputPinIf
{
public:
    virtual void set() = 0;
    virtual void clear() = 0;
    virtual void set(bool bValueP) = 0;
    virtual void toggle() = 0;
};

} // namespace MicroController
} // namespace Msf

#endif // MSF_MICROCONTROLLER_OUTPUTPINIF_HPP