#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"
#include "Boss.h"
using namespace std;

class Dungeon{
private:
    Player player;
    vector<Room*> rooms;
    vector<NPC> npcs;
    vector<Item> items;
    vector<Monster> monsters;
    vector<string> monsterClaim;
    vector<Boss> bosses;
    vector<Skill> skills;
    int choosenAction;
    bool finishGame = 0;
public:
    Dungeon();
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's moveing action */
    vector<string> handleMovement(Room*);

    /* Deal with player's iteraction with objects in that room */
    bool handleEvent(Object*, int, Room*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(vector<Object*>);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    void createNpc();

    void createBoss();

    void createSkill();

    void promptSkill(Player*);

    void createItem();
    /* Deal with the whole game process */
    void runDungeon();

    Item setIntensity(string, string, int);

    void createMonster();

    void initMonsterClaim();

    Player getPlayer(); 


};


#endif // DUNGEON_H_INCLUDED
