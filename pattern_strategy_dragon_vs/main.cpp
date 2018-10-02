#include "gen.h"
#include "utils.h"
#include "Mob.h"

int main()
{
    cout << "War start:" << endl;      

    Mob orc("an orc pawn", 20);
    MaceAttack mace;
    orc.setAttackBehavior(&mace);

    Mob dragon("Lord Nagafen", 2000);
    FireAttack fire;
    dragon.setAttackBehavior(&fire);
    
    Client player1("Bink", 450);
    SwordAttack sword;
    player1.setAttackBehavior(&sword);

    orc.attack(&player1);
    dragon.attack(&player1);

    player1.attack(&dragon);

    cout << "War end." << endl;
    getch();
}


