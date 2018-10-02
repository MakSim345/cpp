#include "gen.h"
#include "utils.h"
#include "FixedPoint.hpp"

namespace Msf {

long g_lTimeTick = 0;

const int EEG_MAX_FREQ = 30;
const int EEG_MIN_FREQ = 0;

const FixedPoint getFrequencyResolution()
{
    static const FixedPoint EEG_FREQ_RESOLUTION = FixedPoint(0.39);
    return EEG_FREQ_RESOLUTION;
}

//namespace {
template<class Type>
int freqIndex(const Type& freqP)
{
    return ((freqP - EEG_MIN_FREQ) / getFrequencyResolution()).getRounded().getInt(); //lint !e845 Argument is certain to be 0
}
} // namespace Msf


void cip_test_01()
{
    const int EEG_MAX_FREQ = 30;
    const int EEG_MIN_FREQ = 0;

    const int EEG_MIN_INDEX = Msf::freqIndex(EEG_MIN_FREQ);
    const int EEG_MAX_INDEX = Msf::freqIndex(EEG_MAX_FREQ);

    const Msf::FixedPoint DELTA_MIN_FREQ(0.0);
    const Msf::FixedPoint DELTA_MAX_FREQ(4.0);     // -> FFT indices 0..10 for Delta
    const Msf::FixedPoint THETA_MIN_FREQ(4.0);
    const Msf::FixedPoint THETA_MAX_FREQ(7.8);     // -> FFT indices 11..20 for Theta
    const Msf::FixedPoint ALPHA_MIN_FREQ(8.0);
    const Msf::FixedPoint ALPHA_MAX_FREQ(12.9);    // -> FFT indices 21..33 for Alpha
    const Msf::FixedPoint BETA_MIN_FREQ(13.3);
    const Msf::FixedPoint BETA_MAX_FREQ(30.0);     // -> FFT indices 34..76 for Beta


    const int DELTA_MIN_INDEX = Msf::freqIndex(DELTA_MIN_FREQ);
    const int DELTA_MAX_INDEX = Msf::freqIndex(DELTA_MAX_FREQ);
    const int THETA_MIN_INDEX = Msf::freqIndex(THETA_MIN_FREQ);
    const int THETA_MAX_INDEX = Msf::freqIndex(THETA_MAX_FREQ);
    const int ALPHA_MIN_INDEX = Msf::freqIndex(ALPHA_MIN_FREQ);
    const int ALPHA_MAX_INDEX = Msf::freqIndex(ALPHA_MAX_FREQ);
    const int BETA_MIN_INDEX = Msf::freqIndex(BETA_MIN_FREQ);
    const int BETA_MAX_INDEX = Msf::freqIndex(BETA_MAX_FREQ);
}

int count_chr_array(const char array[]) 
{
    int i = 0;
    while(array[i] != NULL) 
    {
        i++;
    }
    return i;
}


/**
 * @param pStringP string that possibly has a font size prefix of form $<number> at the beginning
 * @return length of font string of form $<number>, if any, at the beginning of @a pStringP.
 * That is, either 0 or 2.
 */
int fontPrefixLength(const char* pStringP)
{
    return (pStringP[0] == '$') && (pStringP[1] >= '0') && (pStringP[1] <= '9') ? 2 : 0;
}

inline char* safeStringCopyPtr(char* pDestP, const char* pSrcP, size_t destSizeP)
{
    if (destSizeP > 0)
    {
        std::strncpy(pDestP, pSrcP, destSizeP - 1);
        pDestP[destSizeP - 1] = '\0';
    }
    return pDestP;
}


void getDriAlarmText(const char* rAlarmP,
                     char* pDriTextP,
                     size_t driTextSizeP)
{
    char alarmTextTempBuffer[MAX_ALARM_TEXT_LEN] = {0};

    memset(pDriTextP, 0, driTextSizeP);
    // memcpy(alarmTextTempBuffer, rAlarmP, driTextSizeP);
    std::strncpy(alarmTextTempBuffer, rAlarmP, driTextSizeP);
    printf ("alarmTextTempBuffer:   %s.\n", alarmTextTempBuffer);
    
    /*
    Msf::Localization::DRICpUnicode::instance().convertUnicodeToDriCp(
        alarmTextTempBuffer, rAlarmP.getAlarmText().wc_str(), ELEMENTS(alarmTextTempBuffer));
    */

    // Skip font size at the beginning
    const int fontSizeSkip = fontPrefixLength(alarmTextTempBuffer);
    printf ("alarmTextTempBuffer+:  %s.\n", alarmTextTempBuffer + fontSizeSkip);

    safeStringCopyPtr(pDriTextP, alarmTextTempBuffer + fontSizeSkip, driTextSizeP);

    printf ("size: %d. pDriTextP: %s.\n", count_chr_array(pDriTextP), pDriTextP);
}



int main(int argc, char *argv[], char *envp[])
{
    long LastTimeIn=0;
    long LastTimeInMS = 0;
    int RValue = false;
    int Counter=0;
    int CaptureModeHex = 0;
    int NewChar=0;
    int nResult = 0;

    std::cout << "main - start\n";

    char text[MAX_ALARM_MSG_TEXT_LEN];
    getDriAlarmText("$1Check_NIBP_123456789X_123456789X_123456789X_123456789X_123456789X_123456789X_123456789X_", text, sizeof(text));

    std::cout << "Application completed. Idle loop. Press any key to exit\n";
 //*************MAIN LOOP*****************//
 do
 {
   //This is simple Windows way:
   Sleep(1000);

   nResult++;

   printf ("%d - Time: %ld.\n", nResult, Get1msTimeMS());

  // control of endless loop (may be also in monitor.cpp)
    if (_kbhit())  // has anything been pressed from keyboard ?
    {
     RValue = true; // END mark     
    }
}while (!RValue);

#ifdef FILE_OUTPUT
 if (1 == nOpenFileToken)
   fclose (fi);
#endif

printf ("Application complete.\n");
return 0;
}
