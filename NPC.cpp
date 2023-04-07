#include "NPC.h"

#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;



NPC::NPC(string name, string script, vector<Item> commodity) {
	this->setScript(script);
	this->setName(name);
	this->setCommodity(commodity);
}
void NPC::listCommodity() {
	int itemCount = 0;
	for (Item i : commodity) {
		cout << itemCount++ << ". " << i << '\n';
	}
	cout << itemCount << ". I don't want any of them\n";
} /*print all the Item in this NPC*/

/* Virtual function that you need to complete   */
/* In NPC, this function should deal with the   */
/* transaction in easy implementation           */
bool NPC::triggerEvent(Object* object) {
	if (object->getTag() != "player") return 0;
	Player* player = dynamic_cast<Player*>(object);
	int buyWeapon = 0;
	bool successfullyPurchase = 0, wantToBuy = 0;
	cout << this->getScript() << '\n';
	if (this->commodity.size()) {
		cout << "In need of some powerful weapons? Look no further.\n"
			<< "These might be just what you're looking for. Would you like to take a look?\n"
			<< "0. No\n"
			<< "1. Yes, I need.\n";
		cin >> wantToBuy;
		if (wantToBuy) {
			bool moreThanOne = 1;
			bool checkEnoughMoney = 0;
			bool mistakeAction = 0;
			while (moreThanOne) {
				successfullyPurchase = 0;
				if (commodity.size() == 0) {
					cout << "Sorry, I don't have anymore weapons. Hope you have a nice trip!\n";
					break;
				}
				while (!successfullyPurchase) {
					for (Item i : commodity) {
						if (player->getCoin() >= i.getPrice()) checkEnoughMoney = 1;
					}
					if (!checkEnoughMoney) {
						cout << "You didn't have money? Get out of my face!\n";
						break;
					}
					this->listCommodity();
					cout << "Which one do you want?\n"
						<< "your wealth: " << player->getCoin() << '\n';
					cin >> buyWeapon;
					if (buyWeapon<0 || buyWeapon>commodity.size()) {
						cout << "No this action!\n";
						moreThanOne = 0;
						break;
					}
					if (buyWeapon == commodity.size()) {
						moreThanOne = 0;
						break;
					}
					if (player->getCoin() >= this->commodity[buyWeapon].getPrice()) {
						player->setCoin(player->getCoin() - this->commodity[buyWeapon].getPrice());
						successfullyPurchase = 1;
						player->addItem(commodity[buyWeapon]);
						player->increaseStates(commodity[buyWeapon].getAttack(), commodity[buyWeapon].getDefense(), commodity[buyWeapon].getHealth());
						commodity.erase(commodity.begin() + buyWeapon);
					}
					else {
						cout << "Poor bastard. Get away!\n";
						mistakeAction = 1;
						moreThanOne = 0;
						break;
					}
				}
				if (!checkEnoughMoney) break;
				if (successfullyPurchase) {
					cout << "Do you want to choose another?\n"
						<< "0. No\n"
						<< "1. Yes, I need.\n";
					cin >> moreThanOne;
				}
				
			}
			if (checkEnoughMoney && successfullyPurchase) {
				cout << "Thank you for purchasing these weapons. I hope they will aid you in defeating the demon king.\n";
			}
			else if (checkEnoughMoney && !successfullyPurchase && !mistakeAction) {
				cout << "Hope to see you next time!\n";
			}
		}
	}
	return 1;
}

/* Set & Get function*/
void NPC::setScript(string script) {
	this->script = script;
}
void NPC::setCommodity(vector<Item> commodity) {
	this->commodity = commodity;
}
string NPC::getScript() {
	return script;
}
vector<Item> NPC::getCommodity() {
	return commodity;
}
