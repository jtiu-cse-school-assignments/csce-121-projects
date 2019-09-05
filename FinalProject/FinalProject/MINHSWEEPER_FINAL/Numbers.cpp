#include <iostream>
#include <sstream>
#include <string>
#include "Numbers.h"
#include "Game.h"
using namespace std;

Numbers::Numbers() {
	return;
}

Numbers::Numbers(int row, int col, int adjacentBombs) : Box(row, col) ,adjacentBombs(adjacentBombs){
	
}

Box::boxType Numbers::getType() const {
	return Box::Numbers;
}

void Numbers::setAdjacentBombs(int bombs) {
	this->adjacentBombs = bombs;
	this->image(new Fl_JPEG_Image("Covered.jpg"));
}

int Numbers::getAdjacentBombs() {
	return this->adjacentBombs;
}

void Numbers::imageSet() {
	string str = to_string(this->getAdjacentBombs());
	str = str + ".jpg";
	this->image(new Fl_JPEG_Image(str.c_str()));
}

int Numbers::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		if (Fl::event_button() == FL_RIGHT_MOUSE && !uncovered && this->gameOver == false) {
			if (flag) {
				flag = false;
				Qmark = true;
				this->image(new Fl_JPEG_Image("Question Mark.jpg"));
			}
			else if (Qmark) {
				Qmark = false;
				this->image(new Fl_JPEG_Image("Covered.jpg"));
			}
			else {
				flag = true;
				this->image(new Fl_JPEG_Image("Flag.jpg"));
			}
			this->do_callback();
			this->redraw();
		}
		if (Fl::event_button() == FL_LEFT_MOUSE) {
			if (!flag && !Qmark && !uncovered && this->gameOver == false) {
				this->setUncover(true);
				this->imageSet();
				this->do_callback();
				this->redraw();
			}
		}
		break;
	default:
		break;
	}
	return 0;
}