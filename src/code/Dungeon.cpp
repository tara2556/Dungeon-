#include "Dungeon.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <thread>
#include <chrono>
#include <locale>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"
#include "Object.h"
#include "Boss.h"

using namespace std;



Dungeon::Dungeon() {}
/* Create a new player, and give him her basic status */
void Dungeon::createPlayer() {
	string name;
	int occupation;
	cout << "May I ask for your name, adventurer?\nEnter your name: ";
	getline(cin, name);
	player.setName(name);
	cout << "What's your Occupation " << name << "?\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "1. Warrior\n"
		<< "2. Knight\n"
		<< "3. Monk\n"
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	char temp;
	cin >> temp;
	temp -= '0';
	while (temp <= 0 || temp > 3) {
		cout << "No this action!\n";
		cout << "What's your Occupation " << name << "?\n";
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
			<< "1. Warrior\n"
			<< "2. Knight\n"
			<< "3. Monk\n"
			<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cin >> temp;
		temp -= '0';
	}
	occupation = temp;	
	player.setOccupation(occupation);
	vector<Item> inventory;
	player.setInventory(inventory);
	player.setTag("player");
	player.setCoin(100);
	player.setSkill(&skills[(occupation - 1) * 3]);
	player.setSkills(skills);
}

void Dungeon::promptSkill(Player* player) {
	cout << "Your skill \"" << player->getSkill()->getEffect() << "\" is become to \"";
	player->setSkill(&skills[player->getSkill()->getEffectTag() * 3 + player->getSkill()->getLevel() + 1]);
	cout << player->getSkill()->getEffect() << "\"\n";
}
/* Create a map, which include several different rooms */
void Dungeon::createMap() {
	//intialize the first room(hall)
	vector<Object*> obj;
	bool checkSuccessfullyAdd;
	bool npcIsExist, monsterIsExist, treasureIsNotExist;
	Room* originRoom = new(Room);
	originRoom->setIsExit(1);
	originRoom->setIndex(0);
	originRoom->setObjects(obj);
	originRoom->setX(25);
	originRoom->setY(25);
	rooms.push_back(originRoom);
	for (int i = 1; i <= 30; i++) {
		vector<Object*> needObj;
		npcIsExist = rand() % 3;
		monsterIsExist = rand() % 2;
		treasureIsNotExist = rand() % 5;
		if (i == 30) {
			int bossPos = rand() % bosses.size();
			int pos = 30;
			needObj.push_back(&bosses[bossPos]);
			checkSuccessfullyAdd = 0;
			Room* room = new(Room);
			room->setIsExit(0);
			room->setIndex(i);
			room->setObjects(needObj);
			rooms.push_back(room);
			while (!checkSuccessfullyAdd) {
				pos--;
				while (pos == rooms.size() - 1)pos = rand() % rooms.size();
				int dir = rand() % 4;
				//prevent we can't add room on the current room
				bool cover = 0;
				switch (dir) {
				case 0:
					if (rooms[pos]->getUpRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() == rooms[i]->getX()) && (rooms[pos]->getY() - 1 == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setDownRoom(rooms[pos]);
						rooms[pos]->setUpRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX());
						rooms.back()->setY(rooms[pos]->getY() - 1);
						checkSuccessfullyAdd = 1;
					}
					break;
				case 1:
					if (rooms[pos]->getDownRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() == rooms[i]->getX()) && (rooms[pos]->getY() + 1 == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setUpRoom(rooms[pos]);
						rooms[pos]->setDownRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX());
						rooms.back()->setY(rooms[pos]->getY() + 1);
						checkSuccessfullyAdd = 1;
					}
					break;
				case 2:
					if (rooms[pos]->getLeftRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() - 1 == rooms[i]->getX()) && (rooms[pos]->getY() == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setRightRoom(rooms[pos]);
						rooms[pos]->setLeftRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX() - 1);
						rooms.back()->setY(rooms[pos]->getY());
						checkSuccessfullyAdd = 1;
					}
					break;
				case 3:
					if (rooms[pos]->getRightRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() + 1 == rooms[i]->getX()) && (rooms[pos]->getY() == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setLeftRoom(rooms[pos]);
						rooms[pos]->setRightRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX() + 1);
						rooms.back()->setY(rooms[pos]->getY());
						checkSuccessfullyAdd = 1;
					}
					break;
				}


			}
		}
		else {
			if (npcIsExist) {
				int npcPos = rand() % npcs.size();
				needObj.push_back(&npcs[npcPos]);

			}
			if (monsterIsExist) {
				needObj.push_back(&monsters[i + rand() % 3]);
			}
			if (!treasureIsNotExist) {
				int treasurePos = rand() % items.size();
				while (items[treasurePos].getRare() != "rare" && items[treasurePos].getRare() != "legendary") treasurePos = rand() % items.size();
				needObj.push_back(&items[treasurePos]);
			}
			//add room and check whether the current room cover other rooms
			checkSuccessfullyAdd = 0;
			Room* room = new(Room);
			room->setIsExit(1);
			room->setIndex(i);
			room->setObjects(needObj);
			rooms.push_back(room);
			while (!checkSuccessfullyAdd) {
				int pos = rand() % rooms.size();
				while (pos == rooms.size() - 1)pos = rand() % rooms.size();
				int dir = rand() % 4;
				//prevent we can't add room on the current room
				bool cover = 0;
				switch (dir) {
				case 0:
					if (rooms[pos]->getUpRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() == rooms[i]->getX()) && (rooms[pos]->getY() - 1 == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setDownRoom(rooms[pos]);
						rooms[pos]->setUpRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX());
						rooms.back()->setY(rooms[pos]->getY() - 1);
						checkSuccessfullyAdd = 1;
					}
					break;
				case 1:
					if (rooms[pos]->getDownRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() == rooms[i]->getX()) && (rooms[pos]->getY() + 1 == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setUpRoom(rooms[pos]);
						rooms[pos]->setDownRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX());
						rooms.back()->setY(rooms[pos]->getY() + 1);
						checkSuccessfullyAdd = 1;
					}
					break;
				case 2:
					if (rooms[pos]->getLeftRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() - 1 == rooms[i]->getX()) && (rooms[pos]->getY() == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setRightRoom(rooms[pos]);
						rooms[pos]->setLeftRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX() - 1);
						rooms.back()->setY(rooms[pos]->getY());
						checkSuccessfullyAdd = 1;
					}
					break;
				case 3:
					if (rooms[pos]->getRightRoom() == NULL) {
						for (int i = 0; i < rooms.size(); i++) {
							if (i != pos) {
								if ((rooms[pos]->getX() + 1 == rooms[i]->getX()) && (rooms[pos]->getY() == rooms[i]->getY())) {
									cover = 1;
									break;
								}
							}
						}
						if (cover) continue;
						rooms.back()->setLeftRoom(rooms[pos]);
						rooms[pos]->setRightRoom(rooms.back());
						rooms.back()->setX(rooms[pos]->getX() + 1);
						rooms.back()->setY(rooms[pos]->getY());
						checkSuccessfullyAdd = 1;
					}
					break;
				}

			}
		}
	}
	int u = 50, d = 0, r = 0, l = 50;
	for (int i = 0; i <= 30; i++) {
		u = min(u, rooms[i]->getY());
		d = max(d, rooms[i]->getY());
		l = min(l, rooms[i]->getX());
		r = max(r, rooms[i]->getX());

	}
	this->player.initializeMap(u, d, l, r);
	for (int i = 0; i <= 30; i++) {
		this->player.setMap(rooms[i]->getY() - u, rooms[i]->getX() - l, rooms[i]->getIndex());
	}

}

/* Deal with player's moveing action */
vector<string> Dungeon::handleMovement(Room* roomPos) {
	vector<string> existRoom;
	Room currentRoom = *roomPos;
	if (currentRoom.getDownRoom() != NULL) {
		existRoom.push_back("downRoom");
	}
	if (currentRoom.getUpRoom() != NULL) {
		existRoom.push_back("upRoom");
	}
	if (currentRoom.getRightRoom() != NULL) {
		existRoom.push_back("rightRoom");
	}
	if (currentRoom.getLeftRoom() != NULL) {
		existRoom.push_back("leftRoom");
	}
	return existRoom;
}

/* Deal with player's iteraction with objects in that room */
/*type 0 : npc*/
/*type 1 : monster*/
/*type 2 : item*/
bool Dungeon::handleEvent(Object* room, int type, Room* currentRoom) {
	bool determine = 0;

	if (type == 0) {
		cout << "Are you sure you want to talk with " << room->getName() << "?\n"
			<< "0.NO\n"
			<< "1.Yes\n";
		char temp;
		cin >> temp;
		temp -= '0';
		if (temp >= 0 && temp <= 1) determine = temp;
		else {
			cout << "No this action!\n";
			return 0;
		}
		if (!determine) {
			return determine;
		}
		NPC* npc = dynamic_cast<NPC*>(room);
		npc->triggerEvent(&player);
	}
	else if (type == 1) {
		cout << "Are you sure you want to attack " << room->getName() << "?\n"
			<< "0.NO\n"
			<< "1.Yes\n";
		char temp;
		cin >> temp;
		temp -= '0';
		if (temp >= 0 && temp <= 1) determine = temp;
		else {
			cout << "No this action!\n";
			return 0;
		}
		if (!determine) {
			return determine;
		}
		Monster* monster = dynamic_cast<Monster*>(room);
		if (!monster->triggerEvent(&player)) {
			return 0;
		}
		currentRoom->popObject(room);
	}
	else if (type == 2) {
		cout << "Do you want to open this mysterious bag?\n"
			<< "0.NO\n"
			<< "1.Yes\n";
		char temp;
		cin >> temp;
		temp -= '0';
		if (temp >= 0 && temp <= 1) determine = temp;
		else {
			cout << "No this action!\n";
			return 0;
		}
		if (!determine) {
			return determine;
		}
		Item* item = dynamic_cast<Item*>(room);
		item->triggerEvent(&player);
		currentRoom->popObject(room);
	}
	else {
		cout << "You really want to challenge me? little coward?\n"
			<< "0.NO\n"
			<< "1.Yes\n";
		char temp;
		cin >> temp;
		temp -= '0';
		if (temp >= 0 && temp <= 1) determine = temp;
		else {
			cout << "No this action!\n";
			return 0;
		}
		if (!determine) {
			cout << "haha! you dumbass\n";
			return determine;
		}
		Boss* boss = dynamic_cast<Boss*>(room);
		if (boss->triggerEvent(&player)) this->finishGame = 1;
		else return 0;
		currentRoom->popObject(boss);
	}
	return 1;
}


void Dungeon::createNpc() {
	ifstream ifs("NPC.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "fail\n";
		return;
	}
	string npcDescription;
	bool itemBeUsed = 0;
	int itemPos = 0;
	while (getline(ifs, npcDescription)) {
		if (npcDescription == "") break;
		int blankCount = 0, cuttingPos = 0, itemCount;
		vector<Item> com;
		itemCount = rand() % 4;
		if (itemBeUsed) itemCount = 0;
		//build item array
		for (int i = 0; i < items.size(); i++) {
			if (npcDescription[i] == ' ') blankCount++;
			if (blankCount == 3) {
				cuttingPos = i;
				break;
			}
		}
		//push item
		for (int i = itemPos; i < itemPos + itemCount; i++) {
			if (i >= items.size()) break;
			com.push_back(items[i]);
		}
		itemPos += itemCount;
		if (itemPos >= items.size()) {
			itemBeUsed = 1;
		}
		NPC npc(npcDescription.substr(0, cuttingPos), npcDescription.substr(cuttingPos, npcDescription.size()), com);
		npc.setTag("npc");
		npcs.push_back(npc);
	}
	ifs.close();
}

void Dungeon::createBoss() {
	ifstream ifs1("boss_name.txt", ios::in);
	ifstream ifs2("boss_descripation.txt", ios::in);
	string s1, s2;
	while (getline(ifs1, s1)) {
		int atk = 0, def = 0, hp = 0;
		getline(ifs2, s2);
		if (s2 == "") break;
		while (atk < 350) atk = rand() % 500 + 1;
		while (def < 300) def = rand() % 400 + 1;
		while (hp < 2000) hp = rand() % 2500 + 1;
		Boss boss(s1, s2, atk, def, hp);
		boss.setTag("boss");
		bosses.push_back(boss);
	}
	ifs1.close();
	ifs2.close();
}

void Dungeon::createItem() {
	ifstream ifs("weapons.txt", ios::in);
	string itemName;
	while (getline(ifs, itemName)) {
		int blankCount = 0, cuttingPos = 0, rare = rand() % 100;
		for (int i = 0; i < itemName.length(); i++) {
			if (itemName[i] == ' ') blankCount++;
			if (blankCount) {
				cuttingPos = i;
				break;
			}
		}
		if (rare > 60) rare = 0;
		else if (rare > 30 && rare <= 60) rare = 1;
		else if (rare > 10 && rare <= 30) rare = 2;
		else rare = 3;
		Item item = Dungeon::setIntensity(itemName.substr(0, cuttingPos), itemName.substr(cuttingPos, itemName.size()), rare);
		item.setTag("item");
		int prize = 0;
		if (item.getRare() == "broken") {
			prize = rand() % 50 + 1;
		}
		else if (item.getRare() == "normal") {
			while (prize <= 50) {
				prize = rand() % 100 + 1;
			}
		}
		else if (item.getRare() == "rare") {
			while (prize <= 150) {
				prize = rand() % 200 + 1;
			}
		}
		else if (item.getRare() == "legendary") {
			while (prize <= 200) {
				prize = rand() % 300 + 1;
			}
		}
		item.setPrice(prize);
		items.push_back(item);
	}

	ifs.close();
}
Item Dungeon::setIntensity(string name, string descripation, int rare) {
	int atk = 0, def = 0, hp = 0;
	switch (rare) {
	case 0:
		atk = rand() % 6;
		def = rand() % 6;
		hp = rand() % 6;
		break;
	case 1:
		atk = rand() % 20;
		def = rand() % 20;
		hp = rand() % 40;
		atk = (atk < 6) ? 6 : atk;
		def = (def < 6) ? 6 : def;
		hp = (hp < 20) ? 20 : hp;
		break;
	case 2:
		atk = rand() % 50;
		def = rand() % 50;
		hp = rand() % 100;
		atk = (atk < 25) ? 25 : atk;
		def = (def < 25) ? 25 : def;
		hp = (hp < 60) ? 60 : hp;
		break;
	case 3:
		atk = rand() % 200;
		def = rand() % 200;
		hp = rand() % 500;
		atk = (atk < 150) ? 150 : atk;
		def = (def < 150) ? 150 : def;
		hp = (hp < 300) ? 300 : hp;
		break;
	}
	Item item(name, descripation, atk, def, hp, rare);
	return item;
}

void Dungeon::createMonster() {
	this->initMonsterClaim();
	ifstream ifs("monsters.txt", ios::in);
	string monsterName;
	int monsterTag = 0;
	while (getline(ifs, monsterName)) {
		int atk, def, hp;
		int deviation = rand() % 100;
		if (monsterTag >= 10) deviation = rand() % 200;
		else if (monsterTag >= 20) deviation = rand() % 300;
		atk = monsterTag * 5 + deviation / 5;
		def = monsterTag * 2 + deviation / 4;
		hp = monsterTag * 5 + deviation;
		Monster monster(monsterName, atk, def, hp);
		monster.setTag("monster");
		monster.setDescripation(this->monsterClaim[rand() % monsterClaim.size()]);
		monsters.push_back(monster);
		monsterTag++;
	}
}

void Dungeon::initMonsterClaim() {
	ifstream ifs("monsters_claim.txt", ios::in);
	string declare;
	while (getline(ifs, declare)) {
		this->monsterClaim.push_back(declare);
	}
}

/* Deal with all game initial setting       */
/* Including create player, create map etc  */
void Dungeon::startGame() {
	//opening
	cout << "Welcome, adventurer! You have entered a world of danger and excitement, where the \n";
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "darkest dungeons and the most incredible treasures await you. Whether you are a \n";
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "seasoned explorer or a fresh-faced newcomer, you are about to embark on an\n";
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "adventure that will test your skills, your bravery, and your mettle.\n\n";
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "Remember, adventurer, this world is filled with danger, but also with great rewards\n";
	this_thread::sleep_for(chrono::milliseconds(500));
	cout << "We wish you the best of luck on your journey, and may the dungeon gods smile upon you!\n";
	this_thread::sleep_for(chrono::milliseconds(500));
	//Enter character name
	this->createSkill();
	this->createPlayer();
	cout << "Congratulations! The following is your status, " << player.getName() << '\n' << player;
	this->createItem();
	this->createNpc();
	this->createMonster();
	this->createBoss();
	this->createMap();
	cout << "Hi! Adventurer! you are in the hall now. Please choose your action next!\n";
	player.setCurrentRoom(*rooms.begin());

}

/* Deal with the player's action     */
/* including showing the action list */
/* that player can do at that room   */
/* and dealing with player's input   */
void Dungeon::chooseAction(vector<Object*> room) {
	cout << "you can do the following action: " << '\n';
	vector<string> existRoom = this->handleMovement(player.getCurrentRoom());
	for (int i = 0; i < existRoom.size(); i++) {
		cout << i << ". go " << existRoom[i] << '\n';
	}
	for (int i = existRoom.size(); i < existRoom.size() + room.size(); i++) {
		int pos = i - existRoom.size();
		if (room[pos]->getTag() == "npc") {
			cout << i << ". talk with " << room[pos]->getName() << '\n';
		}
		else if (room[pos]->getTag() == "item") {
			cout << i << ". open this mysterious treasure\n";
		}
		else cout << i << ". attack " << room[pos]->getName() << '\n';
	}
	cout << existRoom.size() + room.size() << ". check my status\n";
	cout << existRoom.size() + room.size() + 1 << ". check the map\n";
	cout << "which one you want to do?\n";
	char temp;
	cin >> temp;
	temp -= '0';
	if (temp >= 0 && temp <= 9) this->choosenAction = temp;
	else {
		cout << "No this action!\n";
		return;
	}
	if (this->choosenAction < 0 || this->choosenAction > existRoom.size() + room.size() + 1) {
		cout << "No this action!\n";
		return;
	}
	if (this->choosenAction < existRoom.size()) {
		player.setPreviousRoom(player.getCurrentRoom());
		if (existRoom[this->choosenAction] == "upRoom") {
			player.setCurrentRoom(player.getPreviousRoom()->getUpRoom());
		}
		else if (existRoom[this->choosenAction] == "downRoom") {
			player.setCurrentRoom(player.getPreviousRoom()->getDownRoom());
		}
		else if (existRoom[this->choosenAction] == "rightRoom") {
			player.setCurrentRoom(player.getPreviousRoom()->getRightRoom());
		}
		else if (existRoom[this->choosenAction] == "leftRoom") {
			player.setCurrentRoom(player.getPreviousRoom()->getLeftRoom());
		}
		cout << "You arrive at the room " << player.getCurrentRoom()->getIndex() << '\n';
		if (player.getCurrentRoom()->getIndex() == 30) {
			cout << "Warning! you are in the final boss room."
				<< " Check your status and make sure you want to challenge the god in the Dungeon\n";
		}
	}
	else {
		int choosen = choosenAction - existRoom.size();
		bool determine = 0;
		if (choosen == room.size() + 1) {
			this->player.showMap(player.getCurrentRoom()->getIndex());
		}
		else if (choosen == room.size()) {
			cout << player << '\n';
			this->player.checkInventory();
		}
		else if (room[choosen]->getTag() == "npc") {
			determine = handleEvent(room[choosen], 0, this->player.getCurrentRoom());
			if (!determine) return;
		}
		else if (room[choosen]->getTag() == "monster") {
			determine = handleEvent(room[choosen], 1, this->player.getCurrentRoom());
			if (!determine) return;
		}
		else if (room[choosen]->getTag() == "item") {
			determine = handleEvent(room[choosen], 2, this->player.getCurrentRoom());
			if (!determine) return;
		}
		else if (room[choosen]->getTag() == "boss") {
			determine = handleEvent(room[choosen], 3, this->player.getCurrentRoom());
			if (!determine) return;
		}

	}
}

void Dungeon::createSkill() {
	vector<string> skillName(3);
	vector<string> skillLevel(3);
	skillName[0] = "Critical Strike";
	skillName[1] = "Shielding Aura";
	skillName[2] = "Healing Spell";
	skillLevel[0] = "Novice ";
	skillLevel[1] = "Intermediate ";
	skillLevel[2] = "Advenced ";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Skill temp(skillLevel[j] + skillName[i], i, j);
			string des, mdes;
			switch (i) {
			case 0:
				des = "It will increase your attack by ";
				mdes = "It will increase attack of enemies by ";
				switch (j) {
				case 0:
					des += "20% and cause a lot of damage to your enemies.\n";
					mdes += "20% and cause a lot of damage to you.\n";
					break;
				case 1:
					des += "50% and cause significant damage to your enemies.\n";
					mdes += "50% and cause a lot of damage to you.\n";
					break;
				case 2:
					des += "80% and cause tremendous damage to your enemies.\n";
					mdes += "80% and cause a lot of damage to you.\n";
					break;
				}
				break;
			case 1:
				des = "It will increase your defense by ";
				mdes = "It will increase defense of enemies by ";
				switch (j) {
				case 0:
					des += "20% and protect yourself from attacks of enemies.\n";
					mdes += "15% and cause your attack to be nerfed.\n";
					break;
				case 1:
					des += "50% and protect yourself from attacks of enemies.\n";
					mdes += "30% and cause your attack to be nerfed.\n";
					break;
				case 2:
					des += "80% and protect yourself from attacks of enemies.\n";
					mdes += "45% and cause your attack to be nerfed.\n";
					break;
				}
				break;
			case 2:
				des = "It will heal you and restore ";
				mdes = "The floor is covered in spikes, causing continuous damage. ";
				switch (j) {
				case 0:
					des += "10% your max HP.\n";
					mdes += "Each round, you will receive damage equal to 5% of your max HP.\n";
					break;
				case 1:
					des += "30% your max HP.\n";
					mdes += "Each round, you will receive damage equal to 10% of your max HP.\n";
					break;
				case 2:
					des += "45% your max HP.\n";
					mdes += "Each round, you will receive damage equal to 15% of your max HP.\n";
					break;
				}
				break;
			}
			temp.setDescripation(des);
			temp.setMonsterSkillDescripation(mdes);
			skills.push_back(temp);
		}
	}
}

Player Dungeon::getPlayer() {
	return this->player;
}
/* Check whether the game should end or not */
/* Including player victory, or he/she dead */
bool Dungeon::checkGameLogic() {
	if (this->player.checkIsDead()) {
		ifstream ifs1("emoji1.txt", ios::in);
		string output1;
		while (getline(ifs1, output1)) cout << output1 << '\n';
		ifs1.close();
		return 1;
	}
	if (finishGame) {
		cout << this->player.getName()
			<< "! Your effort and determination have paid off.\n";
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << " Congratulations on completing this challenging dungeon game!";
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "Game over! See you next time! Oh maybe not\n";
		ifstream ifs2("emoji2.txt", ios::in);
		string output2;
		while (getline(ifs2, output2)) cout << output2 << '\n';
		ifs2.close();
		return 1;
	}
	return 0;
}

/* Deal with the whole game process */
void Dungeon::runDungeon() {
	this->startGame();
	while (1) {
		chooseAction(player.getCurrentRoom()->getObjects());
		this->player.setCurrentMp((player.getCurrentMp() + 3) > player.getMaxMp() ? player.getMaxMp() : player.getCurrentMp() + 3);
		if (this->player.getUseSkillCount() >= 5 && this->player.getUseSkillCount() < 10 && this->player.getSkill()->getLevel() == 0) {
			promptSkill(&this->player);
		}
		else if (this->player.getUseSkillCount() >= 10 && this->player.getSkill()->getLevel() == 1) {
			promptSkill(&this->player);
		}
		if (this->checkGameLogic()) break;
	}
}

