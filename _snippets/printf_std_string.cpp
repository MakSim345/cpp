#include <iostream>
#include <string>

int main()
{
    using namespace std;

    string myString = "Press ENTER to quit program!";
    cout << "Come up and C++ me some time." << endl;
    printf("Follow this command: %s", myString.c_str()); //note the use of c_str
    cin.get();

    // string to integer:
    int i_dec = std::stoi(myString);

    return 0;
}

