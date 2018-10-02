#include "utils.h"
#include "gen.h"

extern long g_lTimeTick;

#ifdef ZPCHECK    
            
extern FILE *inf_f;     
extern  FILE *zip_f;

int File_Checking_Routine(char * zip_file_name, char * info_file_name, int write_to_inf)
{
 if (0 == write_to_inf)
 {
  if (access(info_file_name, 0) != 0)  //info-file  does not exist
   {
    //file does not exist, so we can not read a timestamp from there...     
      printf ("The info-file %s does not exist, I can not read a timestamp from there!\n", info_file_name);
    return(0);
   }
 }
   if (access(zip_file_name, 0) != 0)  // zip-file  does not exist
   {
    //file does not exist, nothing to compare
      printf ("ZIP-file '%s' does not exist, I can not read his timestamp!\n", zip_file_name);
    return(0);
    }  
  // next find the current time stamp of the file
 if (0 == write_to_inf)
  {
   if ((inf_f = fopen(info_file_name, "rt")) == NULL) 
    {
    // file is corrupted or something....
    printf ("Info-file %s does not exist, corrupted or something..!\n", info_file_name);
    return(0);
    }
  }
  else
  {
   if ((inf_f = fopen(info_file_name, "wt")) == NULL) 
    {
    // file is corrupted or something....
    printf ("Info-file %s does not exist, corrupted or something..!\n", info_file_name);
    return(0);
    }
  }  
  if ((zip_f = fopen(zip_file_name, "rt")) == NULL) 
    {
    // file is corrupted or something....
    printf ("ZIP-file %s does not exist, corrupted or something..!\n", zip_file_name);   
    if(inf_f)
     fclose (inf_f);  // only one file is opened for now.
    return(0);
    }  
    
  return 1;
}


/********************************************************************
  Declaration:  Parse date and time from string YYYYMMDDHHMMSS
  Call: ParseDate(DateTime,year,month,day,hour,min,secs)
  Input: char * DateTime
     int year, int * month, int * day,
     int * hour, int * min, int * secs
  Returns: void
*********************************************************************/
void   ParseDate(char *DateTime,int * year ,int * month,int * day ,
         int * hour, int * mins,int  * secs)

  {
  char tmp[5];

  // year

  tmp[0]=DateTime[0];
  tmp[1]=DateTime[1];
  tmp[2]=DateTime[2];
  tmp[3]=DateTime[3];
  tmp[4]=0;

  *year=atoi(tmp);

  // month

  tmp[0]=DateTime[4];
  tmp[1]=DateTime[5];
  tmp[2]=0;
  *month=atoi(tmp);

  // day
  tmp[0]=DateTime[6];
  tmp[1]=DateTime[7];
  tmp[2]=0;
  *day = atoi(tmp);

  // hour
  tmp[0]=DateTime[8];
  tmp[1]=DateTime[9];
  tmp[2]=0;
  *hour =atoi(tmp);

  // minutes
  tmp[0]=DateTime[10];
  tmp[1]=DateTime[11];
  tmp[2]=0;
  *mins=atoi(tmp);

  // seconds
  tmp[0]=DateTime[10];
  tmp[1]=DateTime[11];
  tmp[2]=0;
  *secs=atoi(tmp);

  }

void  CloseOpenFiles()
{
  if (zip_f)
   fclose(zip_f);    
  if(inf_f)
   fclose (inf_f);  
}
#endif // ZPCHECK    
/********************************************************************
  Declaration: Put current date to string
  Call: SendTSBMsg(MoveType, MsgId)
  Input: pointer to string
  Returns: 1 if all ok, 0 if error.
  Initial Coding: 03.11.2005 YS

*********************************************************************/
int PutDateBuf(char* buffer)
{
    time_t timer;
    struct tm y2k;
    double seconds;

    for (int i=0; i < (int)strlen(buffer); i++)
    {
        // printf ("%s\n", buffer);
        // buffer[i] = i;
    }

#ifdef YS_TEST_2202932 
    date *str_dt;
    char MonT[5];
    // int DayT;
  
    getdate(str_dt);

    //printf ("str_dt->da_day= %d\n ", str_dt->da_day);
    //printf ("str_dt->da_mon= %d\n ", str_dt->da_mon);
    //printf ("str_dt->da_year= %d\n ", str_dt->da_year);

    switch ( int(str_dt->da_mon) )
    {
     case 1:
        sprintf(MonT, "%s", "JAN");
        break;
    case 2:
             sprintf(MonT, "%s", "FEB");
        break;
    case 3:
          sprintf(MonT, "%s", "MAR");
        break;
    case 4:
          sprintf(MonT, "%s", "APR");
        break;
    case 5:
          sprintf(MonT, "%s", "MAY");
        break;
    case 6:
          sprintf(MonT, "%s", "JUN");
        break;
    case 7:
        sprintf(MonT, "%s", "JUL");
        break;
    case 8:
        sprintf(MonT, "%s", "AUG");
        break;
    case 9:
        sprintf(MonT, "%s", "SEP");
        break;
    case 10:
        sprintf(MonT, "%s", "OCT");
        break;
    case 11:
        sprintf(MonT, "%s", "NOV");
        break;
    case 12:
        sprintf(MonT, "%s", "DEC");
        break;
  
    default:
        printf("Unknown month (%d)\n", str_dt->da_mon);
        sprintf(buffer, "%d_%d_%d", 0, 0, 0);  
        return 1;
        break;
}  // end of switch
    
    // printf("int (str_dt->da_day) = %d\n", int (str_dt->da_day));
    if (int(str_dt->da_day) < 10 )        
    {            
     sprintf(buffer, "0%d_%s_%d",str_dt->da_day, MonT, str_dt->da_year);
    }
    else
    {    
     sprintf(buffer, "%d_%s_%d",str_dt->da_day, MonT, str_dt->da_year);        
    }
    //printf ("PutDateBuf: buffer = %s\n ", buffer);
#endif
  return 0;
}
