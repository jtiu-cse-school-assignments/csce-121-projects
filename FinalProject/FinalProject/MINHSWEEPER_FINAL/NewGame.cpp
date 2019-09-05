#include "NewGame.h"
#include "Game.h"

NewGame::NewGame(int posX, int posY) : Fl_Button(posX, posY, 30, 30, 0) {
	this->image(new Fl_JPEG_Image("NewGame.jpg"));
}

int NewGame::handle(int event) {
	switch (event) {
	case FL_RELEASE:
		this->do_callback();
		this->redraw();
		break;
	}
	return 0;
}
