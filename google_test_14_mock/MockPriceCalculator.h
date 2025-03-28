#pragma once

#include <gmock/gmock.h>
#include "PriceCalculator.h"

class MockPriceCalculator:public PriceCalculator
{
public:
    // MockPriceCalculator(/* args */);
    // ~MockPriceCalculator();
    /*
     * The MOCK_CONST_METHOD4 macro in the MockPriceCalculator class is used to define
     * a mock method that simulates the behavior of the calculateTotalPrice method from
     * the PriceCalculator class. The number "4" in MOCK_CONST_METHOD4 indicates that
     * the mock method takes four parameters, which corresponds to the four parameters of
     * the original calculateTotalPrice method.
     */

    MOCK_CONST_METHOD4(calculateTotalPrice, double(int item1Quantity, double item1Price, int item2Quantity, double item2Price));
};
