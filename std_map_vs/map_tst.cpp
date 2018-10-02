//============================================================
//
// Description:
//============================================================
#include "map_tst.h"

using namespace std;

void smpl_map()
{
    map<string, int> mymap;
    mymap["b"] = 1;
    mymap["a"] = 2;
    mymap["c"] = 5;
    mymap["d"] = 3;

    std::map<string, int>::const_iterator it;
    
    for(it=mymap.begin(); it!=mymap.end(); ++it) 
    {
        std::cout << (it)->first << " = " << (it)->second << std::endl;  
    }

}

void map_test () 
{
    map<int, string> Employees; 
    // Assignment using array index notation
    Employees[5234] = "Mike C.";
    Employees[3374] = "Charlie M.";
    Employees[1923] = "David D.";
    Employees[7582] = "John A.";
    Employees[5328] = "Peter Q.";

    cout << "Employees[3374]=" << Employees[3374] << endl << endl;
    cout << "Map size: " << Employees.size() << endl;
    
    map<int, string>::iterator ii;

    // for( map<int, string>::iterator ii=Employees.begin(); ii!=Employees.end(); ++ii)
    for(ii = Employees.begin(); ii != Employees.end(); ++ii)
        {
            // cout << (*ii).first << ": " << (*ii).second << endl;
            cout << ii->first << ": " << ii->second << endl;
        }
}
