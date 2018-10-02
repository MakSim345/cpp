#pragma once

/*********************************************************************

  utils.h  
  01.10.2017 Initial coding YS 
  
**********************************************************************/
class NAND
{
public:
    NAND();   
    
    int a;
    int b;

    int out;
    void run();

private:
    bool toBool(int toConvert);
    int toInt(bool toConvert);

    bool b_a;
    bool b_b;
    bool b_out;    
};


class NOT
{
public:
    NOT();

    int in;    

    int out;
    void run();

private:
    NAND* nand;

    //bool toBool(int toConvert);
    //int toInt(bool toConvert);

    bool b_a;
    bool b_b;
    bool b_out;    
};