#pragma once
#include "Game.H"

class LevelSelect : public Fl_Window {
private:

public:
	LevelSelect();
	static void beginnerCallback(Fl_Widget* beginner, void* v);
	static void intermediateCallback(Fl_Widget* intemediate, void* v);
	static void expertCallback(Fl_Widget* expert, void* v);
};
