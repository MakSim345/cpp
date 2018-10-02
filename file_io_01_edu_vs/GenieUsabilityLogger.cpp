#include "GenieUsabilityLogger.h"
#include "gen.h"
// using namespace GEng;

GenieUsabilityLogger::GenieUsabilityLogger(void)
{
    // std::cout << "in GenieUsabilityLogger ctor " << std::endl;
    //mLogTime = new QTime();
    //mLogTime->start();
}

GenieUsabilityLogger::~GenieUsabilityLogger(void)
{
    CloseLogFile();
}

void GenieUsabilityLogger::CloseLogFile()
{
    if (mOut && mOut.is_open())
    {
        mOut.close();
    }
}

bool GenieUsabilityLogger::OpenLogFile(std::string username)
{
    //std::cout << "in GenieUsabilityLogger::OpenLogFile" << username.toStdString() << std::endl;
    long double count = 1;
    std::string fname = username + "_" + std::to_string(count) + ".txt";
    while (FileExists(fname) && count < 100)
    {
        count++;
        fname = username + "_" + std::to_string(count) + ".txt";
    }
    // OpenLog(username + "_" + std::to_string(count) + ".txt");
    
    OpenLog(fname);

    if (mOut && mOut.is_open())
    {
        //mLogTime->restart();
        //mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << "START_OF_TEST, " << username << "_" << count << ".txt" << "\n";
        return true;
    }
    return false;
}

void GenieUsabilityLogger::OpenLog(std::string  name)
{
    //std::cout << "in GenieUsabilityLogger::OpenLog " << name.toStdString() << std::endl;
    if (!mOut.is_open())
    {
        //file does not exist yet, create
        mOut.exceptions ( ostream::failbit | ostream::badbit );
        try
        {
            mOut.open(name.c_str(), std::ios::ate);
        }
        catch (ostream::failure e)
        {
            cout << "OpenLog Exception opening/reading file";
        }
    }
}

bool GenieUsabilityLogger::FileExists(std::string  filename)
{
    // std::cout << "in GenieUsabilityLogger::FileExists" << filename.toStdString() << std::endl;
    std::ifstream ifile(filename.c_str());
    return ifile;
}

void GenieUsabilityLogger::Log(std::string  name, std::string  value, std::string  status)
{
    if (!mOut && !mOut.is_open())
    {
        return;
    }

#ifdef YS_23423423423
    if (status == BUTTON_SELECTED)
    {
        //button clicked
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ", " << status.toStdString() << "\n";
    }
    else if (status == PANIC_START)
    {
        //button clicked
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ",  "<< status.toStdString() << "\n";
    }
    else if (status == TIME_OUT)
    {
        //button clicked
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ",  "<< status.toStdString() << "\n";
    }
    else if (status == VALUE_SET)
    {
        //popup value selected
        int elapsed = 0;
        if (!mLogTime->isNull())
        {
            elapsed = mLogTime->elapsed();
        }
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ", " << status.toStdString() << ", " << elapsed << "\n";
    }
    else if (status == INCREMENT)
    {
        //button's increment
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ",  "<< status.toStdString() << "\n";
    }
    else if (status == DECREMENT)
    {
        //button's increment
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ",  "<< status.toStdString() << "\n";
    }
    else if (status == CANCELLED)
    {
        //popup cancelled
        int elapsed = 0;
        if (!mLogTime->isNull())
        {
            elapsed = mLogTime->elapsed();
        }
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ", CANCELLED, " << elapsed << "\n";
    }
    else
    {   
        mLogTime->restart();
        mOut << mLogTime->toString("hh:mm:ss.zzz").toStdString() << ", ";
        mOut << name.toStdString() << ", " << value.toStdString() << ", INFO "<< status.toStdString() << "\n";
    }
#endif
}

#ifdef YS_23423423423

void GenieUsabilityLogger::LogPanicStarted(int seconds)
{
    if (!mOut && !mOut.is_open())
    {
        return;
    }

    QTime panicTime;
    panicTime.start();

    mOut << panicTime.toString("hh:mm:ss.zzz").toStdString() << ", ";
    mOut << "PANIC MODE STARTED " << seconds << " SEC" << "\n";
}

void GenieUsabilityLogger::LogPanicAdjusted(int seconds)
{
    if (!mOut && !mOut.is_open())
    {
        return;
    }

    QTime panicTime;
    panicTime.start();

    mOut << panicTime.toString("hh:mm:ss.zzz").toStdString() << ", ";
    mOut << "PANIC MODE ADJUSTED TO " << seconds << " SEC" << "\n";
}

void GenieUsabilityLogger::LogTimeOut()
{
    if (!mOut && !mOut.is_open())
    {
        return;
    }

    QTime panicTime;
    panicTime.start();

    mOut << panicTime.toString("hh:mm:ss.zzz").toStdString();
    mOut << ", TIME OUT " << "\n";
}

#endif