#include "gen.h"

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \nLet's make some product...\n";

        print_num(3,2,3,4);
        // print("3", 2, 3, 4);
        int av_sum = average_val(1, 2, 3, 4, 5, 89, 90, -12);
        printf("\nAverage sum of parameters: %d\n\n", av_sum);
        return 0;
    }

    void  print(const char *str, ...)
    /*str has the number of integers passed*/
    {
        int i = 1;
        int num_count = atoi(str);
        int *num = (int *)&str;

        for(i; i<=num_count; i++)
        {
            printf("%d ", *(num+i));
        }
    }

    void print_num(int num_count, ...)
    /*num_count contains the number of integers passed*/
    {
        int i=1;
        int *num = &num_count;

        for(i; i<=num_count; i++)
        {
            printf("%d ", *(num+i));
        }
    }

    int average_val(int first_param, ...)
    {
      int i =   0;
      int j =   0;
      int sum = 0;
      int ret_val = 0;

      va_list arg_ptr;

      va_start(arg_ptr, first_param);  //  set arg_ptr to first parameter from threedot

      if (first_param != -1)
      {
          //  is list empty?
          sum = first_param;
          std::cout << "sum = " << sum << "\n";
      }
      else
      {
          return (0);
      }

      j++;

      // get next param and check if list empty:
      while ((i = va_arg(arg_ptr, int)) != -1)
      {
        sum += i;
        std::cout << "sum = " << sum << "\n";
        j++;
      }

      va_end(arg_ptr); // close list of parameters

      ret_val = sum/j;
      return ret_val;
   }


    ~App()
    {
        std::cout << "Good bye!\n";
    }

};

int main(int argc, char *argv[], char *envp[])
{
    int RValue = false;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;
    int arraySize = 2000;

    printf ("main - start\n");

    const char* ClassFileNaMe = "allegro.log";

    //std::auto_ptr <CubeCalc> cube_calc(new CubeCalc());

    std::auto_ptr <App> bakery(new App());
    try
    {
        bakery->Run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }

    // return 0;
    /*
    __try
    {
        fail();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        memento();
    }
    */

//*************MAIN LOOP*****************//
cout << "\n$ > Press any key to exit." << std::endl;
do
{
    //This is simple Windows way:
    Sleep(55);
    // active_matrix->run_matrix();

   //nResult = produceRND();
   //printf ("1-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

   //nResult = produceRND();
   //printf ("2-Time: %ld. RND: %d\n", _time->Get1msTimeMS(), nResult);

   // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
        NewChar=(unsigned char)_getch();
        RValue = true;
        if ((NewChar & 0xff) == 24)  // CTRL-X   pressed
        {
            RValue = true; // END mark
        }
        if (NewChar == 'd')  // pressed
        {
            if (1 == CaptureModeHex)
                CaptureModeHex = 1;
            else
                CaptureModeHex = 0;
        }
    }
} while (!RValue);
printf ("Application complete.\n");
return 0;
}


