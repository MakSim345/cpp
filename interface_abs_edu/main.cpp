#include "gen.h"
#include "utils.h"
#include "ikey.h"
#include "key.h"

class MyKey : public Key
{
public:
    MyKey() { cout << "MyKey: >> Constructor." << endl;};
   ~MyKey(){ cout << "MyKey: >> Destructor." << endl; };    
};


class MagneticKey : public Key
{
public:
   MagneticKey() { cout << "MgntKey: >> Constructor." << endl;};
  ~MagneticKey(){ cout << "MgntKey: >> Destructor." << endl;};    
   void Open()
   {
        cout << "MgntKey: -> Open." << endl;

   }
    
};

class TurnKey : public iKey
{
public:
   TurnKey(){ cout << "TurnKey: >> Constructor." << endl;};
  ~TurnKey(){ cout << "TurnKey: >> Destructor." << endl;};
   void Open()
   {
        cout << "TurnKey: -> Open." << endl;
        Insert();
        Turn();
        Remove();
    }
    
private:
    void Insert() { cout << "TurnKey: Insert." << endl; };
    void Turn()   { cout << "TurnKey: Turn." << endl; };
    void Remove() { cout << "TurnKey: Remove." << endl; };    
};

class MgntKey : public iKey
{
public:
   MgntKey(){ cout << "MgntKey: >> Constructor." << endl;};
  ~MgntKey(){ cout << "MgntKey: >> Destructor." << endl;};
   void Open()
   {
        cout << "MgntKey: -> Open." << endl;
        Insert();
        Slide();
        Remove();
    }
    
private:
    void Insert() { cout << "MgntKey: Insert." << endl; };
    void Slide()  { cout << "MgntKey: Slide." << endl; };
    void Remove() { cout << "MgntKey: Remove." << endl; };
    
};

void test_inherit()
{
    Key* _key = new MagneticKey();
    _key->Open();

    delete _key;

    //MagneticKey _mgntKey;
    //_mgntKey.Open();
}


int main()
{
    cout << "APP start:" << endl;
    iKey* _key = new TurnKey();
    _key->Open();

    _key = new MgntKey();
    _key->Open();

    delete _key;
    
    cout << "APP END:" << endl;
    // getch();
}


