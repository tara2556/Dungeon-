#include "Room.h"

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

    /*contain 1 or multiple objects, including monster, npc, etc*/
    Room::Room(){}
    Room::Room(bool isExit, int index, vector<Object*> objects) {
        this->setIsExit(isExit);
        this->setIndex(index);
        this->setObjects(objects);
        this->setLeftRoom(nullptr);
        this->setRightRoom(nullptr);
        this->setDownRoom(nullptr);
        this->setUpRoom(nullptr);
    }
    bool Room::popObject(Object* objects) {
        for (auto it = this->objects.begin(); it != this->objects.end(); it++ ) {
            if (*it == objects) {
                this->objects.erase(it);
                return 1;
            }
        }
        return 0;
    }
    /*pop out the specific object, used when the interaction is done*/

    /* Set & Get function*/
    void Room::setUpRoom(Room* upRoom) {
        this->upRoom = upRoom;
    }
    void Room::setDownRoom(Room* downRoom) {
        this->downRoom = downRoom;
    }
    void Room::setLeftRoom(Room* leftRoom) {
        this->leftRoom = leftRoom;
    }
    void Room::setRightRoom(Room* rightRoom) {
        this->rightRoom = rightRoom;
    }
    void Room::setIsExit(bool isExit) {
        this->isExit = isExit;
    }
    void Room::setIndex(int index) {
        this->index = index;
    }
    void Room::setObjects(vector<Object*> objects) {
        this->objects = objects;
    }
    void Room::setX(int x) {
        this->x = x;
    }
    void Room::setY(int y) {
        this->y = y;
    }
    int Room::getX() {
        return this->x;
    }
    int Room::getY() {
        return this->y;
    }
    bool Room::getIsExit() {
        return isExit;
    }
    int Room::getIndex() {
        return index;
    }
    vector<Object*> Room::getObjects() {
        return objects;
    }
    Room* Room::getUpRoom() {
        return upRoom;
    }
    Room* Room::getDownRoom() {
        return downRoom;
    }
    Room* Room::getLeftRoom() {
        return leftRoom;
    }
    Room* Room::getRightRoom() {
        return rightRoom;
    }
