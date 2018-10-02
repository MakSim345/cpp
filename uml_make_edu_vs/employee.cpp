#include "employee.h"

man::man()
{
    std::cout << "New man object created.\n";
}

employee::employee(string my_name, string my_surname, string my_position)
{
    _name = my_name;
    _surname = my_surname;
    _position = my_position;
}
