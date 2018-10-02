/*********************************************************************

  virt_class.h
	communication incapsulate
  12.12.2007 Initial coding

**********************************************************************/
#ifndef _VIRT_CLASS_H_
#define _VIRT_CLASS_H_	
	

class VirtualDriver
{

public:
    VirtualDriver();
	 ~VirtualDriver();
    //virtual void Start();
		//virtual void PrintMyVal();
		virtual void SetInteger(int);
		//virtual int GetInteger(); 
    
private:
  int m_IntegerN;
};


class InherDriverA : public VirtualDriver
{
public:
    InherDriverA();
	 ~InherDriverA();
    //void Start();
		//void PrintMyVal();
		void SetInteger(int);
		//virtual int GetInteger();   	  
    
private:
  int m_IntegerN;
};


#endif // _VIRT_CLASS_H_
