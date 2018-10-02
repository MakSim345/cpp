/**
  */

/** This module body exists exclusively for the class Fixed
  * Point. Since FixedPoint is a primitive it should not
  * include Global.hpp, because that would create a cyclic
  * header file dependency.
  *
  * Filename:   FixedPoint.cpp
  *
  * Project:    MSF
  *
  * Subsystem:  Primitives
  *
  * Abstract:   This file contains the non-inlined part of implementation of
  *             the FixedPoint number class.
  */

#include "FixedPoint.hpp"

namespace Msf {

const IntS32 FixedPoint::NTAB[] =
{
    FixedPoint::BASE,
    FixedPoint::BASE / 10,
    FixedPoint::BASE / 100,
    FixedPoint::BASE / 1000,
    FixedPoint::BASE / 10000
};

const Msf::FixedPoint FixedPoint::MIN_S = FixedPoint(INTS32_MIN, 4);
const Msf::FixedPoint FixedPoint::MAX_S = FixedPoint(INTS32_MAX, 4);


Msf::FixedPoint FixedPoint::operator *= (const FixedPoint &right)
{
    // All the multiplications and divisions are now done using 64-bit
    // integers. The old fixed point arithmetic, arithmetic using 64-bit
    // intermediate results and floating point arithmetic were compared
    // and the test showed that 64-bit arithmetic was slightly faster than
    // the old version and a lot faster than floating point arithmetic
    // (floating point arithmetic itself is fast but converting between
    // floating point and integer is slow).
    // Also, the code that uses compiler's 64-bit variables is much more
    // readable than implementing something about 42-bit myself.

    IntS64 p1 = valueM;
    IntS64 p2 = right.valueM;
    // p1 == value1 * BASE, p2 == value2 * BASE,
    // thus p1 * p2 == value1 * value2 * BASE^2 -- one BASE too much
    valueM = static_cast<IntS32>(p1 * p2 / BASE);

    return *this;
}

Msf::FixedPoint FixedPoint::operator /= (const FixedPoint &right)
{
    IntS64 p1 = valueM;
    IntS64 p2 = right.valueM;
    //MSF_ASSERT(p2 != 0);

    // p1 / p2 == value1 / value2 - one BASE too few
    p1 *= BASE;
    valueM = static_cast<IntS32>(p1 / p2);

    return *this;
}

Msf::FixedPoint FixedPoint::mulDiv (const FixedPoint &multiplier, const FixedPoint &divisor)
{
    IntS64 p1 = valueM;
    IntS64 pm = multiplier.valueM;
    IntS64 pd = divisor.valueM;
    //MSF_ASSERT(pd != 0);

    // Base numbers in pm and pd cancel out each other
    valueM = static_cast<IntS32>(p1 * pm / pd);

    return *this;
}

Msf::FixedPoint FixedPoint::getRounded (unsigned int precisionP) const
{
    // MSF_ASSERT(precisionP <= NR_OF_DECIMALS_S);

    FixedPoint rval;
    int factor = NTAB[precisionP];
    rval.valueM = valueM;
    if (valueM >= 0)
    {
        // Get the rounding right. The result of integer division is always
        // rounded down and this shifts the first operand so that it is rounded
        // to the nearest integer to original operand.
        rval.valueM = ((rval.valueM + (factor / 2)) / factor) * factor;
    }
    else
    {
        rval.valueM = ((rval.valueM - (factor / 2)) / factor) * factor;
    }

    return rval;
}

Msf::FixedPoint FixedPoint::getRoundedUp (unsigned int precisionP) const
{
    //MSF_ASSERT(precisionP <= NR_OF_DECIMALS_S);

    FixedPoint rval;
    int factor = NTAB[precisionP];
    rval.valueM = valueM;
    if (valueM >= 0)
    {
        // Get the rounding right. This makes sure the division is always
        // rounded up.
        rval.valueM = ((rval.valueM + (factor - 1)) / factor) * factor;
    }
    else
    {
        rval.valueM = (rval.valueM / factor) * factor;
    }

    return rval;
}

Msf::FixedPoint FixedPoint::getRoundedDown (unsigned int precisionP) const
{
    // MSF_ASSERT(precisionP <= NR_OF_DECIMALS_S);

    FixedPoint rval;
    int factor = NTAB[precisionP];
    rval.valueM = valueM;
    if (valueM >= 0)
    {
        // Integer division simply truncates away the last numbers
        rval.valueM = (rval.valueM / factor) * factor;
    }
    else
    {
        rval.valueM = ((rval.valueM - (factor - 1)) / factor) * factor;
    }

    return rval;
}

// Additional Declarations

} // namespace Msf
