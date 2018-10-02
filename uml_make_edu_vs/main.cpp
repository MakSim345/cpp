#include "gen.h"
#include "employee.h"
#include "idcard.h"
#include "room.h"
#include "timestamp.h"
#include <Windows.h>


using namespace std;

inline float cube(const float s) {return s*s*s;}

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";
        //cout << "Enter id card number\n";
        int tmp = 35;
        //cin >> tmp;  
        
        timestamp* tst = new timestamp();

        create_id_card(tmp);
        create_employee();
        room room101 = room(101);
        room room105 = room(105);
        _employee->setRoom(room101);
        _employee->setRoom(room105);
        
        power_of_two(10);

        return 0;
    }

    void create_room()
    {
        room room101 = room(101);
    }

    void create_employee()
    {
        _employee = new employee("John", "Smith", "BOSS");
        _employee->setIdCard(this->_my_idcard);
    }

    void create_id_card(int new_card)
    {
        // idcard *_my_idcard = new idcard(1);
        this->_my_idcard = idcard(new_card);
        // _my_idcard = idcard(122);
        // _my_idcard.setNumber(122);
        std::cout << "create an idcard number: " << _my_idcard.getNumber() << "\n";        
    }

    void power_of_two(int _max_val)
    {
        int x = 1;
        int _tmp_res;
        int i;
        std::cout << "Power of 2 for non-even: "<< "\n";
        for (i = 0; i <= _max_val; i++)
        {
            _tmp_res = x*x;
            printf ("%3i\t%4i\n", x, _tmp_res);
            x += 2;
        }
    }
    

    ~App()
    {
        std::cout << "Good bye!\n";
    }

private:
    idcard _my_idcard;
    employee*_employee;
};


int main()
{
    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());
    //cube_calc->run();
    std::auto_ptr <App> bakery(new App());
    try
    {
        bakery->Run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }    
    */
    system ("PAUSE");
    return 1;
}
