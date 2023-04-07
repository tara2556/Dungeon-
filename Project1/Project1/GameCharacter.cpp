#include "GameCharacter.h"

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;



GameCharacter::GameCharacter()  {}
GameCharacter::GameCharacter(string name, string tag, int attack, int defense, int health) {
	this->name = name;
	setTag(tag);
	this->attack = attack;
	this->defense = defense;
	this->currentHealth = health;
	this->maxHealth = health;
	this->setAddAtk(0);
	this->setAddDef(0);
	this->setAddHp(0);
}
bool GameCharacter::checkIsDead() {
	return currentHealth <= 0;
}
int GameCharacter::takeDamage(int damageLost) {
	currentHealth -= damageLost;
	return currentHealth;
}
void GameCharacter::increaseStates(int attack, int defense, int health) {
	this->setAttack(this->getAttack() + attack);
	this->setDefense(this->getDefense() + defense);
	this->setCurrentHealth(this->getCurrentHealth() + health);
	this->setMaxHealth(this->getMaxHealth() + health);

}
/* Set & Get function*/
void GameCharacter::setUseSkillCount(int s) {
	this->useSkillCount = s;
}
void GameCharacter::setMaxHealth(int maxHealth) {
	this->maxHealth = maxHealth;
}
void GameCharacter::setCurrentHealth(int currentHealth) {
	this->currentHealth = currentHealth;
}
void GameCharacter::setAttack(int attack) {
	this->attack = attack;
}
void GameCharacter::setDefense(int defense) {
	this->defense = defense;
}
void  GameCharacter::setAddHp(int h) {
	this->addHp = h;
}
void  GameCharacter::setAddAtk(int a) {
	this->addAtk = a;
}
void  GameCharacter::setAddDef(int d) {
	this->addDef = d;
}
int  GameCharacter::getAddHp() {
	return this->addHp;
}
int  GameCharacter::getAddAtk() {
	return this->addAtk;
}
int  GameCharacter::getAddDef() {
	return this->addDef;
}

int GameCharacter::getUseSkillCount() {
	return useSkillCount;
}
int GameCharacter::getMaxHealth() {
	return maxHealth;
}
int GameCharacter::getCurrentHealth() {
	return currentHealth;
}
int GameCharacter::getAttack() {
	return attack;
}
int GameCharacter::getDefense() {
	return defense;
}
