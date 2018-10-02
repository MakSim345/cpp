#include "gen.h"

#include "Address.h"
#include "Person.h"
#include "Student.h"

class App
{
public:
    int run()
    {
        std::cout << "Run....\n";
        vector<unique_ptr<Person>> persons;
        persons.push_back(unique_ptr<Person> (new Person("Ville", 20)));
        persons.push_back(unique_ptr<Person> (new Person("Marja", 20)));
        persons.push_back(unique_ptr<Person> (new Person("Maija", 20)));
        persons.push_back(unique_ptr<Person> (new Student("Kalle", 20, 0, "kalle_test")));

        // for (const vector<Person*>::iterator it = persons.begin(); it != persons.end(); ++it)
        for (auto it = persons.begin(); it != persons.end(); ++it)
        // for (Person * p : persons)
        { 
            (*it)->printData();
        }

        /* for (Person * p : persons)
        { 
            p->printData();
        }*/

        persons.clear();

        return 0;
    }
    int run_usual_way()
    {
        std::cout << "Run....\n";
        vector<Person*> persons;
        persons.push_back(new Person("Ville", 20));
        persons.push_back(new Person("Marja", 25));
        persons.push_back(new Person("Maija", 19));
        persons.push_back(new Student("Kalle", 20, 0, "xxxyyy"));

        Person* x = new Student("Anna", 19, 0, "test" );
        x->printData(); // if printData not virtual, it will print not Student, but Person
        delete x;

        // for (const vector<Person*>::iterator it = persons.begin(); it != persons.end(); ++it)
        for (auto it = persons.begin(); it != persons.end(); ++it)
        // for (Person * p : persons)
        { 
            (*it)->printData();
        }

        /* for (Person * p : persons)
        { 
            p->printData();
        }*/


        for (vector<Person*>::iterator it = persons.begin(); it != persons.end(); ++it)
        {
            delete *it;
        }

        persons.clear();

        return 0;
    }
    ~App()
    {
        std::cout << "Destructor called\n";
    }

};


int main() 
{
    // CubeCalc *cube_calc = new CubeCalc();
    // std::auto_ptr <App> app(new App());
    std::unique_ptr<App> app(new App());
    app->run();    

	system("pause");
	return EXIT_SUCCESS;
}




