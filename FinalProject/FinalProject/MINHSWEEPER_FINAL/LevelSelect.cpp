#include "LevelSelect.H"

using namespace std;

void LevelSelect::beginnerCallback(Fl_Widget* beginner, void* v) {
	LevelSelect* selectLevel = static_cast<LevelSelect*>(v);
	selectLevel->hide();
	Game* game = new Game(9, 9, 10);
	game->show();
}

void LevelSelect::intermediateCallback(Fl_Widget* intemediate, void* v) {
	LevelSelect* selectLevel = static_cast<LevelSelect*>(v);
	selectLevel->hide();
	Game* game = new Game(16, 16, 40);
	game->show();
}

void LevelSelect::expertCallback(Fl_Widget* expert, void* v) {
	LevelSelect* selectLevel = static_cast<LevelSelect*>(v);
	selectLevel->hide();
	Game* game = new Game(30, 16, 99);
	game->show();
}

LevelSelect::LevelSelect() : Fl_Window(200, 350, "Select Level") {
	Fl_Button* beginner = new Fl_Button(50, 50, 100, 50, "Beginner");
	beginner->callback(beginnerCallback, static_cast<void*>(this));
	Fl_Button* intermediate = new Fl_Button(50, 150, 100, 50, "Intermediate");
	intermediate->callback(intermediateCallback, static_cast<void*>(this));
	Fl_Button* expert = new Fl_Button(50, 250, 100, 50, "Expert");
	expert->callback(expertCallback, static_cast<void*>(this));
	this->redraw();
}