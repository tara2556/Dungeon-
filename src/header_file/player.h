#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"
#include "skill.h"

using namespace std;

class Item;
class Skill;

class Player : public GameCharacter
{
private:
	Room* currentRoom;
	Room* previousRoom;
	vector<Item> inventory;
	int occupation;
	int coin;
	int maxMp;
	int currentMp;
	Skill* skill;
	vector<Skill> skills;
	int** map;
	int mapLength;
	int mapWidth;
public:
	Player();
	Player(string, int, int, int, int, int, int, Skill*);
	void addItem(Item);
	void revive(int);
	/* Virtual function that you need to complete   */
	/* In Player, this function should show the     */
	/* status of player.                            */
	bool triggerEvent(Object*);
	void initializeMap(int, int, int, int);
	void showMap(int);
	/* Set & Get function*/
	void setCurrentRoom(Room*);
	void setPreviousRoom(Room*);
	void setInventory(vector<Item>);
	void setOccupation(int);
	void setCoin(int);
	void setMaxMp(int);
	void setCurrentMp(int);
	void checkInventory();
	void setSkill(Skill*);
	void setSkills(vector<Skill> s);
	void setMap(int, int, int);
	void setMapLength(int);
	void setMapWidth(int);
	int getMapLength();
	int getMapWidth();
	Skill* getSkill();
	int** getmap();
	vector<Skill> getSkills();
	Room* getCurrentRoom();
	Room* getPreviousRoom();
	vector<Item> getInventory();
	string getOccupation();
	void useSkill();
	int getCoin();
	int getMaxMp();
	int getCurrentMp();
};
ostream& operator<<(ostream& out, Player& player);

#endif // PLAYER_H_INCLUDED
