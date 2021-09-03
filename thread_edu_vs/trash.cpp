//============================================================
//
// Description:
// <purpose of this file>
//============================================================
#include "trash.h"

class String
{
public:
    String() = default;

    String(const char* stringP)
    {
        printf("Created!\n");
        m_Size = strlen(stringP);
        m_Data = new char[m_Size];
        memcpy(m_Data, stringP, m_Size);
    }

    // copy constructor:
    String(const String& otherP)
    {
        printf("Copied!\n");
        m_Size = otherP.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, otherP.m_Data, m_Size);
    }
    ~String()
    {
        delete m_Data;
    }

    void Print()
    {
        for (uint32_t i = 0; i < m_Size; i++)
        {
            printf("%c", m_Data[i]);
        }
        printf("\n");
    }

private:
    uint32_t   m_Size;
    char* m_Data;

};

class Entity
{
public:
    Entity(const String& nameP)
        : m_Name(nameP)
    {

    }

    // ~Entity();
    void PrintName()
    {
        m_Name.Print();
    }

private:
    String m_Name;
};

#ifdef YS_TEST_20210827
int produceRND()
{
    static int nFirstTime = 1;
    int random;
 
    if (1 == nFirstTime)
    {
        srand (time (NULL));
        nFirstTime = 0;
    }
    random = 1 + (rand() % RND_MAX);
    return random;
}
 

bool isAdult(Person &p)
{
    if (18 < p.age)
    {
        return true;
    }
    return false;
}

void checkDasha()
{
    Person dasha = {15, 160, 50, "Dasha", "Student"};    
    cout << sizeof(dasha) << endl;
    cout << dasha.name << " is ";
    if (!isAdult(dasha))
    {
        cout << "not ";
    }
    cout << "an adult\n";
}

class A 
{
private:
    int a;
    int b;

public:
    A(int x)
      :b(x)
      ,a(b) 
    {
     // NOP;
    }
    void dump() 
    {
        std::cout << "a=" << a << " b=" << b << std::endl;
    }
};


//-------------------CLASS definition----------------
_my_template_class_t::_my_template_class_t()
{   
    system ("TITLE Phone book");
    system ("color 0A");
}

void _my_template_class_t::run()
{
    for (int i = 0; i<25; i++)
    {
        //int a=rand() % matrix_array.size();
        //cout << " " << matrix_array[a];
        cout << " ";
    }
    cout << endl;
}
//---------------END of CLASS Definition--------------

#endif