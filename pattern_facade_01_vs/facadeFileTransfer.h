#include <iostream>
#include "gen.h"

class USB
{
public:
    bool isAvailable()
      {
        cout << "checking is USB available...." << endl;
        return false;
      }

    void connect()
    {
        cout << "connecting via USB..." << endl;
    }  

    void send(string file)
    {
        cout <<  file <<" sent!" << endl;
    }  
};

class Bluetooth
{
public:
    bool isAvailable()
      {
        cout << "checking is Bluetooth available...." << endl;  
        return true;
      }

    void connect()
    {
        cout << "connecting via Bluetooth...\n";
    }  

    void authenticate()
    {
        cout << "authenticating Bluetooth...\n";
    }  

    void send(string file)
    {
        cout <<  file <<" sent!\n";
    }  
};

// The Facade:
class facadeFileTransfer
{
public:
    
    void sendFile(string fileName)
    {
        USB* u = new USB();
        Bluetooth* b = new Bluetooth();

        if (u->isAvailable ())
        {
            u->connect();
            u->send(fileName);
        }

        if (b->isAvailable ())
        {
            b->connect();
            b->authenticate();
            b->send(fileName);
        }
        else
        {
            cout << "File not sent!\n";
        }
        delete u;
        delete b;        
    }  

};

