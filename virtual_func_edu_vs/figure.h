#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "gen.h"

class figure
{
protected:
    double x; 
    double y;

public:
    void set_dim( double i, double j) 
    {
        x = i;
        y = j;
    }

    figure() 
    {
        std::cout << "figure object created" << std::endl;
    }
    
    virtual void show_area() = 0
    {
        cout << "No area computation defined ";
        cout << "for this class. \n";
    }
};


class triangle: public figure 
{
public:
    triangle()
    {
        //this->x = 10.0;
        //this->y = 20.0;
    }

    void show_area() 
    {
        cout << "Triangle with height ";
        cout << x << " and base " << y;
        cout << " has an area of ";
        cout << (x * (0.5 * y)) << ". \n";
    }
};

class square: public figure 
{
public:
    void show_area() 
    {
        cout << "Square with dimensions ";
        cout << x << " x " << y;
        cout << " has an area of ";
        cout << x * y << ". \n";
    }
};

class circle: public figure 
{
public:
    void show_area() 
    {
        cout << "Circle with radius ";
        cout << x;
        cout << " has an area of ";
        cout << 3.14 * x * x;
    }
};

#endif

