#include "Debug.h"
#include <iostream>

Debug::Debug() : Fl_Button(0, 0, 0, 0, 0) {}

int Debug::handle(int event) {
	switch (event) {
	case FL_KEYBOARD:
		if ((Fl::event_key() == 'd') && (Fl::event_shift())) {
			this->do_callback();
		}
	default:
		return Fl_Button::handle(event);
	}
}
