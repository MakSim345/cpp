#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_

#include "gen.h"
#include "employee.h"
#include "room.h"

class department
{
public:
    department()
    {
        _dep_name = "no_name";
    }

    department(string new_name)
    {
        _dep_name = new_name;
    }

    void setName(string new_name)
    {
        _dep_name = new_name;
    }

    string getName()
    {
        return this->_dep_name;
    }
    /*
    void addEmployee(employee new_worker)
    {   
        new_worker.setDepartment(this);
        this->workers.push_back(new_worker);
        cout << endl;
        // std::cout << "Employee "<< _name << " got an id card number: " << _my_card._number << "\n";
    }

    vector<employee> getWorkers()
    {
        return this->workers;
    }
    */

private:
    string _dep_name;
    // vector<employee> workers; 

};
#endif
