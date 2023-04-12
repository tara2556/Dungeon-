#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include "Monster.h"
using namespace std;
class Boss :public Monster {
private:
	string specialSkillName;
public:
	Boss();
	Boss(string, string, int, int, int);
	void secondState();
	bool triggerEvent(Object*);
	void setSpecialSkillName(string);
	string getSpecialSkillName();
};
#endif
