#include "gen.h"
#include "person.h"

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world!\n";
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};

int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    // std::auto_ptr <Person> pers(new Person());
    std::unique_ptr <Person> pers(new Person());
    pers->setName("Ada Lovelace");
    pers->setAge(19);
    
    // boost::array<int, 4> arr = {{1,2,3,4}};
    std::cout << "My Name:" << pers->getName() << "\n"; 
    std::cout << "-age:" << pers->getAge() << "\n"; 
    return 0;
}
