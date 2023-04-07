#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster : public GameCharacter
{
private:
    string descripation;

public:
    Monster();
    Monster(string, int, int, int);
    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    void revive(int);
    bool triggerEvent(Object*);
    void setDescripation(string);
    void chooseMonsterSkill(Object*);
    string getDescripation();
};
ostream& operator<<(ostream&, Monster);

#endif // ENEMY_H_INCLUDED
