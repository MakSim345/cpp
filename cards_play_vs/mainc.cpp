#include "gen.h" 
#include "deck.h"

struct Time
{
    int m;
    int h;
    int s;
};

typedef struct
{
    // std::string _name;
    char* _name;
    //int m;
    //int h;
    //int s;
    int ms;
} my_time;

void print_my_struct(my_time* _to_print)
{
    printf ("ms: %d\n", _to_print->ms);
    printf ("name: %s\n", _to_print->_name);
    // cout << "name:" << _to_print._name << endl;
    /*cout << "h:" << _to_print._name << endl;
    cout << "m:" << _to_print._name << endl;
    cout << "s:" << _to_print._name << endl;
    cout << "ms:" << _to_print._name << endl;   */
}


int main( int argc, char *argv[] )
{
    //char *suit[4] = {"4epBu", "6y6HbI", "TpeFbI", "nuku"};
    
    std::string suit[4] = {"4epBu", "6y6HbI", "TpeFbI", "nuku"};

    std::string face[13] = {"Ty3", "gBojka", "Tpojka", "4eTBepka", 
                      "nqTepka", "wecTepka", "ceMepka", "BocMepka",
                      "geBqTka", "gecqTka", "BaLeT", "gaMa", "KopoLb"};
    
    // int deck[4][13] = {0};
    
    srand (time(NULL));
    
    // shuffle (deck);
    deck _deck = deck();
    _deck.shuffle();

    my_time _mt;
    _mt.ms = 134;
    _mt._name = "test";
    printf ("name: %s\n", _mt._name);
    print_my_struct(&_mt);
    std::cout << Timestamp() << "\n";
    _deck.print_deck();
    system("PAUSE");
    return 0;   
}


 
