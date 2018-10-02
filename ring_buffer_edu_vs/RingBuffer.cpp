#include "RingBuffer.h"

#include <string.h>
#include <stdio.h>  

Ring_Buffer::Ring_Buffer()
{
 
}
Ring_Buffer::Ring_Buffer(int buffer_size )
{
    //printf ("Constructor. buffer_size  = %d\n", buffer_size );
    getindex = 0;
    putindex = 0;
    buffersize = 0;
    m_buffer_size = buffer_size;
    ringbuffer = new unsigned char[m_buffer_size];
}
    // Try to add data to the buffer. After the call, 'len' contains
    // the amount of bytes actually buffered.
int Ring_Buffer::Put_Data(char c)
{
  if ( buffersize >= m_buffer_size )
    return -1;

  ringbuffer[ putindex ] = c;
  putindex++;
  
  if ( putindex >= m_buffer_size )
      putindex = 0;
  
  buffersize++;
  return 0;
}


int Ring_Buffer::Get_Data( void)
{
 
 char c;
  if ( !m_buffer_size )
    return -1;
  
  buffersize--;
  c = ringbuffer[ getindex ];
  getindex++;
  if ( getindex >= m_buffer_size )
    getindex = 0;

  return c;
}

 void Ring_Buffer::PrintDump ()

 {
   printf ("Dump: \n");
   for (int i=0; i<m_buffer_size; i++)
   {
    printf ("%d:[%c]  ", i, ringbuffer[i]);
   }
   printf ("\n---------------------------------------------------------\n");
 }

/*



 Ring_Buffer::Ring_Buffer()
    {}

 Ring_Buffer::Ring_Buffer( void* buffer, unsigned int buffer_size )
    {
        //printf ("Constructor. buffer_size  = %d\n", buffer_size );
        m_buffer_size = buffer_size;
        m_buff = (unsigned char*)buffer;        
        m_buff_end = m_buff + m_buffer_size;
        m_load_ptr = m_consume_ptr = m_buff;
        m_max_load = m_buffer_size; 
        //printf ("Constructor. m_buffer_size  = %d\n", m_buffer_size );
        m_max_consume = m_data_in_buffer = 0;
        Update_State();
    }

 void Ring_Buffer::PrintDump ()

 {
   printf ("Dump: \n");
   for (int i=0; i<m_buffer_size; i++)
   {
    printf ("%d:[%d]  ", i, m_buff[i]);
   }
   printf ("\n---------------------------------------------------------\n");
 }
    // Try to add data to the buffer. After the call, 'len' contains
    // the amount of bytes actually buffered.
 void Ring_Buffer::Buffer_Data( const void* data, unsigned int& len )
    {
        if ( len > (unsigned int)m_max_load )
            len = (unsigned int)m_max_load;
        memcpy( m_load_ptr, data, len );
        m_load_ptr += len;
        m_data_in_buffer += len;
        Update_State();
    }

    // Request 'len' bytes from the buffer. After the call,
    // 'len' contains the amount of bytes actually copied.
 void Ring_Buffer::Get_Data( void* outData, unsigned int& len )
    {
        if ( len > (unsigned int)m_max_consume )
            len = (unsigned int)m_max_consume;
        memcpy( outData, m_consume_ptr, len );
        m_consume_ptr += len;
        m_data_in_buffer -= len;
        Update_State();
    }

    // Tries to skip len bytes. After the call,
    // 'len' contains the realized skip.
 void Ring_Buffer::SkipData( unsigned int& len )
    {
        unsigned int requestedSkip = len;
        for ( int i=0; i<2; ++i ) // This may wrap  so try it twice
        {
            int skip = (int)len;
            if ( skip > m_max_consume )
                skip = m_max_consume;
            m_consume_ptr += skip;
            m_data_in_buffer -= skip;
            len -= skip;
            Update_State();
        }
        len = requestedSkip - len;
    }

void Ring_Buffer::Update_State()
    {
        if (m_consume_ptr == m_buff_end)
             m_consume_ptr = m_buff;
        
        if (m_load_ptr == m_buff_end)        
          m_load_ptr = m_buff;

        if (m_load_ptr == m_consume_ptr)
        {
            if ( m_data_in_buffer > 0 )
            {
                m_max_load = 0;
                m_max_consume = m_buff_end - m_consume_ptr;
            }
            else
            {
                m_max_load = m_buff_end - m_load_ptr;
                m_max_consume = 0;
            }
        }
        else if ( m_load_ptr > m_consume_ptr )
        {
            m_max_load = m_buff_end - m_load_ptr;
            m_max_consume = m_load_ptr - m_consume_ptr;
        }
        else
        {
            m_max_load = m_consume_ptr - m_load_ptr;
            m_max_consume = m_buff_end - m_consume_ptr;
        }
    }
*/

