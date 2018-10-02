/*
 * Example from: http://simplestcodings.blogspot.co.uk/2014/10/facade-design-pattern-in-cpp.html
 * */

#include "gen.h"

#include "Courier.h"
#include "Vendor.h"
#include "OrderingTeam.h"
#include "OnlineShoppingFacade.h"


long g_lTimeTick = 0;

std::string _stateToStrCourier[]   = { "Received", "VerifyReachbility", "AssignPerson", 
                                       "DispatchPackage", "GetDeliveryConfirmation", "Complete"};
std::string _stateToStrVendor[]    = { "Received", "VerifyInventory", "GetItemFromWareHouse", 
                                       "PackItem", "ContactCourier", "Complete"};
std::string _stateToStrOrderTeam[] = { "Received", "VerifyPayment", "ContactVendor", "Complete"};
 
int main(int argc, char *argv[], char *envp[]) 
{
    long LastTimeIn=0;    
    long LastTimeInMS = 0;    
    int RValue = false;
    int Counter=0;  
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;

    printf ("main - start\n");
    
#ifdef FILE_OUTPUT
    int nOpenFileToken = 0;
    char *FileNameF = "TimeSt.log";
    FILE *fi = NULL; 
 
 // open the file for input:    
 if ( (fi = fopen(FileNameF, "a+") ) != NULL)
  {
  // printf ("file %s was open successfully\n", FileNameF);
   nOpenFileToken = 1;
  }
 else
  {
   printf ("file %s was not open\n", FileNameF);
   getchar(); // pause
   nOpenFileToken = 0;
  }
      
  fprintf(fi, "Start time: %d\n", Get1msTime());
#endif// FILE_OUTPUT    

    OnlineShoppingFacade onlinereq;  
    onlinereq.submitRequest();  
    /* Keep checking until order is complete */
    while (!onlinereq.checkStatus());
     
    std::cout << "Order completed after " << onlinereq.numFUPs() << " followups" << std::endl;
  
 //*************WAIT LOOP*****************//
 do 
 {
    //This is simple Windows way:
    Sleep(1000);
   
    // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {   
     NewChar=(unsigned char)_getch();
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
}while (!RValue);  
 
printf ("Application complete.\n");
return 0;
}
