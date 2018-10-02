
#ifndef _COMPRESSOR_H_ 
#define _COMPRESSOR_H_

#include "gen.h"

class CompressionIf
{
  public:   
    virtual ~CompressionIf() {}
    virtual void compress( const string & str_file_name ) = 0;
};
  
class ZIP_Compression : public CompressionIf
{
  public:
    void compress( const string & str_file_name ) 
    {
        cout << "perform ZIP compression for file -" << str_file_name << "- ... " << endl;
    }
};
  
class ARJ_Compression : public CompressionIf
{
  public:
    void compress( const string & str_file_name ) 
    {
        cout << "perform ARJ compression for file -" << str_file_name << "- ... " << endl;
    }
};
  
class RAR_Compression : public CompressionIf
{
  public:
    void compress( const string & str_file_name ) 
    {
        cout << "perform RAR compression for file -" << str_file_name << "- ... " << endl;
    }
};
#endif

