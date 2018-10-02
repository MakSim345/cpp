class employee 
{
public:
   virtual int salary();
};

class manager : public employee 
{
public:
   int salary();
};

class programmer : public employee 
{
public:
   int salary();
};


void payroll( employee *pe ) 
{
   pe->salary()
}


int main()
{
    
    return 0;
}
