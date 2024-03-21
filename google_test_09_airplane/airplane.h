#ifndef _AIR_PLANE_H_
#define _AIR_PLANE_H_

#include "gen.h"

class Airplane
{
    enum
    {
        MIN_NUMBER_OF_SEATS = 10,
        MAX_NUMBER_OF_SEATS = 200,
    };

public:
    Airplane();

    Airplane(size_t numberOfSeats, double fuelTankCapacity)
        : m_numberOfSeats(numberOfSeats),
          m_fuelTankCapacity(fuelTankCapacity),
          m_fuel(0.0)
    {

        // DEBUG: std::cout << "Airplane create with: " <<  m_numberOfSeats << " seats\n";
        if ((numberOfSeats > MAX_NUMBER_OF_SEATS) ||
            (numberOfSeats < MIN_NUMBER_OF_SEATS))
        {
            throw std::invalid_argument("trow: Number of seats is out of range!");
        }
    }

    void reFuel(double fuel_in_litres)
    {
        // DEBUG: std::cout << "Airplane reFuel: current " <<  m_fuel << " l.\n";
        // DEBUG: std::cout << "Airplane reFuel: to add " <<  fuel_in_litres << " l.\n";
        m_fuel = m_fuel + fuel_in_litres;
        if (m_fuel > m_fuelTankCapacity)
        {
            m_fuel = m_fuelTankCapacity;
        }
        // DEBUG: std::cout << "Airplane reFuel: after add " <<  m_fuel << " l.\n";
    }

    double getFuel() const {return m_fuel;}
    double getFuelTankCapacity () const {return m_fuelTankCapacity;}

    size_t getNumberOfPassengers() const {return 0;}
    size_t getNumberOfSeats() const {return m_numberOfSeats;}
    size_t getNumberOfPilots() const {return 0;}
    size_t getNumberOfStewardess() const {return 0;}
    // ~Airplane();

    bool canFly();

private:
    std::string mFuel;
    std::string mColor;
    size_t m_numberOfSeats;
    double m_fuelTankCapacity;
    double m_fuel;
    bool isFuel;
};
#endif
