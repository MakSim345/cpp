#include "gen.h"
#include "nand.h"

NAND::NAND()
    :a(0),
     b(0)
{
    run();
}

bool NAND::toBool(int toConvert)
{
    if (toConvert)
        return true;
    else
        return false;
}

int NAND::toInt(bool toConvert)
{
    if (toConvert)
        return true;
    else
        return false;
}

void NAND::run()
{
    b_a = toBool(a);
    b_b = toBool(b);
    b_out = !(b_a && b_b);
    out = toInt(b_out);
}

/************************************/
void NOT::run()
{
    nand->a = in;
    nand->b = in;
    nand->run();
    out = nand->out;
}

NOT::NOT()
    :in(0)
{
    nand = new NAND();
    run();
}
/************************************/

