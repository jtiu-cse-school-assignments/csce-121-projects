#include <iostream>
#include "Box.h"
using namespace std;

// Box default contructor
Box::Box() : Fl_Button(1, 1, 1, 1, 0) {
	return;
}

// Box constructor
Box::Box(int posX, int posY) : Fl_Button(posX * 30, posY * 30, 30, 30, 0) {
	this->posX = posX;
	this->posY = posY;
}

// Gets the position of the box
vector<int> Box::getLocation() {
	vector<int> position = vector<int>{this->posX, this->posY };
	return position;
}

// If the flag is placed on a grid, this function returns true
void Box::setFlag(bool flag) {
	this->flag = flag;
}

// Gets the boolean condition of flag 
bool Box::getFlag() const {
	return this->flag;
}

// If the question mark is placed on a grid, this function returns true
void Box::setQmark(bool Qmark) {
	this->Qmark = Qmark;
}

// Gets the bolean condition of Qmark
bool Box::getQmark() const {
	return this->Qmark;
}

// Sets the condtion of box covered
void Box::setUncover(bool uncovered) {
	this->uncovered = uncovered;
}

// gets the state of the box
bool Box::getUncover() const{
	return this->uncovered;
}

// sets the game status
void Box::setGameOver(bool over) {
	this->gameOver = over;
}

//sets adjacent bombs
void Box::setAdjacentBombs(int bombs) {}