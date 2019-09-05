#pragma once
#include <Windows.h>
#include <string>
#include "Box.h"
#include <FL/Fl.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include "Game.h"

class Numbers : public Box {
private:
	int adjacentBombs;
public:
	Numbers();
	Numbers(int row, int col, int adjacentBombs);
	Box::boxType getType() const;
	void setAdjacentBombs(int bombs);
	int getAdjacentBombs();
	void imageSet();
	int handle(int event);
};