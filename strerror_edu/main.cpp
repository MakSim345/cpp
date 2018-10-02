#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "stdlib.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

inline float cube(const float s) {return s*s*s;}

int test_foo()
{
    std::cout << "test_foo() function called!\n";
    return 1;
}

void call_other(int t())
{
    std::cout << "call_other called! Now we'll call outside function:\n";
    t();
}

void call_other_empty(int ())
{
    std::cout << "call_other_empty called!\n";    
}

class App
{
public:
    int run()
    {
        std::cout << "Hello cruel world!\n";
        
        
        return 0;
    }
    ~App()
    {
        std::cout << "Good bye!\n";
    }

};

class CubeCalc
{
public:
    CubeCalc()
    {
        std::cout << "Hello! I will calculate a cube for you!\n";
    }
    ~CubeCalc()
    {
        std::cout << "Good bye!\n";
    }
    
    int run()
    {
        std::cout << "Enter cube dimention: ";
        std::cin >> side;
        
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
/*
        for (int i = 0; i < 1000000; i++)
        {
            long _number = my_rnd->getRandomNumber(100, 10000000);
            int _lenght_name =  my_rnd->getRandomNumber(3, 7);
            std::string _name = my_name->genPass(_lenght_name);

            pb->add_data_to_file(_name, _number);
        }
  */      

        cout << "Cube with side " << side << " is equal to " << calculation(side) << "\n";
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";    
        return 1;
    }

private:
    float side; 

    float calculation(float s)
    {
        return s*s*s;
    }

};

void test_array_error()
{
    char strHello[] = "Hello, world!";
    std::cout << "Enter an index: \n>";
     
    int nIndex;
    std::cin >> nIndex;     
    std::cout << "Letter #" << nIndex << " is -" << strHello[nIndex] << "- in " << strHello << std::endl; 
    // std::cout << strHello << std::endl; 
}

int &fun()
{
    static int x = 10;
    return x;
}

bool are_unique_characters(const std::string& str)
{
	std::vector<bool> char_set(256, false);

    // std::string str ("Test string");
    for (unsigned i=0; i<str.length(); ++i)
    {
        std::cout << str.at(i);
    }   

	std::cout << "\nInput str has size: " << str.size() << "\n";
    for (int i = 0; i < str.size(); ++i) 
    {
		int val = str.at(i);
        std::cout << "char - " << val << ": " << str.at(i) << "\n";
		if (char_set[val]) 
        {
			return false;
		}
		char_set[val] = true;
	}
	return true;
}
/*
#define BAS_PERROR(msg, err_code)\
  bas_perror(msg, err_code, __FILE__, __LINE__)

void bas_perror (const char* msg, int err_code, const char* filename,
                 unsigned long line_number);


void
bas_perror (const char* usr_msg, int err_code, const char* filename,
            unsigned long line_number)
{
  char sys_msg[64];

#ifdef _WIN32
  if ( strerror_s(sys_msg, sizeof sys_msg, err_code) != 0 )
  {
    // strncpy(sys_msg, "Unknown error", taille);
    sys_msg[sizeof sys_msg - 1] = '\0';
  }
#else
  if ( strerror_r(err_code, sys_msg, sizeof sys_msg) != 0 )
  {
    strncpy(sys_msg, "Unknown error", sizeof sys_msg);
    sys_msg[sizeof sys_msg - 1] = '\0';
  }
#endif

  fprintf(stderr, "%s: %s (debug information: file %s, at line %lu)\n",
          usr_msg, sys_msg, filename, line_number);
}
*/

/*
char *errno_str(int error)
{
  const int buffSize = 256;
  // char buf[buffSize];
  char* buf = new char[buffSize];
#ifdef _WIN32
    strerror_s(buf, buffSize, error);
    // printf ("errno_str buf = %s\n", buf);  
    for (int i =0; i < 15; i++)
    {
        printf ("buf = %c\n", buf[i]);
    }
#else
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
    strerror_r(error, buf, buffSize);
#else
    // res(strerror_r(error, buf, buffSize));
    strcpy (buf, strerror_r(error, buf, buffSize) );
#endif  

#endif
    return buf;
}
*/

/*
 string errno_str(int error)
{
    // char buf[64];
    char* buf = new char[64];
#ifdef _WIN32
    strerror_s(buf, sizeof(buf), error);    
    string res(buf);

    for (int i =0; i < 15; i++)
    {
        printf ("buf = %c\n", buf[i]);
    }
    printf ("errno_str buf = %s\n", res);
#else
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
    strerror_r(errno, buf, 256);
    string res(buf);
#else
    string res(strerror_r(errno, buf, 256));
#endif  
#endif  
    return res;
}
 **/
/*
std::vector<char> errno_str(int error)
{
    std::vector<char> res(64);
    // char* buf = new char[64];
    char buf[64];
#ifdef _WIN32
    strerror_s(&res[0], sizeof(buf), error);
    // string res(buf);
    // strcpy (&res[0], buf);

    //for (int i =0; i < 15; i++)
    //{
    //    printf ("buf = %c\n", buf[i]);
    //}
    printf ("-----errno_str buf = %s\n", buf);
#else
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
    strerror_r(errno, buf, 256);
    // string res(buf);
#else
    // string res(strerror_r(errno, buf, 256));
#endif  
#endif  
    return res;
}

enum
    {
        ERR_BUFF_SIZE = 256
    };
// declaration:
const SwToolkit::StringInst<ERR_BUFF_SIZE> errNumStr(int errNumP);

//definition:
const SwToolkit::StringInst<ERR_BUFF_SIZE> errNumStr(int errNumP)
{
    char aBuf[ERR_BUFF_SIZE + 1];
#ifdef _WIN32
    strerror_s(aBuf, ERR_BUFF_SIZE, errNumP);
    return SwToolkit::StringInst<ERR_BUFF_SIZE>(aBuf);
#else
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
    strerror_r(errNumP, aBuf, ERR_BUFF_SIZE);
    return SwToolkit::StringInst<ERR_BUFF_SIZE>(aBuf);
#else
    return SwToolkit::StringInst<ERR_BUFF_SIZE>(strerror_r(errNumP, aBuf, ERR_BUFF_SIZE));
#endif
#endif
}
*/

void func(char *&array)
{
    // ....
}

void errno_str(int error, char *buffer)
{
  const int buffSize = 256;
  // char buf[buffSize];
  // char* buf = new char[buffSize];
#ifdef _WIN32
    strerror_s(buffer, buffSize, error);
    // printf ("errno_str buf = %s\n", buf);  
    for (int i =0; i < 15; i++)
    {
        printf ("buf = %c\n", buffer[i]);
     }
#else
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
    //strerror_r(error, buf, buffSize);
#else
    // res(strerror_r(error, buf, buffSize));
    //strcpy (buf, strerror_r(error, buf, buffSize) );
#endif
#endif
}

int test_strerror()
{
  FILE * pFile;
  pFile = fopen ("unexist.ent","r");
  if (pFile == NULL)
  {
    //printf ("Error opening file unexist.ent. strerror says: %s\n", strerror(errno) );
    //printf("Digit code of an error: %d\n", errno);
    //perror ("Function perror: The following error occurred");
    //strerror_s
    char sys_msg[256];
    // strerror_s(sys_msg, sizeof(sys_msg), errno);
    // errno_str(errno);
    errno_str(errno, sys_msg);
    printf ("strerror_s says: %s\n", sys_msg );
    
    //printf ("errno_str says: %s\n", errno_str(errno));
  }
  return 0;
}




int main()
{
    // CubeCalc *cube_calc = new CubeCalc();
    //std::auto_ptr <App> app(new App());
    //app->run();    
    
    //test_foo();        
    //call_other(test_foo);
    // test_array_error();
    
    //fun() = 30;
    //cout << fun();
    // are_unique_characters("my_test");
    int res = test_strerror();

    return 1;
}
