class ARR_INDEX // Array index
{
 public:
 // Constructor
  ARR_INDEX();  
 //Default constructor
  ARR_INDEX(int); 
 // Destructor
  ~ARR_INDEX();

 void SetIndex (int Index); //set index
 void SetMaxIndex(int);

 int get (void);     // return current index of array, get
 int GetMaxIndex(void);
 
 int inc (void); // Increment current index++
 int inc_r (void); // Increment current ++index
 int dec (void);// Decrement current index--
 int dec_r (void);// Decrement current --index
 int add (int Add); // Add a number to current index
 int sub (int Sub); // Decrement a number from current index

 protected: 
  int CheckRange (int ArrIndex);
  int m_Index;
  int m_MaxIndex;
  
};



// ----ARR_INDEX--FUNCTIONS:
// Constructor:
// Init maximum possible value for index.	
ARR_INDEX::ARR_INDEX(int MaxIndex)
{ 
	SetMaxIndex(MaxIndex);	
	SetIndex(0);
}
// Default constructor:
// Set maximum index value to 10.000.
ARR_INDEX::ARR_INDEX(void)
{
 SetMaxIndex(10000);
 SetIndex (0);
}
// Destructor
ARR_INDEX::~ARR_INDEX()
{
 return;
}

int ARR_INDEX::get()
{
 return m_Index;
}	 

int ARR_INDEX::CheckRange(int Index)
{ 
	if (Index < 0)
	{
	 printf ("Array index is negative!\n");
	 return 0;
	}
  else if (Index > m_MaxIndex)
	{
	 printf ("Array index is out of range!\n");
   return m_MaxIndex;
	}
	// default:
	return Index;
}

void ARR_INDEX::SetIndex(int Index)
{
  m_Index = CheckRange(Index);	
}

int ARR_INDEX::add(int Add)
{
  int var;
	var = m_Index + Add;
	m_Index = CheckRange(var);
	return m_Index;
}

int ARR_INDEX::inc(void)
{
  int var;
	var = m_Index++;
	m_Index = CheckRange(var);
	return m_Index;
}

int ARR_INDEX::inc_r(void)
{
  int var;
	int var2;
	var2= m_Index;
	var = m_Index++;
	m_Index = CheckRange(var);
	return var2;
}

int ARR_INDEX::sub(int Sub)
{
  int var;
	var = m_Index - Sub;
	m_Index = CheckRange(var);
	return m_Index;
}

int ARR_INDEX::dec(void)
{
  int var;
	var = m_Index--;
	m_Index = CheckRange(var);
	return m_Index;
}

int ARR_INDEX::dec_r(void)
{
  int var;
	int var2;
  var2= m_Index;
	var = m_Index--;
	m_Index = CheckRange(var);
	return var2;
}

void ARR_INDEX::SetMaxIndex(int MaxIndex)
{
 if (MaxIndex >= 0)
	m_MaxIndex = MaxIndex;
 else 
  m_MaxIndex = 0;
}

int ARR_INDEX::GetMaxIndex (void)
{
 return m_MaxIndex;
}

