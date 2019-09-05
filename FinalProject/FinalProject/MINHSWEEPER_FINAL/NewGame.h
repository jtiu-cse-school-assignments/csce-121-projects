#pragma once

#include <Windows.h>
#include <string>
#include "Box.h"
#include <FL/Fl.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

class NewGame : public Fl_Button {
private:

public:
	NewGame(int posX, int posY);
	int handle(int event);
};
