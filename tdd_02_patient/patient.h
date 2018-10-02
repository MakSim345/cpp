#ifndef _PATIENT_H_
#define _PATIENT_H_

#include "gen.h"

class Patient
{
public:
    // Patient(const std::string& name, const std::string& location);
    Patient(std::string name, std::string location);
    
    ~Patient() {};

    std::string toString() const;
    std::string getName() const;
    std::string getLocation() const;
    bool isAlive();
    void test_str_len();

private:
    std::string _name;
    std::string _location;
    bool _alive;
};

class InvalidLocation : public std::runtime_error
{
public:
    InvalidLocation() : std::runtime_error("Invalid location") {};
    // InvalidLocation(std::string error_message) : std::runtime_error(error_message) {};
    // InvalidLocation(const std::string& msg) : runtime_error(BuildMessage(msg, id)) { }
    
};

#endif
