#include "Amy.h"
#include <iostream>

Amy::Amy() : Fl_Button(250, 600, 230, 200, 0) {
	this->image(new Fl_JPEG_Image("Amy.jpg"));
}

int Amy::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		count++;
		if (count % 2 == 0) {
			this->image(new Fl_JPEG_Image("Amy.jpg"));
		}
		else {
			this->image(new Fl_JPEG_Image("amy1.jpg"));
		}
	default:
		return Fl_Button::handle(event);
	}
}