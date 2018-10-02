void printHex(int a)
{
    cout << hex << "0x" << a << "\n";
}

void printHex(std::string a)
{
    unsigned int k;
    for (int i = 0; i<a.size(); i++)
    {
        k = (unsigned int)a[i];
        cout << " 0x" << hex << uppercase  << k;        
        // cout << hex << k;
    }
    cout << "\n";
}
