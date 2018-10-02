#include "gen.h"
#include "linked_list.h"
#include "crc_calc.h"
#include <Windows.h>

class App
{
public:
    int Run()
    {
        std::cout << "Hello cruel world! \n";
        
        char buff[ 10 ];
        char filename[ 256 ];
        char checksumhex[ SLC_FCRC_MAXHEXSIZE ]; //0-terminated    

        do
        {            
            //Get the file name from the user
            std::cout << "\nEnter a file name:\n";
            // cin.getline( filename, 256 );        
            std::cin >> filename;
        
            // readFileToMemory(filename);
            // readFileLoop(filename);
            readStdFileLoop(filename);

            //Calculate CRC32 checksum using Calculate
            //if(Calculate_CRC32_Example1( filename, checksumhex ) )
            //    cout << "\nChecksum calculated using Calculate:        " << checksumhex;

            //Calculate CRC32 checksum using Update and Final
            //if( Calculate_CRC32_Example2( filename, checksumhex ) )
            //    cout << "\nChecksum calculated using Update and Final: " << checksumhex;        

            //Continue?
            std::cout << "\nContinue (Y/N)?";
            cin >> buff;
        
        } while ( *buff == 'y' || *buff == 'Y' ); 
        
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
        return 0;
    }

    void readFileToMemory(std::string filename)
    {            
        FILE *fs = fopen(filename.c_str(), "rb");   //open file for reading
        long bufsize = FileSize(fs);
        long result;
        
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
        
        std::cout << "Allocate " << bufsize << " bytes.\n";
        unsigned char *buffer = new unsigned char[bufsize];
        
        result = fread (buffer, 1, bufsize, fs);
        fclose(fs);
                        
        int crc = CalculateBlockCRC32(bufsize, buffer);
        // crc = Get_CRC(buffer, bufsize);
        printf("\nCRC: 0x%X\n",crc);
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
    }
    
    
    double readStdFileLoop(string s_logFileName)
    {
        int c;
        unsigned long charCounter = 0;
        std::ifstream data_file;
        char new_char;
        
        data_file.open (s_logFileName.c_str(), ios::binary);
        
        // data_file << name << " " << number << std::endl;;
        
        //return data_file.is_open(); 
        //
        // FILE* pStream = fopen(s_logFileName.c_str(), "a");
        // FILE *fi = fopen(s_logFileName.c_str(), "rb");
    
        //std::cout << "readFileLoop - after open file... \n";
    
        if ( !data_file.is_open() )
        {
            std::cout << "Unable to open file " << s_logFileName << " !!\n";
            return 0;
        }
        else
        {
            std::cout << "File " << s_logFileName << " was open. Processing.....\n";
        }
        
        int crc = 0;
        unsigned long ulTemp1, ulTemp2;
        unsigned long ulCRC = 0;
         
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";
        
        // TODO:

        while ( data_file >> new_char )
        // while ( !data_file.eof() )
        // while ( (c= getc(fi)) != EOF )
        {
            // data_file.get(new_char);
            // if (nPrintValue)
            // printf ("c = %d, *cp = %d\n", c, *cp);
            // BitCalculation((unsigned)c, nPrintValue, &ctrONE, &ctrZERO);
            
            ulTemp1 = ( ulCRC>>8 ) & 0x00FFFFFFL;
            ulTemp2 = CRC32Value( ((int)ulCRC ^ new_char) & 0xFF );
            ulCRC = ulTemp1 ^ ulTemp2;

            //crc ^= CRC32Value(c);
            
            charCounter++;
            // std::cout << "charCounter = " << charCounter <<  ". Char = " << new_char << "\n";
            // Sleep(3);
        }
        
        //std::time(&end_time);
        //std::cout << "\nTime diff: " << std::difftime(end_time, start_time) << "sec.\n";
        
        printf("\nCRC: 0x%X\n", ulCRC);
        std::cout << "Iterations: " << charCounter << "\n";
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
        

        // fclose (fi);
        data_file.close();
        return charCounter;
    }

    double readFileLoop(string s_logFileName)
    {
        int c;
        unsigned long charCounter = 0;
        
        // FILE* pStream = fopen(s_logFileName.c_str(), "a");
        FILE *fi = fopen(s_logFileName.c_str(), "rb");
    
        //std::cout << "readFileLoop - after open file... \n";
    
        if (!fi)
        {
            std::cout << "Unable to open file " << s_logFileName << " !!\n";
            return 0;
        }
        else
        {
            std::cout << "File " << s_logFileName << " was open. Processing.....\n";
        }
        
        int crc = 0;
        unsigned long ulTemp1, ulTemp2;
        unsigned long ulCRC = 0;
         
        long a = std::clock();
        std::cout << "Time Start: " << a << "\n";

        while ((c= getc(fi)) != EOF)
        {
            //if (nPrintValue)
            //printf ("c = %d, *cp = %d\n", c, *cp);
            // BitCalculation((unsigned)c, nPrintValue, &ctrONE, &ctrZERO);
            
            ulTemp1 = ( ulCRC>>8 ) & 0x00FFFFFFL;
            ulTemp2 = CRC32Value( ((int)ulCRC ^ c) & 0xFF );
            ulCRC = ulTemp1 ^ ulTemp2;

            //crc ^= CRC32Value(c);
            
            charCounter++;
            // Sleep(3);
        }
        
        //std::time(&end_time);
        //std::cout << "\nTime diff: " << std::difftime(end_time, start_time) << "sec.\n";
        printf("\nCRC: 0x%X\n", ulCRC);
        std::cout << "Iterations: " << charCounter << "\n";
        
        long b = std::clock();
        std::cout << "Time END: " << b << "\n\n";
        std::cout << "Time TOTAL: " << (b-a)/1000.0 << " sec.\n";
        

        fclose (fi);
        return charCounter;
    }

    App()
    {
        init_random_gen();
    }
    
    long FileSize(FILE *input)
    {

        long fileSizeBytes;
        fseek(input, 0, SEEK_END);
        fileSizeBytes = ftell(input);
        fseek(input, 0, SEEK_SET);
        
        return fileSizeBytes;
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

    bool calc_file_crc( const char* filename, char* checksumhex)
    {
        //Generate CRC32 checksum using Update and Final
        fstream file( filename, ios::in | ios::binary );
        if( !file )
        {
            std::cout << "\nCould not open file: " << filename;
            return false;
        }    

        const unsigned int BUFF_SIZE = 1024;
        unsigned char buff[ BUFF_SIZE ];    

        //Instantiate a CFastCRC32 object
        //CFastCRC32 crc;    
    
        //Calculate the checksum by calling Update for each block of the file
        while( !file.eof() )
        {
            file.read( ( char* )buff, BUFF_SIZE );
            //crc.Update( buff, file.gcount() );
        }    
    
        //Do final changes and get the checksum
        //unsigned long checksum = crc.Final(); // Final reinitializes crc object
    
        //Get the hexadecimal representation of checksum
        //SL_FCRC_ConvertToHex32( checksumhex, checksum, 0 );    
    
        file.close();    

        return true;
    }

    ~App()
    {
        std::cout << "\nGood bye!\n";
    }

};

int main()
{
    std::auto_ptr <App> my_maps(new App());
    try
    {
        my_maps->Run();
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
    return 1;
}
