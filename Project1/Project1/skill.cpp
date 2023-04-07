#include"skill.h"

#include<iostream>
#include<vector>
#include<string>
#include"Monster.h"
#include"player.h"
#include"Boss.h"
using namespace std;
Skill::Skill() {}
Skill::Skill(string d, int t, int l) {
	this->setEffect(d);
	this->setEffectTag(t);
	this->setLevel(l);
}
void Skill::setEffect(string s) {
	this->effect = s;
}
string Skill::getEffect() {
	return this->effect;
}

void Skill::setEffectTag(int s) {
	this->effectTag = s;
}
int Skill::getEffectTag() {
	return this->effectTag;
}
void Skill::setLevel(int l) {
	this->level = l;
}
int Skill::getLevel() {
	return this->level;
}
string Skill::getDescripation() {
	return this->descripation;
}
void Skill::setDescripation(string s) {
	this->descripation = s;
}
void Skill::setMonsterSkillDescripation(string l) {
	this->monsterSkillDescripation = l;
}
string Skill::getMonsterSkillDescripation() {
	return this->monsterSkillDescripation;
}
void Skill::activateSkill(Object* object) {
	Player* player = dynamic_cast<Player*>(object);
	switch (this->effectTag) {
	case 0:
		switch (this->level) {
		case 0:
			player->setAddAtk(player->getAttack() * 0.2);
			player->increaseStates(player->getAttack() * 0.2, 0, 0);
			break;
		case 1:
			player->setAddAtk(player->getAttack() * 0.5);
			player->increaseStates(player->getAttack() * 0.5, 0, 0);
			break;
		case 2:
			player->setAddAtk(player->getAttack() * 0.8);
			player->increaseStates(player->getAttack() * 0.8, 0, 0);
			break;
		}
		break;
	case 1:
		switch (this->level) {
		case 0:
			player->setAddDef(player->getDefense() * 0.2);
			player->increaseStates(0, player->getDefense() * 0.2, 0);
			break;
		case 1:
			player->setAddDef(player->getDefense() * 0.5);
			player->increaseStates(0, player->getDefense() * 0.5, 0);
			break;
		case 2:
			player->setAddDef(player->getDefense() * 0.8);
			player->increaseStates(0, player->getDefense() * 0.8, 0);
			break;
		}
		break;
	case 2:
		switch (this->level) {
		case 0:
			player->revive(player->getMaxHealth() * 0.1);
			break;
		case 1:
			player->revive(player->getMaxHealth() * 0.2);
			break;
		case 2:
			player->revive(player->getMaxHealth() * 0.3);
			break;
		}
		break;
	}
}
void Skill::recoverState(Object* object) {
	if (object->getTag() == "monster") {
		Monster* monster = dynamic_cast<Monster*>(object);
		monster->increaseStates(-monster->getAddAtk(), -monster->getAddDef(), -monster->getAddHp());
		monster->setAddAtk(0), monster->setAddDef(0), monster->setAddHp(0);
	}
	else if (object->getTag() == "player") {
		Player* player = dynamic_cast<Player*>(object);
		player->increaseStates(-player->getAddAtk(), -player->getAddDef() / 2, -player->getAddHp());
		player->setAddAtk(0), player->setAddDef(0), player->setAddHp(0);

	}
	else {
		Boss* monster = dynamic_cast<Boss*>(object);
		monster->increaseStates(-monster->getAddAtk(), -monster->getAddDef(), -monster->getAddHp());
		monster->setAddAtk(0), monster->setAddDef(0), monster->setAddHp(0);
	}
}

void Skill::monsterSkill(Object* object, Monster* monster) {
	Player* player = dynamic_cast<Player*>(object);
	int tag = rand() % 3;
	int level = rand() % 100;
	if (level >= 80) level = 2;
	else if (level < 80 && level >= 50) level = 1;
	else level = 0;
	cout << monster->getName() << " use special skills: " << player->getSkills()[tag * 3 + level].getEffect() << '\n'
		<< "- " << player->getSkills()[tag * 3 + level].getMonsterSkillDescripation() << '\n';
	switch (tag) {
	case 0:
		switch (this->level) {
		case 0:
			monster->setAddAtk(monster->getAttack() * 0.2);
			monster->increaseStates(monster->getAttack() * 0.2, 0, 0);
			break;
		case 1:
			monster->setAddAtk(monster->getAttack() * 0.5);
			monster->increaseStates(monster->getAttack() * 0.5, 0, 0);
			break;
		case 2:
			monster->setAddAtk(monster->getAttack() * 0.8);
			monster->increaseStates(monster->getAttack() * 0.8, 0, 0);
			break;
		}
		break;
	case 1:
		switch (this->level) {
		case 0:
			monster->setAddDef(monster->getDefense() * 0.15);
			monster->increaseStates(0, monster->getDefense() * 0.15, 0);
			break;
		case 1:
			monster->setAddDef(monster->getDefense() * 0.3);
			monster->increaseStates(0, monster->getDefense() * 0.3, 0);
			break;
		case 2:
			monster->setAddDef(monster->getDefense() * 0.45);
			monster->increaseStates(0, monster->getDefense() * 0.45, 0);
			break;
		}
		break;
	case 2:
		switch (this->level) {
		case 0:
			player->revive(-player->getCurrentHealth() * 0.05);
			break;
		case 1:
			player->revive(-player->getCurrentHealth() * 0.10);
			break;
		case 2:
			player->revive(-player->getCurrentHealth() * 0.15);
			break;
		}
		break;
	}
}