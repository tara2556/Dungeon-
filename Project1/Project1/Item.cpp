#include "Item.h"

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
using namespace std;


Item::Item() :Item("NULL", "NULL", 0, 0, 0, 0) {}
Item::Item(string name, string descripation, int attack, int defense, int health, int rare) {
	this->setName(name);
	this->setDescripation(descripation);
	this->attack = attack;
	this->defense = defense;
	this->health = health;
	this->rare = rare;
}

ostream& operator<<(ostream& out, Item a) {
	out << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< a.getName() << '\n'
		<< a.getRare() << '\n'
		<< a.getDescripation() << '\n'
		<< "atk: " << a.getAttack() << '\n'
		<< "def: " << a.getDefense() << '\n'
		<< "hp: " << a.getHealth() << '\n'
		<< "price: " << a.getPrice() << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	return out;
}
/* Virtual function that you need to complete    */
/* In Item, this function should deal with the   */
/* pick up action. You should add status to the  */
/* player.     */

bool Item::triggerEvent(Object* object) {
	int reward = rand() % 200 + 1;
	Player* player = dynamic_cast<Player*>(object);
	cout << player->getName() << ", Congratulations, you have obtained a treasure," << *this << "And " << reward << " coins\n";
	player->addItem(*this);
	player->increaseStates(this->attack, this->defense, this->health);
	player->setCoin(player->getCoin()+reward);
	return 1;
}

/* Set & Get function*/
int Item::getHealth() {
	return health;
}
int Item::getAttack() {
	return attack;
}
int Item::getDefense() {
	return defense;
}
string Item::getDescripation() {
	return descripation;
}
int Item::getPrice() {
	return price;
}
string Item::getRare() {
	switch (rare) {
	case 0:
		return "broken";
		break;
	case 1:
		return "normal";
		break;
	case 2:
		return "rare";
		break;
	case 3:
		return "legendary";
		break;
	}
}
void Item::setHealth(int health) {
	this->health = health;
}
void Item::setPrice(int price) {
	this->price = price;
}
void Item::setAttack(int attack) {
	this->attack = attack;
}
void Item::setDefense(int defense) {
	this->defense = defense;
}
void Item::setRare(int rare) {
	this->rare = rare;
}
void Item::setDescripation(string descripation) {
	this->descripation = descripation;
}



