#ifndef MSF_FIXEDPOINT_HPP
#define MSF_FIXEDPOINT_HPP 1
/** This module specification exists exclusively for the
 * class FixedPoint. Since FixedPoint is a primitive it
 * should not include Global.hpp, because that would create
 * a cyclic header file dependency.

 * This file contains the declaration and the inlined part of
 * the implementation of the FixedPoint number class.
 */

//#include "Msf/Common/Primitives/MsfTypes.hpp"
//#include "Msf/Common/Log/DebugAPI.hpp"

#include "gen.h"

namespace Msf {

/**
 * This class represents a fixed point number with four
 * decimals in the fraction part. It supports all the
 * operations you would expect from a numerical variable,
 * i.e. assignment, addition, subtraction, multiplication
 * and division and their assignment forms and equality,
 * inequality and comparison operations.
 *
 * Overflowing is not supported.
 *
 * The range is from ( -2^31 / 10^4 )
 * to ( ( 2^31 - 1 ) / 10^4 )
 *
 * Values not inside the given rage are truncated.
 */
class FixedPoint
{

public:
    inline FixedPoint();

    /**
     * @brief Constructs a FixedPoint with the given value.
     *
     * @param valueP -- The value of the FixedPoint. Since the value
     * is a double, it can have more precision than a Fixed
     * Point can represent. In such a case the given value is
     * rounded, not truncated. Note, that if the first insignificant
     * decimal is 5 (e.g., 0.12345), it may be rounded either up or down
     * (e.g., => 0.1234 or 0.1235).
     *
     * @par Multi-thread safe:
     * Yes
     */
    inline explicit FixedPoint(double valueP);

    /**
     * @brief Constructs a FixedPoint with the given value.
     *
     * @param valueP -- The value of the FixedPoint as a scaled integer.
     * It can only be scaled in powers of ten.
     * @param precisionP -- The number of decimals in valueP.
     *
     * @par Examples:
     * These are valid, but it's not recommended to construct
     * FixedPoints like this:
     *   FixedPoint(60, 0) constructs a FixedPoint with the
     * same value as FixedPoint(60.0).
     *   FixedPoint(6000, 2) constructs a FixedPoint with the
     * same value as FixedPoint(60.0).
     *   FixedPoint(6000, 1) constructs a FixedPoint with the
     * same value as FixedPoint(600.0).
     *
     * The intended use for this constructor:
     * You have some int x and need to construct a FixedPoint from it.
     *   So if x==6000, FixedPoint(x, 2) constructs a FixedPoint with the same
     *   value as FixedPoint(60.0).
     *
     * @par Multi-thread safe:
     * Yes
     */
    inline FixedPoint(int valueP, unsigned int precisionP);

    /**
     * @brief Constructs a FixedPoint with the given value.
     *
     * @param valueP -- The value of the FixedPoint.
     *
     * @par Multi-thread safe:
     * Yes
     *
     * @par Constraints:
     * valueP must be in range (-214748 to 214748)
     */
    inline FixedPoint(int valueP);

    /**
     * @brief Load a FixedPoint with the given value.
     *
     * @param valueP -- The new value for the FixedPoint. Since the value is
     * a double, it can have more precision than a FixedPoint can represent.
     * In such a case the given value is rounded, not truncated.
     *
     * @par Multi-thread safe:
     * Yes
     */
    inline void load(double valueP);

    /**
     * @brief Load a FixedPoint with the given value
     *
     * @param valueP -- The new value for the FixedPoint as a scaled integer.
     * It can only be scaled in powers of ten.
     * @param precisionP -- The number of decimals in valueP.
     * For examples, see constructor with similar argument list.
     *
     * @par Multi-thread safe:
     * Yes
     */
    inline void load(int valueP, unsigned int precisionP);

    /**
     * @brief Load a FixedPoint with the given value
     *
     * @param  valueP -- the new value for the FixedPoint.
     *
     * @par Multi-thread safe:
     * Yes
     */
    inline void load(int valueP);

    inline bool operator==(const FixedPoint& right) const;

    inline bool operator!=(const FixedPoint& right) const;

    inline bool operator<(const FixedPoint& right) const;

    inline bool operator>(const FixedPoint& right) const;

    inline bool operator<=(const FixedPoint& right) const;

    inline bool operator>=(const FixedPoint& right) const;

    /**
     * @brief Sum and assignment operator
     *
     * @param FixedPoint right: reference to FixedPoint value to be added to
     * current value
     *
     * @par Multi-thread safe:
     * Yes
     */
    inline void operator += (const FixedPoint& right);

    /**
     * @brief Sum and assignment operator
     *
     * @param FixedPoint right: reference to FixedPoint value to be added to
     * current value
     *
     * @par Multi-thread safe:
     * No
     */
    inline void operator += (int right);

    /**
     * @brief Subtraction and assignment operator
     *
     * @param FixedPoint right: reference to FixedPoint value to be subtracted
     * from current value
     *
     * @par Multi-thread safe:
     * No
     */
    inline void operator -= (const FixedPoint& right);

    /**
     * @brief Subtraction and assignment operator
     *
     * @param FixedPoint right: reference to FixedPoint value to be subtracted
     * from current value
     *
     * @return FixedPoint object containing the difference of originating
     * value and parameter
     *
     * @par Multi-thread safe:
     * No
     */
    inline void operator -= (int right);

    /**
     * @brief Multiplication and assignment operator
     *
     * @param FixedPoint right: reference to FixedPoint value to be multiplied
     * with current value
     *
     * @par Multi-thread safe:
     * No
     */
    Msf::FixedPoint operator *= (const FixedPoint& right);

    /**
     * @brief Multiplication and assignment operator
     *
     * @param FixedPoint right: int value to be multiplied with current value
     *
     * @return FixedPoint object containing the product of originating
     * value and parameter.
     *
     * @par Multi-thread safe:
     * No
     */
    inline void operator *= (int right);

    /**
     * @brief Division and assignment operator
     *
     * @param FixedPoint right: reference to FixedPoint value to divide
     * the current value with.
     *
     * @par Multi-thread safe:
     * No
     */
    Msf::FixedPoint operator /= (const FixedPoint& right);

    /**
     * @brief Divide and assign operator.
     *
     * @param right -- The value to divide this FixedPoint with.
     *
     * @par Multi-thread safe:
     * No
     */
    inline void operator /= (int right);

    /**
     * @brief Multiply, divide and assign
     *
     * @param multiplier - The value to multiply object value with
     * @param divisor - The value to divide the product with
     *
     * @return FixedPoint object containing the original value multiplied
     * with multiplier and divided with divisor
     *
     * @par Multi-thread safe:
     * No
     */
    Msf::FixedPoint mulDiv(const FixedPoint& multiplier, const FixedPoint& divisor);

    /**
     * @brief Produces a new FixedPoint with its value rounded using normal
     * rounding rules.
     *
     * @param precisionP -- The number of decimals used in the fraction
     * part of the output.
     *
     * @return FixedPoint containing the rounded value.
     *
     * @par Multi-thread safe:
     * Yes
     *
     * @par Constraints:
     * The precisionP must be between 0 and 4.
     */
    Msf::FixedPoint getRounded(unsigned int precisionP = 0) const;

    /**
     * @brief getRoundedInt combines two methods for performance.
     * getRoundedInt(prec) == getRounded(prec).getInt(prec)
     *
     * @param precisionP The number of decimals used in
     *                   the fraction part of the output.
     *
     * @return
     */
    inline int getRoundedInt(unsigned int precisionP = 0) const;

    /**
     * @brief Produces a new FixedPoint with its value rounded up.
     * Rounds towards plus infinity
     *
     * @param precisionP -- The number of decimals used in the fraction
     * part of the output.
     *
     * @return FixedPoint containing the rounded up value.
     *
     * @par Multi-thread safe:
     * Yes
     *
     * @par Constraints:
     * The precisionP must be between 0 and 4.
     */
    Msf::FixedPoint getRoundedUp(unsigned int precisionP = 0) const;

    /**
     * @brief Produces a new FixedPoint with its value rounded down.
     * Rounds towards minus infinity.
     *
     * @param precisionP -- The number of decimals used in the fraction
     * part of the output.
     *
     * @return FixedPoint containing the rounded down value.
     *
     * @par Multi-thread safe:
     * Yes
     *
     * @par Constraints:
     * The precisionP must be between 0 and 4.
     */
    Msf::FixedPoint getRoundedDown(unsigned int precisionP = 0) const;

    /**
     * @return FixedPoint containing the absolute value.
     *
     * @par Multi-thread safe:
     * No
     */
    inline Msf::FixedPoint getAbs() const;

    /**
     * @brief Returns an integer representation (a scaled integer) of a fixed
     * point with (1) its value based on this fixed point, but (2) only with
     * the given number of decimals in its fraction part. That is, the integer
     * representation returned is not necessarily the same as this fixed point
     * internaly has.
     *
     * Notice that the integer representation is truncated if necessary,
     * not rounded.
     *
     * @param precisionP -- The number of decimals in the fraction part of
     * the output. That is, this number determines what kind of fixed point
     * representation the returned integer
     *   uses: it may have 0, 1, 2, 3 or 4 decimals.
     *
     * @par Example:
     *    FixedPoint x(12.3456) has an internal representation of (int) 123456
     *    with an implicit number of 4 decimals. x.get Int(1) returns 123, with
     *    an implicit number of 1 decimal.
     *
     * @return the scaled integer representation of a presicion P decimal
     * fixed point.
     *
     * @par Multi-thread safe:
     * Yes
     *
     * @par Constraints:
     * The precisionP must be between 0 and 4.
     */
    inline int getInt(unsigned int precisionP = 0) const;

    /** @return float Value as a float.  */
    inline float getFloat() const;

    /** @return decimal part of the fixed point */
    inline int getDecimalPart() const
    {
        return valueM % BASE;
    }

    /**
     * @brief Multiplies with power of 2. This is the same as >> with
     * an integers. It also takes the same time as >> with integers.
     *
     * @par Example:
     *    fp << 1; // Is same as fp * 2 but faster
     *    fp << 3; // Is same as fp * 8 but faster
     *
     * @param power - (2 ^ power) is the value used in multiplication
     * @param divisor - The value to divide the product with
     */
    inline void operator <<= (int power);

    /**
     * @brief Divides with power of 2. This is the same as << with an
     * integers. It also takes the same time as << with integers.
     *
     * @par Example:
     *    fp >> 1; // Is same as fp / 2 but faster
     *    fp >> 3; // Is same as fp / 8 but faster
     *
     * @param power - (2 ^ power) is the value used in division
     */
    inline void operator >>= (int power);

    /**
     * @brief Negation operator.
     *
     * @return Negated FixedPoint.
     *
     * @par Multi-thread safe:
     * No
     */
    inline Msf::FixedPoint operator - () const;

    /** The minimum possible value of a FixedPoint. */
    static const Msf::FixedPoint MIN_S;

    /** The maximum possible value of a FixedPoint. */
    static const Msf::FixedPoint MAX_S;

    /** The number of decimals in the fraction part of a Fixed Point. */
    static const unsigned int NR_OF_DECIMALS_S = 4;

private:

    /**
     * Rounds a double value to an integer value.
     * -1.5 => -2
     * -1.4 => -1
     * 1.4  => 1
     * 1.5  => 2
     *
     * @param valueP [in] value to round.
     *
     * @return double rounded to int.
     */
    static inline IntS32 round(double valueP);

    /**
      * The variable that contains the fixed point value multiplied with
      * constant BASE.
      */
    IntS32 valueM;

    /** Table that contains BASE divided by powers of 10 for getRounded */
    static const IntS32 NTAB[NR_OF_DECIMALS_S+1];
    enum
    {
        /** Maximum integer */
        INTS32_MAX = INT_MAX,
        INTS32_MIN = INT_MIN,
        /** Square root of maximum integer. */
        SQRT_INTS32_MAX = 46340,
        /**
          * The constant that is used to multiply the fixed point value before
          * storing it into integer valueM. Change this to 16384 for faster
          * calculations. And tell people at CAD-UL to implement
          * multiplications and divisions with powers of two using
          * _arithmetical_ shift instructions as well.
          */
          BASE = 10000
    };

    friend const FixedPoint operator+(const FixedPoint& rLeftP, const FixedPoint& rRightP);
    friend const FixedPoint operator+(const FixedPoint& rLeftP, int rightP);
    friend const FixedPoint operator+(int leftP, const FixedPoint& rRightP);
    friend const FixedPoint operator-(const FixedPoint& rLeftP, const FixedPoint& rRightP);
    friend const FixedPoint operator-(const FixedPoint& rLeftP, int rightP);
    friend const FixedPoint operator-(int leftP, const FixedPoint& rRightP);
    friend const FixedPoint operator*(const FixedPoint& rLeftP, const FixedPoint& rRightP);
    friend const FixedPoint operator*(const FixedPoint& rLeftP, int rightP);
    friend const FixedPoint operator*(int leftP, const FixedPoint& rRightP);
    friend const FixedPoint operator/(const FixedPoint& rLeftP, const FixedPoint& rRightP);
    friend const FixedPoint operator/(const FixedPoint& rLeftP, int rightP);
    friend const FixedPoint operator<<(const FixedPoint& rLeft, int right);
    friend const FixedPoint operator>>(const FixedPoint& rLeft, int right);
};

/**
  * Standard way of doing these operations is to:
  * 1. Create temporary value.
  * 2. Use assigmenet version of operation.
  * 3. Return temporary.
  *
  * For example:
  *  operator+(const FixedPoint& rLeftP, const FixedPoint& rRightP) {
  *    FixedPoint temp(rLeftP); // Create temporary
  *    temp += rRight; // Use assigment version
  *    return temp; // Return temp
  *  }
  *
  * However, CAD-UL compiler makes really bad optimization on that code.
  * Therefore, these methods were made friends of the class and assingment
  * version of operation was not used.
  *
  * For the very same reason, there is separate version for integer operands.
  * When CAD-UL is no longer used, we can return back to standard way of
  * doing this. At least Microsoft compiler can optimize it beautifully.
  */

inline const FixedPoint
    operator+(const FixedPoint& rLeftP, const FixedPoint& rRightP)
{
    FixedPoint retVal(rLeftP);
    retVal.valueM += rRightP.valueM;
    return retVal;
}

inline const FixedPoint
    operator+(const FixedPoint& rLeftP, int rightP)
{
    FixedPoint retVal(rLeftP);
    retVal.valueM += rightP * FixedPoint::BASE;
    return retVal;
}

inline const FixedPoint
    operator+(int leftP, const FixedPoint& rRightP)
{
    FixedPoint retVal(rRightP);
    retVal.valueM += leftP * FixedPoint::BASE;
    return retVal;
}

inline const FixedPoint
    operator-(const FixedPoint& rLeftP, const FixedPoint& rRightP)
{
    FixedPoint retVal(rLeftP);
    retVal.valueM -= rRightP.valueM;
    return retVal;
}

inline const FixedPoint
    operator-(const FixedPoint& rLeftP, int rightP)
{
    FixedPoint retVal(rLeftP);
    retVal.valueM -= rightP * FixedPoint::BASE;
    return retVal;
}

inline const FixedPoint
    operator-(int leftP, const FixedPoint& rRightP)
{
    FixedPoint retVal(leftP);
    retVal.valueM -= rRightP.valueM;
    return retVal;
}

inline const FixedPoint
    operator*(const FixedPoint& rLeftP, const FixedPoint& rRightP)
{
    // There is now way to optimize this.
    FixedPoint retVal(rLeftP);
    retVal *= rRightP;
    return retVal;
}

inline const FixedPoint
    operator*(const FixedPoint& rLeftP, int rightP)
{
    FixedPoint retVal(rLeftP);
    retVal.valueM *= rightP;
    return retVal;
}

inline const FixedPoint
    operator*(int leftP, const FixedPoint& rRightP)
{
    FixedPoint retVal(rRightP);
    retVal.valueM *= leftP;
    return retVal;
}

inline const FixedPoint
    operator/(const FixedPoint& rLeftP, const FixedPoint& rRightP)
{
    //MSF_ASSERT(rRightP.valueM != 0);

    // There is now way to optimize this.
    FixedPoint retVal(rLeftP);
    retVal /= rRightP;
    return retVal;
}

inline const FixedPoint
    operator/(const FixedPoint& rLeftP, int rightP)
{
    //MSF_ASSERT(rightP != 0);

    FixedPoint retVal(rLeftP);
    retVal.valueM /= rightP;
    return retVal;
}

inline const FixedPoint
    operator<<(const FixedPoint& rLeft, int right)
{
    FixedPoint temp(rLeft);
    temp.valueM <<= right;
    return temp;
}

inline const FixedPoint
    operator>>(const FixedPoint& rLeft, int right)
{
    FixedPoint temp(rLeft);
    temp.valueM >>= right;
    return temp;
}

inline FixedPoint::FixedPoint()
  : valueM(0)
{
    // Default constructor. Does nothing.
}

inline FixedPoint::FixedPoint(double valueP)
{
    load(valueP);
}

inline FixedPoint::FixedPoint(int valueP, unsigned int precisionP)
{
    load(valueP, precisionP);
}

inline FixedPoint::FixedPoint(int valueP)
{
    load(valueP);
}

inline void FixedPoint::load(double valueP)
{
    valueM = round(valueP * BASE);
}

inline void FixedPoint::load(int valueP, unsigned int precisionP)
{
    //MSF_ASSERT(precisionP <= NR_OF_DECIMALS_S);

    IntS32 temp = valueP * NTAB[precisionP];
    valueM = temp;
}

inline void FixedPoint::load(int valueP)
{
    IntS32 temp = valueP * BASE;
    valueM = temp;
}

inline bool FixedPoint::operator==(const FixedPoint& right) const
{
    return(valueM == right.valueM);
}

inline bool FixedPoint::operator!=(const FixedPoint& right) const
{
    return(valueM != right.valueM);
}

inline bool FixedPoint::operator<(const FixedPoint& right) const
{
    return(valueM < right.valueM);
}

inline bool FixedPoint::operator>(const FixedPoint& right) const
{
    return(valueM > right.valueM);
}

inline bool FixedPoint::operator<=(const FixedPoint& right) const
{
    return(valueM <= right.valueM);
}

inline bool FixedPoint::operator>=(const FixedPoint& right) const
{
    return(valueM >= right.valueM);
}

inline void FixedPoint::operator += (const FixedPoint& right)
{
    // The fixed point numbers can be added directly, as the constant
    // multiplier is preserved in the sum.
    valueM += right.valueM;
}

inline void FixedPoint::operator += (int right)
{
    valueM += right * BASE;
}

inline void FixedPoint::operator -= (const FixedPoint& right)
{
    // The fixed point numbers can be subtracted directly, as the constant
    // multiplier is preserved in the difference.
    valueM -= right.valueM;
}

inline void FixedPoint::operator -= (int right)
{
    valueM -= right * BASE;
}

inline void FixedPoint::operator *= (int right)
{
    valueM *= right;
}

inline void FixedPoint::operator /= (int right)
{
    //MSF_ASSERT(right != 0);
    valueM /= right;
}

inline Msf::FixedPoint FixedPoint::getAbs() const
{
    FixedPoint fp;
    fp.valueM = (valueM >= 0 ? valueM : -valueM);
    return fp;
}

inline int FixedPoint::getInt(unsigned int precisionP) const
{
    //MSF_ASSERT(precisionP <= NR_OF_DECIMALS_S);

    return valueM / NTAB[precisionP];
}

inline float FixedPoint::getFloat() const
{
    return static_cast<float>(valueM)/static_cast<float>(BASE);
}

inline int FixedPoint::getRoundedInt(unsigned int precisionP) const
{
    // MSF_ASSERT(precisionP <= NR_OF_DECIMALS_S);

    int factor = NTAB[precisionP];
    if (valueM >= 0)
    {
        return((valueM + (factor / 2)) / factor);
    }
    else
    {
        return((valueM - (factor / 2)) / factor);
    }
}

inline void FixedPoint::operator <<= (int power)
{
    valueM <<= power;
}

inline void FixedPoint::operator >>= (int power)
{
    valueM >>= power;
}

inline Msf::FixedPoint FixedPoint::operator - () const
{
    FixedPoint temp;
    // Faster (hopefully...) than "temp.valueM = -valueM;"
    // We can do it since temp.valueM is initialized to 0
    temp.valueM -= valueM;
    return temp;
}

inline IntS32 FixedPoint::round(double valueP)
{
    return valueP > 0 ? static_cast<IntS32>(valueP + .5) : static_cast<IntS32>(valueP - .5);
}

} // namespace Msf

#endif
