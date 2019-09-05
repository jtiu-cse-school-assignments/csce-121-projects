#include "Julian.h"
#include <iostream>

Julian::Julian() : Fl_Button(490, 600, 230, 200, 0) {
	this->image(new Fl_JPEG_Image("Julian.jpg"));
}

int Julian::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		count++;
		if (count % 2 == 0) {
			this->image(new Fl_JPEG_Image("Julian.jpg"));
		}
		else {
			this->image(new Fl_JPEG_Image("julian1.jpg"));
		}
	default:
		return Fl_Button::handle(event);
	}
}