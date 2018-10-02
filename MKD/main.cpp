#include "utils.h"
#include "info.h"
#include "gen.h"

/*
 * the application run by:
   mkd.exe <ADD/WRITE> <filename> [message]
   mkd.exe ADD backup.log "Files are copied successfully"
   mkd.exe WRITE run.bat
*/

int main(int argc, char *argv[ ])
{
    FILE *file;

    if (argc <= 1)
    {
        PrintIntroduction(2);
        return 0;
    }

    if (strcmp(argv[1], "START") ==0)
    {
        char load_string[250];
        char default_file[50];
        time_t system_time;
        time( &system_time );
        printf( "The time is %s\n", ctime( &system_time ) );
        strcpy(load_string, ctime( &system_time ) ); // put time to log file
        
        printf ("argc: %d\n", argc);
        if (argc >= 3)
        {
            strcpy(default_file, argv[3]);
            printf ("File to open: %s\n", default_file);
        }
        else
        {
            strcpy(default_file, "tmp1234.txt");
            printf ("File to open (default): %s\n", default_file);
        }       
        
        file = fopen(default_file, "a" );
            
        if( file != 0 )
            fwrite(load_string, strlen(load_string), 1, file);
        else
            printf( "Error saving to file\n" );
        fclose(file);
        return 1;
    }

    if (strcmp(argv[1], "ADD") ==0)
    {
        char load_string[250];
        time_t ltime;
        time( &ltime );
        printf( "The time is %s\n", ctime( &ltime ) );
        strcpy(load_string, ctime( &ltime ) ); //time to log file
        
        // printf ("argc: %d\n", argc);
        if (argc >= 4)
        {
            strcat(load_string, argv[3]); //message to log file
        }

        strcat(load_string, "\n"); //
        file = fopen(argv[2], "a" ); //argv[2] ==filename
        if( file != 0 )
            fwrite(load_string, strlen(load_string), 1, file );
        else
            printf( "Error saving to file\n" );
        fclose(file);
        return 1;
    }
    else if (strcmp(argv[1], "WRITE")==0)
    {
        //char load_string[27] = "call backup.bat ";
        char buffDR[37] = "call backup.bat ";
        char buffer[20];

        _strdate(buffer); // put current date to string
        // PutDateBuf(buffer);
        
        for (int i=0; i < (int)strlen(buffer); i++)
        {
            if (buffer[i] == '/') buffer[i] = '_';
        }
        
        printf ("Today: %s\n", buffer);

        strcat(buffDR, buffer );//create string " call backup.bat XX_XX_XX"
        printf ("Result string: %s\n", buffDR);

        printf ("File to open: %s\n", argv[2]);
        file = fopen(argv[2], "w" ); //argv[2] ==filename, "w+" == for writing with erasing previous
        if( file != 0 )
        {
            fwrite(buffDR, strlen(buffDR), 1, file );
            printf ("write to file %s - 1\n", argv[2]);
            fwrite(" ", 1, 1, file );
            printf ("write to file %s - 2\n", argv[2]);
            fwrite(argv[3], strlen(argv[3]), 1, file );
            printf ("write to file %s - 3\n", argv[2]);
        }
        else
        {
            printf ("File %s not found !\n", argv[2]);
        }

        fclose(file);
        return 1;
    }
    else if ((strcmp(argv[1], "VER")==0) ||(strcmp(argv[1], "ver")==0) )
    {
        printf ("MKD.EXE - version 3.0.2. 2013.\n");
        return 1;
    }
    PrintIntroduction(0);
    // printf ("Arguments must be WRITE or ADD! Nothing has been done. Application complete.\n");
    return 0;
}

