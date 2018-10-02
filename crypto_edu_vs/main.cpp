#include "gen.h"
#include "Binary.h"
#include "msg_print.h"
#include "gen.h"
#include <Windows.h>


typedef enum
{
    SELFTEST_MODE,
    CHECKOUT_MODE,
    NORMAL_MODE
} FIB_MODE;

class App
{
public:
    int Run()
    {
        if (!isAllParamsOK())
            return 0;

        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
        
        // data_file.get(crypted_char);

        while ((crypted_char = getc(fi)) != EOF)
        {
            if (nPrintValue)
            {
                printf ("crypted_char = %d, key = %d\n", crypted_char, *tmp_crypto_key);
            }
            
            if (!*tmp_crypto_key)
            {
                tmp_crypto_key = main_crypto_key;
            }
            
            //printf ("before XOR: c = %d\n", c);
            dispBits((unsigned)crypted_char, nPrintValue);
            
            char next_char_from_key = *(tmp_crypto_key++);
            crypted_char^= next_char_from_key;
            
            dispBits((unsigned)next_char_from_key, nPrintValue);
            //printf ("after XOR: c = %d\n", c);
            
            dispBits((unsigned)crypted_char, nPrintValue);
            
            putc(crypted_char, fo); 
            
            iter_counter++;
        }       
        
        fclose (fo);
        fclose (fi);

        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
        
        /*
        Item *first = 0;
        Item *p;
        std::cout << sizeof(first) << "\n";
        int i;
        for (int j = 0; j < 5; j++)
        {
            // std::cin >> i;
            i = this->get_rnd_number();
            std::cout << "Enter new number: " << i << "\n";
            if (!i) break;

            p = new Item;
            p->info = i;

            p->next = first;
            first = p;
        }

        p = first;
        while (p)
        {
            //std::cout << "p->Item = " << p->Item << "\n";
            // std::cout << hex << "0x" << p << " - ";
            //std::cout << sizeof(p) << "\n";
            std::cout << p << " - ";
            std::cout << "p->info = 0x" << p->info << "\n";
            p = p->next;
        }
        */

        /*
        * long num_to_search = 345345325;
        std::cout << "search by number " << num_to_search << " - "<< search_by_number(num_to_search) << "\n";
        Number t;
        std::cout << "\nEnter new name:\n";
        cin >> t.name;
        
        std::cout << "Enter new number:\n";
        cin >> t.number;
        
        add_data_to_file(t.name, atol(t.number.c_str()));
        */
        printf ("\nCoding complete. There was %d iterations\n", iter_counter);
        // system("pause");
        return 0;
    }
    
    int isAllParamsOK()
    {
        if (*main_crypto_key == '\0') 
        {
            std::cout << "ERROR: No crypto key has been set! Application completed.\n";
            return 0; // no key!
        }

        if (NULL == (fi = fopen(this->filename_source.c_str(), "rb")))
        {
            std::cout << "ERROR: No file '" << filename_source << "' to crypt! Application completed.\n";
            return 0; // no file to read!
        }
        
        if (NULL == (fo = fopen(this->filename_result.c_str(), "wb")))
        {
            std::cout << "ERROR: No file to write result! Application completed.\n";
            return 0; // no file to write!
        }

        return 1;
    }

    bool open_file_to_read()
    {
        // fi = fopen(this->filename_source.c_str(), "rb");
        // if (NULL == (fo = fopen(this->filename_result.c_str(), "wb")))        
        //data_file.open (this->filename_source.c_str(), ios::app);
        
        // std::cout << "Writing this to a file.\n";    

        // data_file << name << " " << number << std::endl;;
        //return data_file.is_open(); 
        return true;
    }

    App(int argc, char *argv[]):
        iter_counter(0)
    {
        if (argc < 2)
        {
            argc = 4;
            // char *argv[5];
            argv[0] = "app";
            argv[1] = "1234ABBA";
            argv[2] = "tst.txt";
            argv[3] = "tres.txt";
            argv[4] = NULL;
        }
        
        std::cout << "Hello crypted world! \n";
        
        FIB_MODE _my_var = FIB_MODE::NORMAL_MODE;

        init_random_gen();
        mp = new msg_print();

        if (argc <= 1)
        {
            mp->PrintErrorMessage();
            // return 0;
        }
        
        else 
        {
            mp->PrintInfoMessage();
        }

        if (argv[4] == NULL)
        {
            nPrintValue = 0;
        }

        else // if (argv[4] == 1)
        { 
            nPrintValue = 1;
        }

        main_crypto_key = argv[1];
        tmp_crypto_key  = argv[1];
        filename_source = argv[2];
        filename_result = argv[3];
        
        if (nPrintValue)
        {
            printf ("Program started. The main crypto key = %s \n", main_crypto_key);
        }
        else 
        {
            printf ("Program started.\n");
        }
   }

    void init_random_gen()
    {
        srand((unsigned)time(0));
        rand();
        return;
    }

    int get_rnd_number(int iMin=0, int iMax=101)
    {
        int _tmp_rand_value = 0;
        int _retValue = 0;

        _tmp_rand_value = rand();
        _retValue = ( iMin + int( (iMax - iMin + 1) * _tmp_rand_value /(RAND_MAX + 1.0) ) );
        return _retValue;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

private:
    int nPrintValue;
    long iter_counter;
    char *main_crypto_key;
    char *tmp_crypto_key;
    msg_print *mp;
    std::string filename_source;
    std::string filename_result;
    FILE *fi;
    FILE *fo;        
    //std::ofstream result_file;
    //std::ifstream data_file;
    int crypted_char;
};

int main (int argc, char *argv[])
{   
    
    std::auto_ptr <App> crypto_app(new App(argc, argv));
    
    try
    {
        crypto_app->Run();
    }
    catch(std::runtime_error)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER\n";
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "EXCEPTION_EXECUTE_HANDLER has number - " << EXCEPTION_EXECUTE_HANDLER << "\n";
    }    
    */
    system ("PAUSE");
    return 1;
}
