/******************************************************************
  Savcor IT Oy/YS
  Declaration: compare given TimeStamp with the active TimeStamp
               nd set the global flag variable to TRUE(or calls 
               an appr. function) if there are 3 (4) equal TimeStamps. 
               In case the given TimeStamp bigger than the active, it's 
               become to be active and number first.
  Call: TopPickTimeStamp (unsigned long)
  Input: unsigned long, milliseconds
  Returns:  
  30.10.2002 Initial coding  YS
*****************************************************************/
void TopPickTimeStamp(unsigned short MsgID, unsigned long Milliseconds)
{
 static int nTSCounter = 0;
 static unsigned long ulActiveTStamp = 0;
 static TimeStamp TSArray[MESSG_NUM];
 //*********************************
 //static unsigned long ulDEBUGTStamp = 0;
 //char* DeBChar = "ABCDEFGHFF"; 
 //**********************************
 int i, j;

 BOOL bFlag1=FALSE; 
 
  //************DEBUG ONLY*************************
  //TRACE ("\nMsgID = %d, ulActiveTStamp = %d, Milliseconds = %d, nTSCounter =%d, ulDEBUGTStamp =%d\n", MsgID, ulActiveTStamp, Milliseconds, nTSCounter, ulDEBUGTStamp);
     //TRACE ("Before TxData\n");
    //i=TxData(2, DeBChar, 10);    
  //return;
    //**********************************************
 
    if (Milliseconds > ulActiveTStamp)
 {
   ulActiveTStamp = Milliseconds;    
     for (i=0; i<MESSG_NUM; i++)
        {
         TSArray[i].bValidate = FALSE;
         TSArray[i].MsgID  = 0;
         TSArray[i].Milliseconds  = 0;
        }
    
  TSArray[0].bValidate=TRUE;
  TSArray[0].MsgID = MsgID;
  TSArray[0].Milliseconds = Milliseconds;    
    nTSCounter =1;
 }
 else if ((Milliseconds == ulActiveTStamp) && nTSCounter)
 {  
     for (j=0; j<MESSG_NUM; j++)
     {
         if (TSArray[j].MsgID == MsgID)
           bFlag1 = TRUE;
      }
     
     if (!bFlag1)
     {
      for (i=0; i<MESSG_NUM; i++)
            {        
              if (!TSArray[i].bValidate)
                {                
                 TSArray[i].bValidate = TRUE;
         TSArray[i].MsgID = MsgID;
         TSArray[i].Milliseconds = Milliseconds;
               nTSCounter++;
               break;
                }
            }
     }    
 } 
 if (nTSCounter>=MESSG_NUM)
 {
    //TRACE ("****SET THE GLOBAL FLAG****, ulActiveTStamp =%d\n", ulActiveTStamp);
    CalcPos();
    nTSCounter =0;
    ulActiveTStamp =0;        
 } 
}

/********************************************************************

  Savcor IT Oy/JLM, YS.
  Borland TURBO C++ 3.0
  Declaration: Assemble and interpret received data from GPS.
  Call: Packet Ready=InterpretGPSData(GPSNbr,NbrOfBytes,Data)
  Input:int GPSNbr
        int NbrOfBytes, char * Data
  Returns: int if packet ready, FALSE if packet not yet received
  13.11.2000 Initial coding JLM, extend: YS

*********************************************************************/

int InterpretGPSData(int GPSNbr, int NbrOfBytes,char * data)
  {

  unsigned long RxCRC;
    unsigned long CRC;
  static unsigned char tmps[2][RECV_DATA_BUF_SIZE];
  BESTPOS tmpBPOS;
    BESTXYZ tmpBXYZ;
  int RetVal=FALSE;    
    static int nMsgLenght[2];
  static int nMessageID[2];
    static int nRNGCount[2];
    static int nRNGArrCount[2];        
    char cXYZTmpBuf[24][XYZ_TMP_BUFF_SIZE]; // :68
    char cRANGETmpBuf[2][24][RNG_BUFF_SIZE]; // 44
    char cSAV_RNGmpBuf[12][SAV_RNG_TMP_BUFF_SIZE]; // :16
    char cTMP_Buf[600];
    static char cSend_Out_Buf[2][RECV_DATA_BUF_SIZE];
    static BOOL bHeaderFlag[2] = {FALSE, FALSE};
    static BOOL bNumberSatelFlag[2] = {FALSE, FALSE};
    static BOOL bCRCFlag[2] = {FALSE, FALSE};
    static int nTopPick;
    static BOOL bFIRST_TIME = TRUE;
    unsigned int L0;    
    int SatT, nCntr, nNbr;
 
    //TRACE ("\nIncoming to function. state[%d]=%d, NbrOfBytes=%d\n",GPSNbr, state[GPSNbr],  NbrOfBytes );
     
 if (bFIRST_TIME)
 {
     //Reading an information from ini-file about a state of RR computer.
   GetProfileInt("[TOPPICK]","TopPick", 1, &nTopPick);     
     bFIRST_TIME = FALSE;
 } 
    nNbr=NbrOfBytes;

  while(NbrOfBytes --)
    {  
    switch (state[GPSNbr])
     {
     case 0: // Waiting for SYNC_FLAG1          
              if (*data == (char)SYNC_FLAG1)
            {
             state[GPSNbr] = 1 ; // Next should receive SYNC_FLAG2
           tmps[GPSNbr][0]=SYNC_FLAG1;
           RecvData[GPSNbr][0]=SYNC_FLAG1;           
                     //TRACE ("\n[GPSNbr=%d]:SYNC_FLAG1 received = %X\n",GPSNbr, SYNC_FLAG1);
            }                
       break;

     case 1: // Waiting for SYNC_FLAG2              
              if (*data == SYNC_FLAG2)
            {
             state[GPSNbr] = 2 ; // Next should receive SYNC_FLAG3
           tmps[GPSNbr][1]=SYNC_FLAG2;
           RecvData[GPSNbr][1]=SYNC_FLAG2;
           //TRACE ("[GPSNbr=%d]:SYNC_FLAG2 received = %X\n", GPSNbr, SYNC_FLAG2);
            }
       break;

     case 2: // Waiting for SYNC_FLAG3
              if (*data == SYNC_FLAG3)
            {             
           RePtr[GPSNbr]=3;
             state[GPSNbr]=3 ; //a message body should be received next  
           tmps[GPSNbr][2]=SYNC_FLAG3;
           RecvData[GPSNbr][2]=SYNC_FLAG3;
                     if (FirstChar && (GPSNbr == 0))
                     {
           //TRACE ("[GPSNbr=%d]: SYNC_FLAG3 received = %X\n",GPSNbr, SYNC_FLAG3); 
                     FirstCharTime=Get1msTime();
                     TRACE(" Alku: %ld(%d)\n", FirstCharTime,GPSNbr);
                     FirstChar=0;
                    
                     }
                    }
       break;

     case 3: // Receiving data
   //TRACE ("3: [GPSNbr=%d], Next character %X(%c)\n",GPSNbr, *data, *data);   
     // Put received byte to the buffer(s)     
      RecvData[GPSNbr][RePtr[GPSNbr]]=*data;      
      tmps[GPSNbr][RePtr[GPSNbr]]=*data;       
            RePtr[GPSNbr]++;
            


   // we have to recognize out of sync situation
       if (RePtr[GPSNbr] > 2)// don't mess up with normal syncronization !!!
         {
         if ((RecvData[GPSNbr][RePtr[GPSNbr]-1] == (char)SYNC_FLAG3) &&
             (RecvData[GPSNbr][RePtr[GPSNbr]-2] == (char)SYNC_FLAG2) &&
             (RecvData[GPSNbr][RePtr[GPSNbr]-3] == (char)SYNC_FLAG1))
           {            
                      TRACE("\nGPSNbr =%d, RePtr = %d (Now=3). Reason: don't mess up with normal syncronization\n",GPSNbr,RePtr[GPSNbr]);
            RePtr[GPSNbr]=3;  // just reset the buffer counter ! State remains still the same
                        //state[GPSNbr]=0;                        
                        bHeaderFlag[GPSNbr] = FALSE;
            break;
           }
         }
       // check buffer overflow (out of sync !)
        if (RePtr[GPSNbr] >= RECV_DATA_BUF_SIZE)
            {
           TRACE ("\nRePtr[%d] = %d (now set to 0). Reason: RePtr >= RECV_DATA_BUF_SIZE (%d)\n",GPSNbr, RePtr[GPSNbr], RECV_DATA_BUF_SIZE);
             bHeaderFlag[GPSNbr]= FALSE;
                     RePtr[GPSNbr]=0;
             state[GPSNbr]=0;                     
                     Range[0].nObs=0;
                     Sav_Range.Sav_Range_Header.obs=0;
           SatXYZ.nSat=0;
                     BestXYZ.Obs=0;
           break;
            }

  //now checking when HEADER is received:                 
    if (!bHeaderFlag[GPSNbr])
     { 
          if (RePtr[GPSNbr] >= (signed)sizeof(HEADER))
            {                 
                //set the GPS_Header structure:
        memcpy((void *)&GPS_Header[GPSNbr], (const void*)RecvData[GPSNbr], sizeof(HEADER));                
        nMsgLenght[GPSNbr] = (int)GPS_Header[GPSNbr].MessageLength;  
              nMsgLenght[GPSNbr] = nMsgLenght[GPSNbr] + sizeof(HEADER) + 4;// Added: HeaderLenght+CRC    
                nMessageID[GPSNbr] = (int)GPS_Header[GPSNbr].MessageID;                    
                //TRACE ("\nnMessageID[%d] = %d\n", GPSNbr, nMessageID[GPSNbr]);
              //TRACE ("nMsgLenght[%d] = %d\n", GPSNbr, nMsgLenght[GPSNbr]);
                bHeaderFlag[GPSNbr]= TRUE;                    
                if (nMsgLenght[GPSNbr] >= RECV_DATA_BUF_SIZE)
                {
                    //TRACE ("\nnMessageID[%d] = %d\n", GPSNbr, nMessageID[GPSNbr]);
                  //TRACE ("nMsgLenght[%d] = %d\n", GPSNbr, nMsgLenght[GPSNbr]);
                  TRACE ("Incorrect information received! All settings are set to 0!\n");
                    bHeaderFlag[GPSNbr]= FALSE;
                    RePtr[GPSNbr]=0;
            state[GPSNbr]=0;
                    Range[0].nObs=0;
                    Sav_Range.Sav_Range_Header.obs=0;  
          SatXYZ.nSat=0;
          break;
                }
            }            
     }// if !bHeaderFlag
    else
     { 
//********************************************RANGE_CMP***      
      if (nMessageID[GPSNbr] == RANGECMP_MSG) 
        {    
       // first, find the number of satellites, #obs
         // according to documentations, it's type: long, 4 binary bytes.                     
      if (!bNumberSatelFlag[GPSNbr] && (RePtr[GPSNbr] >= ((signed)sizeof(HEADER)+4))) 
            {
                memcpy((void *)&RangeCMP.RNG_Header, (const void*)RecvData[GPSNbr], sizeof(RNG_HEADER));                
                bNumberSatelFlag[GPSNbr] = TRUE;
                nRNGCount[GPSNbr] = 0;
                nRNGArrCount[GPSNbr] = 0;
                break;
            }
      // fill the number of arrays equal to number of visible satellites            
            if (bNumberSatelFlag[GPSNbr] && !bCRCFlag[GPSNbr])
            {            
       if (nRNGCount[GPSNbr] >= RNG_TMP_BUFF_SIZE) //RNG_TMP_BUFF_SIZE = 24
             {                    
                 nRNGCount[GPSNbr] = 0;
                 nRNGArrCount[GPSNbr]++;                                                   
                 if (nRNGArrCount[GPSNbr] >= ((int)RangeCMP.RNG_Header.obs))// no more satellites.
                 {
                     bCRCFlag[GPSNbr]= TRUE; // next 4 bytes are CRC. Set the CRC flag:                                          
                     nRNGArrCount[GPSNbr]=0; 
                 }
                 else                 
                    RangeCMP.tmpRNG[nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;
                }
              else
               RangeCMP.tmpRNG[nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                 
             }
      // check the CRC, in case enough bytes have been received          
         if ( RePtr[GPSNbr] >= nMsgLenght[GPSNbr]) 
          {                
                    //CRC calculates without the CRC bytes 
          RxCRC = CalculateBlockCRC32(nMsgLenght[GPSNbr]-4,tmps[GPSNbr]);        
          memcpy((void *)&CRC,(const void*)(tmps[GPSNbr]+(nMsgLenght[GPSNbr]-4)),sizeof(unsigned long));                    
                    RePtr[GPSNbr]=0;
          state[GPSNbr]=0;
                    bHeaderFlag[GPSNbr] = FALSE;
            bNumberSatelFlag[GPSNbr] = FALSE;
            bCRCFlag[GPSNbr] = FALSE;
          
                if ( RxCRC == CRC ) // CRC OK    
                    {                                     
                      for (SatT = 0;SatT<20; SatT++)
                            {
                         // re-set all arrays to invalide:
                           RangeCMP.RNG_Records[SatT].DataValidate = FALSE;                        
                            }                     
                      for (SatT = 0;SatT<(int)RangeCMP.RNG_Header.obs; SatT++)
                            {    
                             // NoOp
                            }     
                        RetVal = TRUE;        
                      TopPickTimeStamp (RangeCMP.RNG_Header.MessageID, RangeCMP.RNG_Header.Milliseconds);
                        break;  // out of loop                                             
                    }
         else    // CRC is not OK                
           CRCErrCounter++;                    
        }
        break;
      }
//********************************************SATXYZ***********     
     if (nMessageID[GPSNbr] == SATXYZ_MSG)
        {
        // first, find the number of satellites, #sat
         // according to documentations, it's type: Ulong, 4 binary bytes + 8 reserved bytes
      if (!bNumberSatelFlag[GPSNbr] && (RePtr[GPSNbr] >= (signed)(sizeof(HEADER)+12))) 
            {
               memcpy((void *)&SatXYZ.XYZ_Header, (const void*)RecvData[GPSNbr], sizeof(XYZ_HEADER));
                 // check the sat.number for correctness:
                  if ((int)SatXYZ.XYZ_Header.sat>12 || (int)SatXYZ.XYZ_Header.sat < 0)
                            SatXYZ.nSat =0;
                    else
                          SatXYZ.nSat = (int)SatXYZ.XYZ_Header.sat;                    
                 bNumberSatelFlag[GPSNbr] = TRUE;
                 nRNGCount[GPSNbr] = 0;
                 nRNGArrCount[GPSNbr] = 0;    
                 break;
            }
      // fill the number of arrays equal to number of visible satellites
            if (bNumberSatelFlag[GPSNbr] && !bCRCFlag[GPSNbr])
            { 
       if (nRNGCount[GPSNbr] >= XYZ_TMP_BUFF_SIZE) //XYZ_TMP_BUFF_SIZE = 68
                {              
                 //copy data from the temp buffer to an appropriate array:
         //memcpy((void *)&tmpXYZ[nRNGArrCount[GPSNbr]], (const void*)cXYZTmpBuf[nRNGArrCount[GPSNbr]], sizeof(XYZ_RANGE));
                  nRNGArrCount[GPSNbr]++;
                    nRNGCount[GPSNbr] = 0;
                  if (nRNGArrCount[GPSNbr] >= SatXYZ.nSat)// no more satellites.
                        {                       
                         bCRCFlag[GPSNbr]= TRUE; // next 4 bytes are CRC. Set the CRC flag.
                       nRNGArrCount[GPSNbr]=0; // reset the static variable 
                         //TRACE("SatXYZ: %ld(%d)\n", Get1msTime(),GPSNbr);
                        }
                else
                  cXYZTmpBuf[nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                    
                }
             else             
                 cXYZTmpBuf[nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                                   
            }            
      // check CRC in case enough bytes hav been received       
          if ( RePtr[GPSNbr] >= nMsgLenght[GPSNbr]) 
          {            
                    //TRACE ("nMsgLenght[%d]=%d, RePtr[GPSNbr]=%d\n",GPSNbr, nMsgLenght[GPSNbr], RePtr[GPSNbr]);
                    RxCRC = CalculateBlockCRC32(nMsgLenght[GPSNbr]-4,tmps[GPSNbr]);        
          memcpy((void *)&CRC,(const void*)(tmps[GPSNbr]+(nMsgLenght[GPSNbr]-4)),sizeof(unsigned long));                     
          nNbr = RePtr[GPSNbr]; 
                    RePtr[GPSNbr] = 0;
          state[GPSNbr] = 0;
                    bHeaderFlag[GPSNbr] = FALSE;
            bNumberSatelFlag[GPSNbr] = FALSE;
            bCRCFlag[GPSNbr] = FALSE;
                    //TRACE ("RxCRC = %d, CRC = %d\n", RxCRC, CRC);
                    if ( RxCRC == CRC ) // CRC OK 
                    {
                    //clean the arrays:
                        for (SatT = 0; SatT<12; SatT++)
                             SatXYZ.bValidSatArray[SatT] = FALSE;
                    //copy data from temp char array to working XYZ_RANGE one:
                        for (SatT = 0; SatT<SatXYZ.nSat; SatT++)
                        {                         
                         memcpy((void *)&SatXYZ.XYZ_Records[SatT], (const void*)cXYZTmpBuf[SatT], sizeof(XYZ_RANGE));
                         SatXYZ.bValidSatArray[SatT] = TRUE;
                        }
                        //*********************DEBUG:**********************************
                      /*TRACE ("\nSatXYZ.XYZ_Records:        ");
                        for (SatT = 0; SatT<SatXYZ.nSat; SatT++)
                        {    
                            TRACE("[%d]=%d, ", SatT, (int)SatXYZ.XYZ_Records[SatT].PRN);
                         //TRACE("SatXYZ.XYZ_Records[%d].PRN = %d\n", SatT, SatXYZ.XYZ_Records[SatT].PRN);
                         /TRACE("SatXYZ.XYZ_Records[%d].SatelX = %f\n", SatT, (float)SatXYZ.XYZ_Records[SatT].SatelX);
                         TRACE("SatXYZ.XYZ_Records[%d].SatelY = %f\n", SatT, (float)SatXYZ.XYZ_Records[SatT].SatelY);
                         TRACE("SatXYZ.XYZ_Records[%d].SatelZ = %f\n", SatT, (float)SatXYZ.XYZ_Records[SatT].SatelZ);
                         TRACE("SatXYZ.XYZ_Records[%d].CLK_Corr = %f\n", SatT, (float)SatXYZ.XYZ_Records[SatT].CLK_Corr);
                         TRACE("SatXYZ.XYZ_Records[%d].ION_Corr = %f\n", SatT, (float)SatXYZ.XYZ_Records[SatT].ION_Corr);
                         TRACE("SatXYZ.XYZ_Records[%d].TROP_Corr = %f\n", SatT, SatXYZ.XYZ_Records[SatT].TROP_Corr);
                         if (SatXYZ.bValidSatArray[SatT])
                          TRACE("SatXYZ.bValidSatArray[%d]= TRUE\n", SatT);
                         else 
                            TRACE("SatXYZ.bValidSatArray[%d]= FALSE\n",SatT);
                         TRACE("\nSatXYZ.= %d\n", SatXYZ.); 
                        }*/ 
                        //TRACE("SatXYZ.Timestamps= %d\n", (int)SatXYZ.XYZ_Header.Milliseconds);
                 //*********************************************************** 
                     RetVal = TRUE;
                     TopPickTimeStamp (SatXYZ.XYZ_Header.MessageID, SatXYZ.XYZ_Header.Milliseconds);
           break;// out of loop  
                    }
          else // CRC <> RxCRC
                    {
                        CRCErrCounter++;
                        TRACE ("\nSatXYZ: Checksum is not correct! SatXYZ.nSat was %d, now it's 0..\n", SatXYZ.nSat);
                        SatXYZ.nSat =0;                        
                    }
           }
     break;           
      } 

// ****************************RANGE*********************   
if (nMessageID[GPSNbr] == RANGE_MSG)
        {
        // first, find the number of satellites, #sat
         // according to documentations, it's type: Ulong, 4 binary bytes 
      if (!bNumberSatelFlag[GPSNbr] && (RePtr[GPSNbr] >= (signed)(sizeof(HEADER)+4))) 
            {
               memcpy((void *)&Range[GPSNbr].Range_Header, (const void*)RecvData[GPSNbr], sizeof(RANGE_HEADER));
                 if ((int)Range[GPSNbr].Range_Header.obs > 24 || (int)Range[GPSNbr].Range_Header.obs < 0)
                            Range[GPSNbr].Range_Header.obs =0;//to prevent array's overflow..                     
                 bNumberSatelFlag[GPSNbr] = TRUE;
                 nRNGCount[GPSNbr] = 0;
                 nRNGArrCount[GPSNbr] = 0;
                 break;
            }
      // fill the number of arrays equals to number of visible satellites
            if (bNumberSatelFlag[GPSNbr] && !bCRCFlag[GPSNbr])
            {       
       if (nRNGCount[GPSNbr] >= RNG_BUFF_SIZE)  // RNG_BUFF_SIZE=44
             {        
                nRNGArrCount[GPSNbr]++;
                nRNGCount[GPSNbr] = 0;                                   
                if (nRNGArrCount[GPSNbr] >= ((int)Range[GPSNbr].Range_Header.obs))// no more satellites.
                    {                     
                     bCRCFlag[GPSNbr]= TRUE; // next 4 bytes are CRC. Set the CRC flag.                     
                     nRNGArrCount[GPSNbr]=0; // reset the static variable 
                     //TRACE("Range: %ld(%d)\n", Get1msTime(),GPSNbr);
                    }
                else                  
                 cRANGETmpBuf[GPSNbr][nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                  
             }
             else
                  cRANGETmpBuf[GPSNbr][nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                           
            }
      // check CRC, in case enough bytes have been received       
          if ( RePtr[GPSNbr] >= nMsgLenght[GPSNbr]) 
          {            
                    //TRACE ("nMsgLenght[%d]=%d, RePtr[GPSNbr]=%d\n",GPSNbr, nMsgLenght[GPSNbr], RePtr[GPSNbr]);
                    RxCRC = CalculateBlockCRC32(nMsgLenght[GPSNbr]-4,tmps[GPSNbr]);        
          memcpy((void *)&CRC,(const void*)(tmps[GPSNbr]+(nMsgLenght[GPSNbr]-4)),sizeof(unsigned long));                     
          RePtr[GPSNbr] = 0;
          state[GPSNbr] = 0;
                    bHeaderFlag[GPSNbr] = FALSE;
            bNumberSatelFlag[GPSNbr] = FALSE;
            bCRCFlag[GPSNbr] = FALSE;
          //TRACE ("Range: Calculated RxCRC =%d, received CRC= %d\n ",RxCRC, CRC);
                    if ( RxCRC == CRC ) // CRC OK 
                    {                    
                    //cleaning out all arrays:
                        for (SatT = 0; SatT<24; SatT++)
                        {                             
                         Range[GPSNbr].bValidSatArray[SatT] = FALSE;                         
                        }
                        nCntr = 0;
                        RxCRC=0;
                    //copy data from temp char array to the working RANGE array:                        
                        for (SatT = 0; SatT<(int)Range[GPSNbr].Range_Header.obs; SatT++)
                        {                          
                            L0 = cRANGETmpBuf[GPSNbr][SatT][42]/32;                          
              if (L0<1) // bites n-r 20&21 == "00", Freq==L1
                            {                           
                             memcpy((void *)&Range[GPSNbr].Range_Records[nCntr], (const void*)cRANGETmpBuf[GPSNbr][SatT], sizeof(RANGE_RANGE));
                           Range[GPSNbr].bValidSatArray[nCntr++] = TRUE;
                            }
                        }    
                        Range[GPSNbr].Range_Header.obs = (unsigned long)nCntr;
                        Range[GPSNbr].nObs = nCntr;

//**********creating Sav_Range for sending it to a TopPick:***************
           if (!nTopPick) // i.e. - BaseStation
                     {                    
            //step1:                        
            memcpy((void *)&Sav_Range.Sav_Range_Header, (const void*)&Range[GPSNbr].Range_Header, sizeof(Sav_Range));                        
            Sav_Range.Sav_Range_Header.MessageID= SAV_RNG_MSG; // = 1001
                        Sav_Range.Sav_Range_Header.MessageLength =292;//324 in general, but (see how header is counted)
               //step2:
                        for (SatT = 0; SatT<nCntr; SatT++)
                            {                            
                             Sav_Range.Sav_Range_Records[SatT].PRN = Range[GPSNbr].Range_Records[SatT].PRN;
                             Sav_Range.Sav_Range_Records[SatT].ADR = Range[GPSNbr].Range_Records[SatT].ADR ;
               Sav_Range.Sav_Range_Records[SatT].LockTime = Range[GPSNbr].Range_Records[SatT].LockTime;
                             Sav_Range.bValidSatArray[nCntr] = TRUE;
                            }                    
                        memcpy((void *)cTMP_Buf, (const void*)&Sav_Range, sizeof(Sav_Range));
                        // calculate a CRC and add it's value to sending packet:                        
                        Sav_Range.CRC = CalculateBlockCRC32(sizeof(Sav_Range)-4, (unsigned char*)cTMP_Buf);
                        //change CRC a little, for prevent it from reading a GPS card in the RTG:
                        Sav_Range.CRC = ~Sav_Range.CRC;
                        memcpy((void *)(cTMP_Buf + sizeof(Sav_Range)-4), (const void*)&Sav_Range.CRC, sizeof(Sav_Range.CRC));
                        //Send Sav_Range to a TopPick:
                        if (!nTopPick) // i.e. - BaseStation
                           TxData(DIFF_PORT, cTMP_Buf, sizeof(Sav_Range));
                     } 
//***********End of creating Sav_Range_Cmp*************************************
                     
                     //**************************DEBUG TRACING****************          
                      //TRACE("\nRange[%d].Range_Header.obs= %d\n",GPSNbr, Range[GPSNbr].Range_Header.obs);
                        //TRACE("\nRange[%d].Range_Header.obs: ", GPSNbr);
                    /*    for (SatT = 0; SatT < Range[GPSNbr].nObs; SatT++)
                        {
                         //TRACE("[%d]=%d, ",SatT, Range[GPSNbr].Range_Records[SatT].PRN);
                       TRACE("Range[%d].Range_Records[%d].PRN= %d\n",GPSNbr, SatT, Range[GPSNbr].Range_Records[SatT].PRN);
                       TRACE("Range[%d].Range_Records[%d].LockTime= %f\n",GPSNbr, SatT, Range[GPSNbr].Range_Records[SatT].LockTime);
                         TRACE("Range[%d].Range_Records[%d].ADR= %f\n",GPSNbr, SatT, Range[GPSNbr].Range_Records[SatT].ADR);
                         //for (int r=0; r<4; r++)
                         //  TRACE(":%x", Range[GPSNbr].Range_Records[SatT].ChnlTrackStatus[r]);
                         //TRACE ("\n");
                         if (Range[GPSNbr].bValidSatArray[SatT])
                          TRACE("Racnge[%d].bValidSatArray[%d]= TRUE  %d\n",GPSNbr, SatT, Range[GPSNbr].bValidSatArray[SatT]);
                         else 
                            TRACE("Range[%d].bValidSatArray[%d]= FALSE %d\n",GPSNbr, SatT, Range[GPSNbr].bValidSatArray[SatT]);
                     }*/
                     //*****************************************************************************                    
                     RetVal = TRUE;
                     TopPickTimeStamp (Range[GPSNbr].Range_Header.MessageID + GPSNbr, Range[GPSNbr].Range_Header.Milliseconds);    
           break; // out of loop  
                    }
          else
                    {
           TRACE ("Range[%d]: CheckSum was not correct!\n", GPSNbr);
                     Range[GPSNbr].nObs =0;
                     CRCErrCounter++;          
                    }
           }
     break;           
      }   

//********************************************SAV_RANGE****************************
 if (nTopPick) // i.e. - RR is in the TopPick (not the BaseStation!)
 {
   if (nMessageID[GPSNbr] == SAV_RNG_MSG) // 1001
    {    
       // first, find the number of satellites, #obs
         // according to documentations, it has a type: "Ulong", 4 binary bytes long
      if (!bNumberSatelFlag[GPSNbr] && (RePtr[GPSNbr] >= (signed)(sizeof(HEADER)+4))) 
            {
               memcpy((void *)&Sav_Range.Sav_Range_Header, (const void*)RecvData[GPSNbr], sizeof(SAV_RANGE_HEADER));
                 if ((int)Sav_Range.Sav_Range_Header.obs > 24 || (int)Sav_Range.Sav_Range_Header.obs < 0)
                            Sav_Range.Sav_Range_Header.obs =0;//to prevent array's overflow..                     
                 bNumberSatelFlag[GPSNbr] = TRUE;
                 nRNGCount[GPSNbr] = 0;
                 nRNGArrCount[GPSNbr] = 0;
                 break;
            }
      // fill number of arrays equals to number of visible satellites
            if (bNumberSatelFlag[GPSNbr] && !bCRCFlag[GPSNbr])
            {       
       if (nRNGCount[GPSNbr] >= SAV_RNG_TMP_BUFF_SIZE)  // SAV_RNG_TMP_BUFF_SIZE=16
             {        
                nRNGArrCount[GPSNbr]++;
                nRNGCount[GPSNbr] = 0;                                   
                if (nRNGArrCount[GPSNbr] >= ((int)Sav_Range.Sav_Range_Header.obs))// no more satellites.
                    {                     
                     bCRCFlag[GPSNbr]= TRUE; // next 4 bytes are CRC. Set the CRC flag.                     
                     nRNGArrCount[GPSNbr]=0; // reset the static variable 
                    }
                 else                  
                    cSAV_RNGmpBuf[nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                  
             }
             else
                  cSAV_RNGmpBuf[nRNGArrCount[GPSNbr]][nRNGCount[GPSNbr]++] = *data;                           
            }            
      // check the CRC, in case enough bytes have been received       
          if (RePtr[GPSNbr] >= nMsgLenght[GPSNbr]) //324 bytes
          {             
/*******************TRACE DEBUG**********************
                    if (nTopPick) 
                     {
            memcpy((void *)&cSend_Out_Buf[GPSNbr], (const void*)RecvData[GPSNbr], nMsgLenght[GPSNbr]);
                TxData(GPS_PORT, cSend_Out_Buf[GPSNbr], nMsgLenght[GPSNbr]);
                   TRACE ("\nTopPick(GPSNbr=%d): sent to GPS:(CommPort%d)\n", GPSNbr, GPS_PORT);
                     //for (int nOut=0; nOut<nMsgLenght[GPSNbr]; nOut++)
                   //    TRACE ("%c", (unsigned char)cSend_Out_Buf[GPSNbr][nOut]);
                     //TRACE ("\n");
                     }
**************************************************/
                    //TRACE ("nMsgLenght[%d]=%d, RePtr[GPSNbr]=%d\n",GPSNbr, nMsgLenght[GPSNbr], RePtr[GPSNbr]);
                    RxCRC = CalculateBlockCRC32(nMsgLenght[GPSNbr]-4,tmps[GPSNbr]);        
          memcpy((void *)&CRC,(const void*)(tmps[GPSNbr]+(nMsgLenght[GPSNbr]-4)),sizeof(unsigned long));                     
     //TRACE ("Sav_Range(before): Calculated RxCRC =%d, received CRC= %d\n ",RxCRC, CRC);
                    RePtr[GPSNbr] = 0;
          state[GPSNbr] = 0;
                    bHeaderFlag[GPSNbr] = FALSE;
            bNumberSatelFlag[GPSNbr] = FALSE;
            bCRCFlag[GPSNbr] = FALSE;
     //TRACE ("Sav_Range(after): Calculated RxCRC =%d, received CRC= %d\n ",RxCRC, ~CRC);
                  if ( RxCRC == ~CRC ) // CRC OK 
                    {        
                        //TRACE("SavRange: %ld(%d)\n", Get1msTime(),GPSNbr);
                    //cleaning out all arrays:
                        for (SatT = 0; SatT<24; SatT++)
                             Sav_Range.bValidSatArray[SatT] = FALSE; 

                    //copy data from temp char array to the real SAV_RANGE array:
                        for (SatT = 0; SatT<(int)Sav_Range.Sav_Range_Header.obs; SatT++)
                        {                                        
                          memcpy((void *)&Sav_Range.Sav_Range_Records[SatT], (const void*)cSAV_RNGmpBuf[SatT], sizeof(SAV_RANGE_RANGE));
                          Sav_Range.bValidSatArray[SatT] = TRUE;                            
                        }    
                
                  /**************************DEBUG TRACING****************                   
                        for (int nDEB=0; nDEB<Sav_Range.Sav_Range_Header.obs; nDEB++)                             
                        {                         
                       TRACE("Sav_Range.Sav_Range_Records[%d].PRN= %d\n", nDEB, Sav_Range.Sav_Range_Records[nDEB].PRN);
                       TRACE("Sav_Range.Sav_Range_Records[%d].LockTime= %f\n",nDEB, Sav_Range.Sav_Range_Records[nDEB].LockTime);
             TRACE("Sav_Range.Sav_Range_Records[%d].ADR= %f\n",nDEB, Sav_Range.Sav_Range_Records[nDEB].ADR);                         
                         
                         if (Sav_Range.bValidSatArray[nDEB])
                          TRACE("Sav_Range.bValidSatArray[%d]= TRUE  %d\n", nDEB, Sav_Range.bValidSatArray[nDEB]);
                         else 
                            TRACE("Sav_Range.bValidSatArray[%d]= FALSE  %d\n", nDEB, Sav_Range.bValidSatArray[nDEB]);
                     }
                     **********************END OF DEBUG TRACING**************/
                     RetVal = TRUE;
                     TopPickTimeStamp (Sav_Range.Sav_Range_Header.MessageID, Sav_Range.Sav_Range_Header.Milliseconds);
           break; // out of loop  
                    }
          else // CRC is not OK 
                    {
           TRACE ("Sav_Range: CheckSum was not correct!\n");                     
                     Sav_Range.Sav_Range_Header.obs =0;
                     CRCErrCounter++;          
                    }
           }
         break;
      }// if BESTPOS_MSG             
  } // if (nTopPick)

//********************************************RTCM3****************************
   if (nMessageID[GPSNbr] == RTCM3_MSG) // 117
    {    
       if ( RePtr[GPSNbr] >= nMsgLenght[GPSNbr])// check if enough bytes have been received
         {           
             memcpy((void *)&cSend_Out_Buf[GPSNbr], (const void*)RecvData[GPSNbr], nMsgLenght[GPSNbr]);             
             if (!nTopPick) // i.e. - BaseStation
                {
             TxData(DIFF_PORT, cSend_Out_Buf[0], nMsgLenght[GPSNbr]);
               /*TRACE ("\nBaseStation(GPSNbr=%d): sent to TopPick:\n", GPSNbr);
               for (int nOut=0; nOut<nMsgLenght[GPSNbr]; nOut++)
               TRACE ("%c", (unsigned char)cSend_Out_Buf[0][nOut]);
               TRACE ("\n");*/
                }
           else // TopPick RoadRunner
                {
               TxData(GPS_PORT, cSend_Out_Buf[1], nMsgLenght[GPSNbr]);
             /*TRACE ("\nTopPick(GPSNbr=%d): sent to GPS-card:\n", GPSNbr);
             for (int nOut=0; nOut<nMsgLenght[GPSNbr]; nOut++)
                 TRACE ("%c", (unsigned char)cSend_Out_Buf[1][nOut]);
               TRACE ("\n");*/
                }
             RePtr[GPSNbr] = 0;
       state[GPSNbr] = 0;
             bHeaderFlag[GPSNbr] = FALSE;
         } // if RePtr[GPSNbr] >= sizeof()
         break;
      }

//********************************************RTCM59****************************
   if (nMessageID[GPSNbr] == RTCM59_MSG) // 116
    {    
       if ( RePtr[GPSNbr] >= nMsgLenght[GPSNbr])// check if enough bytes have been received
         {          
             memcpy((void *)&cSend_Out_Buf[GPSNbr], (const void*)RecvData[GPSNbr], nMsgLenght[GPSNbr]);             
             if (!nTopPick) // i.e. - BaseStation
                {
             TxData(DIFF_PORT, cSend_Out_Buf[0], nMsgLenght[GPSNbr]);
               /*TRACE ("\nBaseStation (GPSNbr=%d): sent to TopPick:\n", GPSNbr);
               for (int nOut=0; nOut<nMsgLenght[GPSNbr]; nOut++)
               TRACE ("%c", (unsigned char)cSend_Out_Buf[0][nOut]);
               TRACE ("\n");*/
                }
           else // TopPick RoadRunner
                {
               TxData(GPS_PORT, cSend_Out_Buf[1], nMsgLenght[GPSNbr]);
             /*TRACE ("\nTopPick(GPSNbr=%d): sent to GPS-card:\n", GPSNbr);
             for (int nOut=0; nOut<nMsgLenght[GPSNbr]; nOut++)
                 TRACE ("%c", (unsigned char)cSend_Out_Buf[1][nOut]);
               TRACE ("\n");*/
                }             
             RePtr[GPSNbr] = 0;
       state[GPSNbr] = 0;
             bHeaderFlag[GPSNbr] = FALSE;
         } 
         break;
      }

//********************************************BESTPOS****************************
   if (nMessageID[GPSNbr] == BESTPOS_MSG)
    {    
       if ( RePtr[GPSNbr] >= (signed)sizeof(BESTPOS))// check if enough bytes have been received
         {              
       memcpy((void *)&tmpBPOS, (const void*)tmps[GPSNbr], sizeof(BESTPOS));//only for CRC value
       RxCRC = CalculateBlockCRC32((unsigned long)sizeof(BESTPOS)-sizeof(unsigned long), tmps[GPSNbr]);
     //TRACE (" Calculated RxCRC =%d, received tmpBPOS.CRC= %d\n ",RxCRC, tmpBPOS.CRC);       
             if ( RxCRC == tmpBPOS.CRC )
        {
          //Fill in the BestPos structure if raceived CRC is equal to calculated:
          memcpy((void *)&BestPos, (const void*)RecvData[GPSNbr],sizeof(BESTPOS));
          CRCSucCounter++;          
                  RetVal = TRUE;                    
          TopPickTimeStamp (BestPos.MessageID, BestPos.Milliseconds);
                    //TRACE("BestPos: %ld(%d)\n", Get1msTime(),GPSNbr);
         }
       else // if RxCRC <> tmpBPOS.CRC
                 CRCErrCounter++;

             RePtr[GPSNbr] = 0;
       state[GPSNbr] = 0;
             bHeaderFlag[GPSNbr] = FALSE;
         } // if RePtr[GPSNbr] >= sizeof(BESTPOS)
         break;
      }// if BESTPOS_MSG

//********************************************BESTXYZ****************************
   if (nMessageID[GPSNbr] == BESTXYZ_MSG)
    {
       if ( RePtr[GPSNbr] >= (signed)sizeof(BESTXYZ))// check if enough bytes have been received
         {
       memcpy((void *)&tmpBXYZ, (const void*)tmps[GPSNbr], sizeof(BESTXYZ));//only for CRC value
       RxCRC = CalculateBlockCRC32((unsigned long)sizeof(BESTXYZ)-sizeof(unsigned long), tmps[GPSNbr]);
     //TRACE ("RxCRC = %d, tmpBXYZ.CRC = %d\n", RxCRC, tmpBXYZ.CRC);

         //Fill in the BestPos structure if received CRC is equal to calculated CRC:
             if ( RxCRC == tmpBXYZ.CRC )
        {
          memcpy((void *)&BestXYZ, (const void*)RecvData[GPSNbr],sizeof(BESTXYZ));
          CRCSucCounter++;
                  RetVal = TRUE;
             /*TRACE ("BestXYZ.Milliseconds=%d\n", BestXYZ.Milliseconds);
                  TRACE ("BestXYZ.PosType= %d\n", (int)BestXYZ.PosType);
                    TRACE ("BestXYZ.PX_StdDeviation= %f\n", BestXYZ.PX_StdDeviation);
                    TRACE ("BestXYZ.PY_StdDeviation= %f\n", BestXYZ.PY_StdDeviation);
                    TRACE ("BestXYZ.PZ_StdDeviation= %f\n", BestXYZ.PZ_StdDeviation);
                    TRACE ("BestXYZ.PX_StdDeviation= %f\n", BestXYZ.X_Coord);
                    TRACE ("BestXYZ.PY_StdDeviation= %f\n", BestXYZ.Y_Coord);
                    TRACE ("BestXYZ.PZ_StdDeviation= %f\n", BestXYZ.Z_Coord);*/
          //TRACE("BestXYZ: %ld(%d)\n", Get1msTime(),GPSNbr);
                    TRACE ("BestXYZ ms=%d\n", BestXYZ.Milliseconds);
                    TRACE ("timestatus= %d\n", (int)BestXYZ.TimeStatus);
            TRACE ("type= %d\n", (int)BestXYZ.PosType);
                    TRACE ("SolStatus= %d\n", (int)BestXYZ.PSolStatus);
                    TRACE ("stdx= %.2f\n", BestXYZ.PX_StdDeviation);
                    TRACE ("stdy= %.2f\n", BestXYZ.PY_StdDeviation);
                    TRACE ("stdz= %.2f\n", BestXYZ.PZ_StdDeviation);
                    TRACE ("no_of_gps= %d\n", no_of_gps);
                    TRACE ("x= %.2f\n", BestXYZ.X_Coord);
                    TRACE ("y= %.2f\n", BestXYZ.Y_Coord);
                    TRACE ("z= %.2f\n", BestXYZ.Z_Coord);

                    
                    PosValid = FALSE;
                    if ((BestXYZ.PosType > 0) && (BestXYZ.PSolStatus == 0)) {
                        PosValid = TRUE;
                    }

          GPSGood = FALSE;
                    if (BestXYZ.PosType == 32) { // L1_FLOAT = "RT20"
                        if (BestXYZ.TimeStatus == 180) { // FINESTEERING
                            if (BestXYZ.PX_StdDeviation*1000.0 < MaxDeviation) {
                                if (BestXYZ.PY_StdDeviation*1000.0 < MaxDeviation) {
                                    if (BestXYZ.PZ_StdDeviation*1000.0 < 3.0*MaxDeviation) {
                                            //if (no_of_gps < 9) { // test
                                            GPSGood = TRUE;
                                        //}
                                    }
                                }
                            }
                        }
                    }

                    TopPickTimeStamp (BestXYZ.MessageID, BestXYZ.Milliseconds);
         }
       else // if RxCRC <> tmpBPOS.CRC
                {
          CRCErrCounter++;
                    TRACE ("BestXYZ: Checksum is not correct!\n");
        }       
       RePtr[GPSNbr] = 0;
       state[GPSNbr] = 0;
             bHeaderFlag[GPSNbr] = FALSE;
         } // if RePtr[GPSNbr] >= sizeof(BESTPOS)
      }// if BESTPOS_MSG
      break;
//****************************************************************************

     }// else: bHeaderFlag==TRUE
  break; //case 3

  default:        
    state[GPSNbr]=0;
    break ;
   }
    data++;
  }
    /*if (RetVal)
     TRACE ("Message is done. RetVal= TRUE\n");
  else 
     TRACE ("Message is done, but not complete. RetVal= FALSE\n");*/
  return(RetVal); // if == FALSE, it means message is not ready yet
} // function is over.
//****************************************************************************
