#include "PriceCalculator.h"

double PriceCalculator::calculateTotalPrice(int item1Quantity, double item1Price, int item2Quantity, double item2Price) const

{
    return (item1Quantity * item1Price) + (item2Quantity * item2Price);
}

PriceCalculator::~PriceCalculator()
{
    // ~PriceCalculator();
}

