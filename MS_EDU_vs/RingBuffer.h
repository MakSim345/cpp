class Ring_Buffer
{
public:
	// Constuctor:
	Ring_Buffer();
	Ring_Buffer(int buffer_size );
	
	// Try to add data to the buffer. After the call, 'len' contains
	// the amount of bytes actually buffered.
	int Put_Data( char c);
	
	// Request 'len' bytes from the buffer. After the call,
	// 'len' contains the amount of bytes actually copied.
	int Get_Data( void);
	
	// Tries to skip len bytes. After the call,
	// 'len' contains the realized skip.
	// void SkipData( unsigned int& len );
	
	// The amount of data the buffer can currently receive on one Buffer_Data() call.
	//inline unsigned int Free_Space()    { return (unsigned int)m_max_load; }

	// The total amount of data in the buffer. Note that it may not be continuous: you may need
	// two successive calls to Get_Data() to get it all.
	//inline unsigned int Buffered_Bytes() { return (unsigned int)m_data_in_buffer; }
    void PrintDump(); 
private:
    
 unsigned char *ringbuffer;
 unsigned short getindex;
 unsigned short putindex;
 unsigned short buffersize;
 unsigned short m_buffer_size;
 void Update_State();
	


};