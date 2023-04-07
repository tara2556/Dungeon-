#include "Record.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"

using namespace std;

/* This is the record system. Get the information of the  */
/* player and rooms then save them to (a) file(s). Notice */
/* that using pass by reference can prevent sending the   */
/* whole vector to the function.                          */


void savePlayer(Player* player, ofstream& out) {

}
void saveRooms(vector<Room>&, ofstream&);
void loadPlayer(Player*, ifstream&);
void loadRooms(vector<Room>&, ifstream&);


void saveToFile(Player*, vector<Room>&) {

}
void loadFromFile(Player*, vector<Room>&);

