#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter : public Object
{
private:
	string name;
	int maxHealth;
	int currentHealth;
	int attack;
	int defense;
	int useSkillCount = 0;
	int addAtk = 0;
	int addDef = 0;
	int addHp = 0;
public:
	GameCharacter();
	GameCharacter(string, string, int, int, int);
	bool checkIsDead();
	int takeDamage(int);
	void increaseStates(int, int, int);

	/* Set & Get function*/
	void setUseSkillCount(int);
	void setMaxHealth(int);
	void setCurrentHealth(int);
	void setAttack(int);
	void setDefense(int);
	void setAddHp(int);
	void setAddAtk(int);
	void setAddDef(int);
	int getAddHp();
	int getAddAtk();
	int getAddDef();
	int getMaxHealth();
	int getCurrentHealth();
	int getUseSkillCount();
	int getAttack();
	int getDefense();
};
#endif // GAMECHARACTER_H_INCLUDED
