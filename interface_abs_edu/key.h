#ifndef _KEY_H_
#define _KEY_H_

class Key
{
public:
    Key() { cout << "Key: >> Constructor." << endl; };
    ~Key(){ cout << "Key: << Destructor." << endl; };

    void Open()
    {
        cout << "Key: -> Open." << endl;
        Insert();
        Turn();
        Remove();
    }
    
private:
    void Insert() { cout << "Key: Insert called." << endl; };
    void Turn()   { cout << "Key: Turn called." << endl; };
    void Remove() { cout << "Key: Remove called." << endl; };
};


#endif