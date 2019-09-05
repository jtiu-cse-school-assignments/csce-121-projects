#include "Taylor.h"
#include <iostream>

Taylor::Taylor() : Fl_Button(730, 600, 230, 200, 0) {
	this->image(new Fl_JPEG_Image("Taylor.jpg"));
}

int Taylor::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		count++;
		if (count % 2 == 0) {
			this->image(new Fl_JPEG_Image("Taylor.jpg"));
		}
		else {
			this->image(new Fl_JPEG_Image("taylor1.jpg"));
		}
	default:
		return Fl_Button::handle(event);
	}
}