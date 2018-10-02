/********************************************************************

  Savcor One Oy/YS
  VC++ / DJGPP
  Declaration: function converts an unsigned value to binary format,
  	           presents it in the char array sPtr. 
  Call: displayBits
  Input: Val - any value, like 0xE9; sPtr - result array of char.
  Returns: No returns, only result is changing an input array.
  10.02.2004 YS

*********************************************************************/
void displayBits(unsigned Val, char* sPtr)
{
 unsigned   c;
 //unsigned   dispMask=1<<31;
 unsigned   dispMask=1<<7;
 int        nBin, n;
 unsigned int ValueBits;
 int Byte1 = 8; 
 //int Byte2 = 16; 
 //int Byte4 = 32; 
 
 
 ValueBits = Byte1;
 n=0;
 for (c = 1; c<=ValueBits; c++)
 {
	 nBin = Val & dispMask ? 1 : 0 ;
	 if (nBin)
	   sPtr[n] = '1';
	 else
	   sPtr[n] = '0';
	 Val<<=1;
	 if ((c%8 == 0) )
		 {
		  sPtr[n+1] = ' ';
          n++;
		 }
	 n++;
 } 
}


  // How to use it:
	/*
  char sPtr[35];
  unsigned int Test
  displayBits(Test, sPtr);
  TRACE ("Test  = 0x%X, %s\n",Test, sPtr); 
  */