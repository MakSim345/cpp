#pragma once

#include "gen.h"

class PriceCalculator
{
public:
    ~PriceCalculator();

    double calculateTotalPrice(int item1Quantity, double item1Price, int item2Quantity, double item2Price) const;
};