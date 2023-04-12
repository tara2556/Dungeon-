#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include<iostream>
#include<vector>
#include<string>
#include"Item.h"
#include"Monster.h"
#include"Object.h"
using namespace std;

class Monster;

class Skill{
private:
	string effect;
	string descripation;
	string monsterSkillDescripation;
	int effectTag;
	int level;
public:
	Skill();
	Skill(string, int, int);
	void setEffect(string);
	string getEffect();
	void setEffectTag(int);
	int getEffectTag();
	void setLevel(int);
	int getLevel();
	void setMonsterSkillDescripation(string);
	string getMonsterSkillDescripation();
	void setDescripation(string);
	string getDescripation();
	void activateSkill(Object*);
	void recoverState(Object*);
	void monsterSkill(Object* ,Monster*);
};
#endif