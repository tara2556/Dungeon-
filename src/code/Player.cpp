#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"
#include "skill.h"
using namespace std;


Player::Player() {}
Player::Player(string name, int attack, int defense, int health, int occupation, int coin, int mp, Skill* skill) {
	this->setName(name);
	this->setAttack(attack);
	this->setDefense(defense);
	this->setCurrentHealth(health);
	this->setMaxHealth(health);
	this->setOccupation(occupation);
	this->setCoin(coin);
	this->setSkill(skill);
}
void Player::addItem(Item it) {
	inventory.push_back(it);
}


void Player::revive(int hp) {
	int curHp = this->getCurrentHealth() + hp;
	if (curHp > this->getMaxHealth()) curHp = this->getMaxHealth();
	if (curHp < 0) curHp = 0;
	this->setCurrentHealth(curHp);
}

/* Virtual function that you need to complete   */
/* In Player, this function should show the     */
/* status of player.                            */
bool Player::triggerEvent(Object*) {
	return 1;
}
void Player::checkInventory() {
	cout << "equipment: \n";
	if (this->inventory.size() == 0) {
		cout << "You have an empty bag, newbie.\n";
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	for (Item i : this->inventory) {
		cout << i.getName() << i.getDescripation() << '\n';
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
void Player::useSkill() {
	cout << "use special skills: " << this->getSkill()->getEffect() << '\n'
		<< "- " << this->getSkill()->getDescripation() << '\n';
	int consumption = (this->getSkill()->getLevel() + 1) * 50;
	if (this->currentMp < consumption) {
		cout << "You don't have enough MP!\n";
		return;
	}
	this->getSkill()->activateSkill(this);
	this->setUseSkillCount(this->getUseSkillCount() + 1);
	this->currentMp -= consumption;
}

void Player::showMap(int index) {
	for (int i = 0; i < this->getMapLength(); i++) {
		int w = this->getMapWidth();
		while (w--)	cout << "~~~~~~";
		cout << '\n';
		for (int j = 0; j < this->getMapWidth(); j++) {
			if (map[i][j] < 10 && map[i][j] >= 0) {
				if(map[i][j]==index)cout << "~ \033[7m0" << map[i][j] << "\033[0m ~";
				else cout << "~ 0" << map[i][j] << " ~";
			}
			else if (map[i][j] >= 10) {
				if (map[i][j] == index)cout << "~ \033[7m" << map[i][j] << "\033[0m ~";
				else cout << "~ " << map[i][j] << " ~";
			}
			else cout << "~ ## ~";
		}
		w = this->getMapWidth();
		cout << '\n';
		while (w--)	cout << "~~~~~~";
		cout << '\n';
	}
	cout << "You stay in Room " << index << '\n';
}
/* Set & Get function*/
void Player::setSkill(Skill* skill) {
	this->skill = skill;
}
void Player::setCoin(int coin) {
	this->coin = coin;
}
void Player::setMaxMp(int mp) {
	this->maxMp = mp;
}
void Player::setCurrentMp(int mp) {
	this->currentMp = mp;
}
void Player::initializeMap(int u, int d, int l, int r) {
	this->map = new int* [d - u + 1];
	for (int i = u; i <= d; i++) map[i - u] = new int[r - l + 1];
	this->setMapLength(d - u + 1);
	this->setMapWidth(r - l + 1);
	for (int i = 0; i < this->getMapLength(); i++) {
		for (int j = 0; j < this->getMapWidth(); j++) {
			map[i][j] = -1;
		}
	}
}
void Player::setMap(int i, int j, int index) {
	this->map[i][j] = index;
}
void Player::setMapLength(int l) {
	this->mapLength = l;
}
void Player::setMapWidth(int w) {
	this->mapWidth = w;
}
int Player::getMapLength() {
	return this->mapLength;
}
int Player::getMapWidth() {
	return this->mapWidth;
}
int** Player::getmap() {
	return this->map;
}

void Player::setCurrentRoom(Room* cur) {
	this->currentRoom = cur;
}
void Player::setPreviousRoom(Room* pre) {
	this->previousRoom = pre;
}
void Player::setInventory(vector<Item> it) {
	this->inventory = it;
}
void Player::setOccupation(int occupation) {
	this->occupation = occupation;
	switch (occupation) {
	case 1:
		setAttack(11);
		setDefense(3);
		setMaxHealth(15);
		setCurrentHealth(15);
		setMaxMp(100);
		setCurrentMp(100);
		break;
	case 2:
		setAttack(5);
		setDefense(8);
		setMaxHealth(14);
		setCurrentHealth(14);
		setMaxMp(150);
		setCurrentMp(150);
		break;
	case 3:
		setAttack(7);
		setDefense(5);
		setMaxHealth(20);
		setCurrentHealth(20);
		setMaxMp(120);
		setCurrentMp(120);
		break;
	}
}
void Player::setSkills(vector<Skill> s) {
	this->skills = s;
}
vector<Skill> Player::getSkills() {
	return skills;
}
Skill* Player::getSkill()
{
	return skill;
}
Room* Player::getCurrentRoom() {
	return currentRoom;
}
Room* Player::getPreviousRoom() {
	return previousRoom;
}
vector<Item> Player::getInventory() {
	return inventory;
}
int Player::getMaxMp() {
	return maxMp;
}
int Player::getCurrentMp() {
	return currentMp;
}
int Player::getCoin() {
	return coin;
}

string Player::getOccupation() {
	switch (occupation) {
	case 1:
		return "Warrior";
		break;
	case 2:
		return "Knight";
		break;
	case 3:
		return "Monk";
		break;
	}
}

ostream& operator<<(ostream& out, Player& player) {
	out << "===============================================\n"
		<< player.getName() << '\n'
		<< "Your Occupation: " << player.getOccupation() << '\n'
		<< "atk: " << player.getAttack() << '\n'
		<< "def: " << player.getDefense() << '\n'
		<< "HP: " << player.getCurrentHealth() << '/' << player.getMaxHealth() << '\n'
		<< "MP: " << player.getCurrentMp() << '/' << player.getMaxMp() << '\n'
		<< "special Skills: " << player.getSkill()->getEffect() << '\n'
		<< "wealth: " << player.getCoin() << '\n'
		<< "===============================================\n";
	return out;
}
