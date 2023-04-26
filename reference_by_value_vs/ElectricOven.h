#ifndef _ELECTRIC_OVEN_H_
#define _ELECTRIC_OVEN_H_

#include "gen.h"
#include "OvenIf.h"

class ElectricOven: public OvenIf
{
public:
    static int gCounter;

    ElectricOven();
    virtual ~ElectricOven();
    std::string getColor();
    
    int getId() {return mId;}
    void setId(int newId) {mId = newId;}
    
    static int getCount()
    {
        // can return only static!
        return gCounter;
    }

    virtual bool canBake();   
    virtual void start();
    virtual void stop();
    

private:
    std::string mCurrency; // 110 - 220 volt
    std::string mColor;
    bool isCurrency;
    int mId;
    //...
};
#if 0
class Box
{
   public:
      static int objectCount;
      // Constructor definition
      Box(double l=2.0, double b=2.0, double h=2.0)
      {
         cout <<"Constructor called." << endl;
         length = l;
         breadth = b;
         height = h;
         // Increase every time object is created
         objectCount++;
      }
      double Volume()
      {
         return length * breadth * height;
      }
      static int getCount()
      {
         return objectCount;
      }
   private:
      double length;     // Length of a box
      double breadth;    // Breadth of a box
      double height;     // Height of a box
};

// Initialize static member of class Box
int Box::objectCount = 0;
#endif // 0

#endif

