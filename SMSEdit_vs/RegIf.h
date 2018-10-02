class RegIf
{
public:
    RegIf();
	 ~RegIf();
    void Start();

		void Set(int); 
    int  Get();
		int WriteIniDword(int *Value, TCHAR *SubKey, TCHAR *Key);
		int ReadIniDword (int *Value, TCHAR *SubKey, TCHAR *Key);	  
    
private:

	HKEY hKey;
	LONG Err;
	DWORD m_dwSizeP, m_dwSizeS;

};