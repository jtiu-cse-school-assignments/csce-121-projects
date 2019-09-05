#include <iostream>
#include "Bomb.h"
using namespace std;

Bomb::Bomb() {
	return;
}

Bomb::Bomb(int row, int col) : Box(row, col) {
	this->image(new Fl_JPEG_Image("Covered.jpg"));
}

Box::boxType Bomb::getType() const {
	return Box::Bomb;
}

void Bomb::imageSet() {
	this->image(new Fl_JPEG_Image("Bomb.jpg"));
}

bool Bomb::checkLost() {
	return false;
}

int Bomb::handle(int event) {
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
		}
		if (Fl::event_button() == FL_LEFT_MOUSE) {
			if (!flag && !Qmark && this->gameOver == false) {
				setUncover(true);
				if (getType() == Box::Bomb) {
					this->image(new Fl_JPEG_Image("Bomb Exploded.jpg"));
				}
			}
		}
		this->redraw();
		this->do_callback();
		break;
	default:
		break;
	}
	return 0;
}