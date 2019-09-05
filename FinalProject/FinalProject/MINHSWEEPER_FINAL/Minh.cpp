#include "Minh.h"
#include <iostream>

Minh::Minh() : Fl_Button(10, 600, 230, 200, 0) {
	this->image(new Fl_JPEG_Image("Minh.jpg"));
}

int Minh::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		count++;
		if (count % 2 == 0) {
			this->image(new Fl_JPEG_Image("Minh.jpg"));
		}
		else {
			this->image(new Fl_JPEG_Image("Minh1.jpg"));
		}
	default:
		return Fl_Button::handle(event);
	}
}