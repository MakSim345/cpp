#include "gen.h"
#include "PriceCalculator.h"


class ShoppingCart
{
public:
    ShoppingCart(PriceCalculator* priceCalculatorP):
        priceCalculatorM(priceCalculatorP)
        {
            //
        }

    ~ShoppingCart();

    double getTotalPrice(int item1Quantity, double item1Price, int item2Quantity, double item2Price) const
    {
        return priceCalculatorM->calculateTotalPrice(item1Quantity, item1Price, item2Quantity, item2Price);
    }

private:
    PriceCalculator* priceCalculatorM;
};



