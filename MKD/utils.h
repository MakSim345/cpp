#ifndef UTILS_H
	#define UTILS_H
/*********************************************************************

  utils.h  
  		
*********************************************************************/
		
int PutDateBuf(char* buffer);

#ifdef ZPCHECK	
 int File_Checking_Routine(char * zip_file_name, char * info_file_name, int write_to_inf);

 void CloseOpenFiles(void);
 void ParseDate(char*, int*, int*, int*, int*, int *,int* );
 long  Get1msTime(void);
 char* PrintTime(void); // return string with time
 void PrintIntroduction();
#endif
			
#endif //UTILS_H	