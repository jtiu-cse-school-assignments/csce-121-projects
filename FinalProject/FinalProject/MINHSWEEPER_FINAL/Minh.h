#pragma once
#include <Windows.h>
#include <string>
#include "Box.h"
#include <FL/Fl.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

class Minh : public Fl_Button {
private:
	int count = 0;
public:
	Minh();
	int handle(int event);
};