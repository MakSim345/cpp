#if !defined( VENTILATORWAVEFORMS_H )
#define VENTILATORWAVEFORMS_H 

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VCBTESTINTERFACEDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VCBTESTINTERFACEDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef VCBTESTINTERFACEDLL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

extern "C"
{
	DLL_EXPORT typedef struct
	{
        
 

            char EndOfBreathIndicator;
                        //Type IRIS_BYTE

            char StartOfMechanicalBreathIndicator;
                        //Type IRIS_BYTE
           
            char StartOfSpontaneousBreathIndicator;
                        // Type IRIS_BYTE
          

            char StartOfPSVBreathIndicator;
                        // Type IRIS_BYTE
         

            char EndOfInspiration;
                        // Type IRIS_BYTE
          

            short PawWaveform[10];
              //          Type IRIS_INT16[10]
           
            unsigned char PawWaveformDataStatus;
                //        Type IRIS_UBYTE
             
            int FlowWaveform[10];
                  //      Type IRIS_INT32[10]
            

            unsigned char FlowWaveformDataStatus;
                    //    Type IRIS_UBYTE
            
            int VolumeWaveform[10];
                      //  Type IRIS_INT32[10]
           

            unsigned char VolumeWaveformDataStatus;
                        //Type IRIS_UBYTE
             

            short PauxWaveform[10];
                       // Type IRIS_INT16[10]
            

            unsigned char PauxWaveformDataStatus;
                       // Type IRIS_UBYTE
               
            unsigned char SequenceNumber;
                       // Type IRIS_UBYTE
                  
                       
        		
        }VentilatorWaveforms;

    }

#endif
