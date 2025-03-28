#include "gen.h"
/* 
* Computed Science Center. RUS. Lecture on youtube:
https://www.youtube.com/watch?v=J9RuIxDswA8&list=PLlb7e2G7aSpRs7YafQ1GgJvyRku10m1RN&index=66
*
*/

bool s_Finished = false;
bool isChopping = true;


void big_calc(std::string strHowP)
{
    std::cout << "Ok, I'm working " << strHowP << ".\n";
}

int main(int argc, char *argv[], char *envp[])
{

    std::thread threadT1(big_calc, "hard");
    std::thread threadT2(big_calc, "24/7");

    // srand(time(NULL));
    // printf ("Barron requests Olivia help.\n");
    // std::thread olivia_thread(chefOlivia);
    
    // printf ("Barron continues cooking soup.\n");
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    threadT1.join();
    threadT2.join();
    
    printf ("Application complete.\n");
    return 0;
}


