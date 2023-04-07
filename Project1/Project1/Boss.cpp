#include "Boss.h"
#include<iostream>
#include<vector>
#include<string>
#include "GameCharacter.h"
using namespace std;
Boss::Boss(){}
Boss::Boss(string name, string descripation, int atk, int def, int hp) {
	this->setName(name);
	this->setDescripation(descripation);
	this->setAttack(atk);
	this->setDefense(def);
	this->setCurrentHealth(hp);
	this->setMaxHealth(hp);
}

bool Boss::triggerEvent(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	cout << "Although I was ever chicken, now I can knock down you like god!\n";
	bool fightIsEnd = 0, ultraState = 0;;
	while (!fightIsEnd) {
		int isAttack = 0;
		if (this->getCurrentHealth() * 5 < this->getMaxHealth() && !ultraState) {
			ultraState = 1;
			this->secondState();
			cout << "I get powerrrrrrrrrrrrrrrrr!!!!!!!!!!!!!!!!\n";
		}
		this->chooseMonsterSkill(player);
		player->getSkill()->recoverState(this);

		cout << "you:\n" << *player << "rival:\n" << *this;
		cout << "0. attack\n"
			<< "1. defense\n"
			<< "2. use special skill\n"
			<< "3. flee\n";
		cin >> isAttack;
		if (isAttack == 1) {
			int damage = this->getAttack() - player->getAttack() - player->getDefense();
			damage = (damage < 0) ? 0 : damage;
			player->getSkill()->recoverState(player);
			cout << "You received " << damage << " damage.\n";
			player->takeDamage(damage);
			if (player->checkIsDead()) {
				cout << "You die.\n";
				return 0;
			}
		}
		else if (isAttack == 0) {
			int damage = this->getAttack() - player->getDefense();
			int harm = player->getAttack() - this->getDefense();
			player->getSkill()->recoverState(player);
			harm = (harm < 0) ? 0 : harm;
			damage = (damage < 0) ? 0 : damage;
			cout << "You dealt " << harm << " damage\n";
			cout << "You received " << damage << " damage.\n";
			player->takeDamage(damage);
			this->takeDamage(harm);
			if (this->getCurrentHealth() < 0) this->setCurrentHealth(0);
			if (player->checkIsDead()) {
				cout << "You die.\n";
				return 0;
			}
			if (this->getCurrentHealth() == 0) {				
				fightIsEnd = 1;
			}
		}
		else if (isAttack == 2) {
			player->useSkill();
			int damage = this->getAttack() - player->getAttack();
			damage = (damage < 0) ? 0 : damage;
			cout << "You received " << damage << " damage.\n";
			player->takeDamage(damage);
			if (player->checkIsDead()) {
				cout << "You die.\n";
				return 0;
			}
		}
		else {
			player->getSkill()->recoverState(player);
			cout << "Ha Ha! Little coward\n";
			int damage = player->getCurrentHealth() * 0.2;
			damage = (damage < 0) ? 0 : damage;
			cout << "You received " << damage << " damage.\n";
			player->takeDamage(damage);
			return 0;
		}
	}

	return 1;
}

void Boss::secondState() {
	int hp = this->getMaxHealth() * 2;
	int def = this->getDefense() * 1.25;
	int atk = this->getAttack() * 1.25;
	this->setCurrentHealth(hp);
	this->setMaxHealth(hp);
	this->setAttack(atk);
	this->setDefense(def);
}

void Boss::setSpecialSkillName(string s) {
	this->specialSkillName = s;
}

string Boss::getSpecialSkillName() {
	return specialSkillName;
}