#include "animal.h"

// Constructor:
Animal::Animal(std::string animalNameP, Winner *winP) :
    firstCharNameM(animalNameP.at(0)), // Initialize firstCharNameM with the first character of animalNameP
    strNameM(std::move(animalNameP)),  // Use std::move to avoid unnecessary string copying
    nPositionM(1),                     // Initialize nPositionM to 1
    winner(winP)                       // Initialize winner with the provided pointer
{
    // Constructor body can remain empty unless additional logic is required
}

void Animal::setPos(int nPos)
{
    nPositionM=nPositionM + nPos;

    if (nPositionM <= 0)
    {
        nPositionM = 1;
    }

    if (nPositionM >= MAIN_LINE)
    {
        nPositionM = MAIN_LINE;
        this->winner->setWinner(strNameM);
    }
}