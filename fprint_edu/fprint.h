#ifndef _FPRINT_H_
#define _FPRINT_H_

#include "gen.h"
#include "person.h"

class fPrint
{
public:
    ostream & m_os;

    // constructor :
    fPrint (ostream & os)
        :m_os(os)
    {
         ;
    }

    void operator () (const pair <const int, const Person> &map_item) const
    {
     m_os << "# " << map_item.first << " - name :"
         << map_item.second.GetName()
         << " - " << map_item.second.GetEmail()
         << ", age " << map_item.second.GetAge() << "\n";  
    }

private:
};


#endif
