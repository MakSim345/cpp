#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include "gen.h"
#include "idcard.h"
#include "room.h"
#include "department.h"
class department;

class man
{
public:
    man();
    void setName(string new_name)
    {

        this->_name = new_name;
    }
    string getName()
    {
        return this->_name;
    }

    void setSurName(string new_surname)
    {

        this->_surname = new_surname;
    }
    string getSurName()
    {
        return this->_surname;
    }

    
    string _name;
    string _surname;

};

class employee: public man
{
public:

    employee(string my_name, string my_surname, string my_position);
    ~employee();

    void setPosition(string new_profession)
    {

        this->_position = new_profession;
    }
    string getPosition()
    {
        return this->_position;
    }
    
    void setIdCard(idcard new_card)
    {
        _my_card = new_card;
        std::cout << "Employee "<< _name << " got an id card number: " << _my_card._number << "\n";
    }

    idcard getIdCard()
    {
        return _my_card;
    }

    void setRoom(room newRoom)
    {
        this->rooms.push_back(newRoom);
        cout << "Room number" << newRoom._number << " added!\nList of rooms:\n";
        for( int i = 0; i < rooms.size(); i++ ) 
        {
            cout << rooms[i]._number << "\n";
        }   
        cout << endl;
    }

    void deleteRoom(room room_to_delete)
    {
      /*for (int i = 0; i < rooms.size(); i++)
        {
        if (rooms[i] == room_to_delete)
            {
                cout << "room_to_delete" << " - " << rooms[i] << "\n";
            }
        }*/

    }
    vector<room> getRoom()
    {
        return this->rooms;
    }
	/*
    void setDepartment(department new_dep)
    {
        this->_dep = new_dep;
    }

    department getDepartment()
    {
        return this->_dep;
    }
	*/
private:
    string _position;
    idcard _my_card;
    vector<room> rooms; 
    department *_dep;
};





#endif
