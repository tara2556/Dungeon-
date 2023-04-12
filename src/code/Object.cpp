#include "Object.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;


Object::Object() :Object("GUEST", "0") {}
Object::Object(string name, string tag) {
	this->name = name;
	this->tag = tag;
}

/* pure virtual function */
bool triggerEvent(Object*);

/* Set & Get function*/
void Object::setName(string name) {
	this->name = name;
}
void Object::setTag(string tag) {
	this->tag = tag;
}
string Object::getName() {
	return name;
}
string Object::getTag() {
	return tag;
}
