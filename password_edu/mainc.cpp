#include "gen.h"
#include "pass.h"
#include "divide_by_zero.h"
#include "factorial.h"

int test_div_zero()
{
    int num1, num2;    
    cout << "BBeguTe 2 4ucLa gLq geLeHuq:\n";
    cin >> num1 >> num2;
    try 
    {
        float result =  quotient(num1, num2);
        cout << "4acTHoe paBHo: " << result << endl; 
    }      
    catch (DivideByZeroError err)
    {
        cout << "ERROR: ";
        err.printMesage();
        cout << endl;
        return 1;
    }
    return 0;    
}

void create_passwords(const int& pPass_len, const int& pPass_num)
{
    std::auto_ptr <Pass> pass_calc(new Pass());
    /*
    for (int i = 0; i < pPass_num; i++)
    {
        std::cout << "---------------------------\n";
        std::cout << pass_calc->run(pPass_len) << "\n";
        std::cout << "---------------------------\n";
    }
    */

    for (int i = 0; i < pPass_num; i++)
    {
        std::cout << pass_calc->run(pPass_len) << ", ";
    }
    
    std::cout << "\n";
}

void create_one_password(const int& pPass_len)
{
    std::auto_ptr <Pass> pass_calc(new Pass());    
    std::cout << "Password: \n";
    std::cout << pass_calc->run(pPass_len) << "\n";
}

int main(int argc, char *argv[], char *envp[]) 
{
    const int pass_len = 10;
    const int pass_num = 10000;

    // printf ("main - start\n");   
    create_passwords(pass_len, pass_num);
    // create_one_password(pass_len);
    //Factorial *m_f = new Factorial();
    //m_f->run();
    
    // printf ("Application complete.\n");
    return 0;
}

