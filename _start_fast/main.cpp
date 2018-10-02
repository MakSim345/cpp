#include <iostream>
#include "utils.h"

inline float cube (const float s) {return s*s*s;}

using namespace std;

void cube_calc();

class Foo
{
    public:
    Foo() { std::cout << "Foo constructor" << std::endl; }
    virtual ~Foo() { std::cout << "Foo destructor" << std::endl; }
};
class Bar : public Foo
{
    public:
    Bar() { std::cout << "Bar constructor" << std::endl; }
    virtual ~Bar() { std::cout << "Bar destructor" << std::endl; }
};


int test_constructors()
{    
    Foo* bar;
    bar = new Bar();
    delete bar;

    Foo foo = Foo();
    return 1;
}


void cube_calc()
{
    // print_message();
    cout << "Enter cube dimention: " ;
    float side;
    cin >> side;
    cout << "Cube with side " << side << " is equal to " << cube(side) << endl;
}

void _division()
{
    int a = 123;
    int b = 100;
    int i = a % b;
    printf("result %d DIV_10 %d = %d\n",a , b, i);
    float res = a / 10.0;
    printf("result %d DIV %d = %f\n",a , b, res);
}

void test_switch()
{
    int a = 3;
    int b = 100;
    switch (a)
	{	
        case 1:
        case 2:
        case 3:
        case 123:
            printf ("result = %d\n", a);
            break;
        case 4:
        case 5:
            
        /*
        case DRI_ALSRC_ENT_NO_SENSOR : // break intentionally missing
	    case DRI_ALSRC_ENT_CABLE_OFF : // break intentionally missing
	    case DRI_ALSRC_ENT_SENSOR_OFF : // break intentionally missing
	    case DRI_ALSRC_ENT_SENSOR_CHK_FAILED : // break intentionally missing
	    case DRI_ALSRC_ENT_REPLACE_SENSOR : // break intentionally missing
	    case DRI_ALSRC_BIS_MODULE_ERROR : // break intentionally missing
	    case DRI_ALSRC_BIS_DSC_ERROR : // break intentionally missing
	    case DRI_ALSRC_BIS_SENSOR_DISCONN : // break intentionally missing
	    case DRI_ALSRC_BIS_CABLE_DISCONN : // break intentionally missing
	    case DRI_ALSRC_BIS_BAD_IMPEDANCE : // break intentionally missing
	    case DRI_ALSRC_BIS_SENSOR_FAIL : // break intentionally missing
	    case DRI_ALSRC_SPO2_INCOMPATIBLE_PROBE : // break intentionally missing
	    case DRI_ALSRC_ENT_RE : // break intentionally missing
	    case DRI_ALSRC_ENT_SE : // break intentionally missing
	    case DRI_ALSRC_BIS : // break intentionally missing
		    if (p_nFilterDriLevel <= DRI_LEVEL_01)
		    {
    //			MSF_LOG_PMSG("Alarm source filtered");
			    p_rAlSourceId = toLittleEndian16bit(DRI_ALSRC_UNKNOWN);
		    }
		    break;
        */
    default :
		// do nothing
		break;   
    }   
}

enum test_me 
{
    ACTIVE = 100,
    PRECONDITION_MET
};
    
class RState
{
public:
    RState(): _internal_value(0) { std::cout << "RState constructor" << std::endl; }
    virtual ~RState() { std::cout << "RState destructor" << std::endl; }
    void setValue(int i) { _internal_value=i; };
    void printValue() { std::cout << "RState value: " << _internal_value << std::endl; }
private:
   int _internal_value;     
};

bool checkAlarmCondition()
{
    return true;
    // return false;
}

int test_ternar()
{   
    RState rStateM;
    rStateM.printValue();
    rStateM.setValue(checkAlarmCondition() ? ACTIVE : PRECONDITION_MET); 
    rStateM.printValue();
    return 1;
}

bool update1()
{
    std::cout<<"update-1"<<std::endl;
    return false;
}

bool update2()
{
    std::cout<<"update-2"<<std::endl;
    return true;
}


int test_boolean()
{

    bool updatedSuccessfully = update1() && update2();
    return 0;
}


int main (void)
{
    std::cout << "Hello, world from line: " << __LINE__ << ", in file: " << __FILE__ "\n" ;
    // test_ternar();
    test_boolean();
    return 0;

}



