#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"


using namespace std;

int main(){
    srand(time(NULL));
    Dungeon dungeon = Dungeon();
    dungeon.runDungeon();
    system("pause");
    return 0;
}
