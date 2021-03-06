#include "gen.h" 

class Dog 
{
public:
    Dog(string nameP) { std::cout << "Dog is created: " << nameP << std::endl; _name = nameP; }
    Dog() { std::cout << "Nameless dog created. " << std::endl; _name = "nameless"; }
   ~Dog() { std::cout << "Dog is destroyed: " << _name << std::endl; }

    void bark() {std::cout << "Dog " << _name << " rules!" << std::endl;}
private:
    string _name;
};

void simple_pointer()
{
    Dog* p = new Dog("Gunner");
    // delete p; // if delete happens here, there will ba dangling pointer - undefined behaviot
    p->bark();
    // delete p;
} // Memory leak

void foo_shared_pointers()
{
    shared_ptr<Dog> p(new Dog("Gunner")); // counter == 1
    //1. "Gunner" is created 2. p is created
    cout << p.use_count() << std::endl;
    // delete p; // if delete happens here, there will ba dangling pointer - undefined behaviot
    {
        shared_ptr<Dog> p2 = p; // counter == 2
        cout << p.use_count() << std::endl;
        p2->bark();
    }  // counter == 1
    cout << p.use_count() << std::endl;
    p->bark();
    // delete p;
} // counter == 0

void foo()
{   
    shared_ptr<Dog> p4 (new Dog[3]);

    shared_ptr<Dog> p1 = make_shared<Dog>("Gunner"); // using delete operator.
    shared_ptr<Dog> p2 = make_shared<Dog>("Tank");    

    p1 = p2; // Gunner is deleted
    p1 = nullptr; // Gunner is deleted
    p1.reset(); // Gunner is deleted

    // memory leak: (dog[1] and dog[2])
    // shared_ptr<Dog> p3 = shared_ptr<Dog>(new Dog("superTank"));
}


void error_foo()
{
    Dog* d = new Dog("Tank");

    // erroneous code:
    shared_ptr<Dog> p(d); // delete "Tank"   
    //shared_ptr<Dog> p2(d); // try to delete "Tank" again!

    //use make_shared is faster and safe way:
    shared_ptr<Dog> p3 = make_shared<Dog>("SuperTank");
} 


int main(int argc, char *argv[], char *envp[]) 
{
	int RValue = false;
	int CaptureModeHex = 0;
	int NewChar=0;
	int nResult = 0;
    int arraySize = 2000;

    srand(time(NULL));

    printf ("main - start\n");
    
    foo();
    // foo_shared_pointers();
    //error_foo();



//*************MAIN LOOP*****************//
    cout << "\n$ > Press Any Key to exit." << std::endl;
    do 
    {
        //This is simple Windows way:
        Sleep(55);

        
        // control of endless loop (may be also in monitor.cpp)
        if (_kbhit())  // has anything been pressed from keyboard ?
        {
            NewChar=(unsigned char)_getch();
            RValue = true;
            if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
            {
                RValue = true; // END mark
            }     
            if (NewChar == 'd')  // pressed
            {
                if (1 == CaptureModeHex) 
                    CaptureModeHex = 1;
		        else
                    CaptureModeHex = 0;
            }
        }
    } while (!RValue);  
    
    printf ("Application complete.\n");
    // system ("PAUSE");
    return 0;
}


