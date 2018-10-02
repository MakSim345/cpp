#include "patient.h"


// Patient::Patient(const std::string& name, const std::string& location)
Patient::Patient(std::string name, std::string location)
    : _name(name)
    , _location(location)
    , _alive(true)

    {
        if ("bed" != _location.substr(0,3))
        {
            throw InvalidLocation();
        }
        std::cout << "\nPatient " << _name << " created\n";
    }

void Patient::test_str_len()
{
    int a = strlen(_name.c_str());
    std::cout << "\nPatient " << _name << " has " << a << " characters.\n";
    std::cout << "\nPatient " << _name << " tested\n";

}


bool Patient::isAlive()
{
    return this->_alive;
}

std::string Patient::getName() const
{
    return this->_name;
}

std::string Patient::getLocation() const
{
    return this->_location;
}

std::string Patient::toString() const
{
    std::string alive_condition = "";
        if (_alive)
            alive_condition = "still alive";
        else        
            alive_condition = "gone";
    return "Patient '" + _name + "' is in '" + _location + "' and he is " + alive_condition;
}

/*
InvalidLocation::InvalidLocation(std::string error_message) : runtime_error(error_message)
{ 
    std::runtime_error("Invalid location");
}
*/

