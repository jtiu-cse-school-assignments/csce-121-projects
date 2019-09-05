#pragma once
#include <Windows.h>
#include <string>
#include "Box.h"
#include <FL/Fl.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

class Bomb : public Box {
private:
	bool explode;
public:
	Bomb();
	Bomb(int row, int col);
	Box::boxType getType() const;
	void Bomb::imageSet();
	bool checkLost();
	int handle(int event);
};