#include "Monster.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;


Monster::Monster()  {}
Monster::Monster(string name, int attack, int defense, int health) {
	this->setName(name);
	this->setAttack(attack);
	this->setDefense(defense);
	this->setMaxHealth(health);
	this->setCurrentHealth(health);
}


void Monster::revive(int hp) {
	int curHp = this->getCurrentHealth() + hp;
	if (curHp > this->getMaxHealth()) curHp = this->getMaxHealth();
	this->setCurrentHealth(curHp);
}

void Monster::chooseMonsterSkill(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	player->getSkill()->monsterSkill(player, this);
}
/* Virtual function that you need to complete   */
/* In Monster, this function should deal with   */
/* the combat system.                           */
bool Monster::triggerEvent(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	bool fightIsEnd = 0;
	while (!fightIsEnd) {
		if (player->getCurrentMp() != player->getMaxMp()) player->setCurrentMp(player->getCurrentMp() + 1);
		int isAttack = 0;
		int w = rand() % 5;
		if (!w) this->chooseMonsterSkill(player);
		player->getSkill()->recoverState(this);
		cout << "you:\n" << *player << "rival:\n" << *this;
		cout << "0. attack\n"
			<< "1. defense\n"
			<< "2. use special skill\n"
			<< "3. flee\n";
		cin >> isAttack;
		if (isAttack == 1) {
			player->getSkill()->recoverState(player);
			int damage = this->getAttack() - player->getAttack() - player->getDefense();
			damage = (damage < 0) ? 0 : damage;
			cout << "You received " << damage << " damage.\n";
			player->takeDamage(damage);
			if (player->checkIsDead()) {
				cout << "You die.\n";
				return 0;
			}
		}
		else if (isAttack == 0) {
			player->getSkill()->recoverState(player);
			int damage = this->getAttack() - player->getDefense();
			int harm = player->getAttack() - this->getDefense();
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
				cout << "You successfully knock down " << this->getName() << '\n';
				int victory = 0;
				while (victory < this->getMaxHealth() / 2) {
					victory = rand() % this->getMaxHealth();
				}
				cout << "You gain the victory reward: " << victory << " coins\n";
				player->setCoin(player->getCoin() + victory);
				fightIsEnd = 1;
			}
		}
		else if (isAttack == 2) {
			player->getSkill()->recoverState(player);
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
			return 0;
		}
	}
	return 1;
}

void Monster::setDescripation(string s) {
	this->descripation = s;
}

string Monster::getDescripation() {
	return this->descripation;
}

ostream& operator<<(ostream& out, Monster m) {
	out << "===============================================\n"
		<< m.getName() << '\n'
		<< m.getDescripation() << '\n'
		<< "atk: " << m.getAttack() << '\n'
		<< "def: " << m.getDefense() << '\n'
		<< " HP: " << m.getCurrentHealth() << '/' << m.getMaxHealth() << '\n'
		<< "===============================================\n";
	return out;
}

