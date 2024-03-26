#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "gen.h"

class Figure
{
protected:
    double x; 
    double y;

public:
    void setDimentions(double i, double j) 
    {
        x = i;
        y = j;
    }

    Figure(): x(0.0), y(0.0)
    {
        std::cout << "Figure object created" << std::endl;
    }
    
    virtual void showArea() = 0
    {
        cout << "No area computation defined ";
        cout << "for this class. \n";
    }
};

class Triangle: public Figure 
{
public:
    Triangle()
    {
        //this->x = 10.0;
        //this->y = 20.0;
    }

    void showArea() override
    {
        cout << "Triangle with height ";
        cout << x << " and base " << y;
        cout << " has an area of ";
        cout << (x * (0.5 * y)) << ". \n";
    }
};

class Square: public Figure 
{
public:
    void showArea() 
    {
        cout << "Square with dimensions ";
        cout << x << " x " << y;
        cout << " has an area of ";
        cout << x * y << ". \n";
    }
};

class Circle: public Figure 
{
public:
    void showArea() 
    {
        cout << "Circle with radius ";
        cout << x;
        cout << " has an area of ";
        cout << 3.14 * x * x;
    }
};

#endif

