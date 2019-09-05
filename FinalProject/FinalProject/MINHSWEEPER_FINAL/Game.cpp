#include <iostream>
#include <time.H>
#include <stdlib.H>
#include <iostream>
#include "Game.H"

using namespace std;


void nmTimerCallback(void* i) {
	Game* g = static_cast<Game*>(i);
	g->timerCallback();
}

void Game::BombCallback(Fl_Widget* widget, void* v) {
	Game* game = static_cast<Game*>(v);
	Bomb* bomb = static_cast<Bomb*>(widget);
	vector<int> position = bomb->getLocation();
	int posX = position.at(0);
	int posY = position.at(1);
	game->getRemainingBombs();
	if (bomb->getFlag() == false && bomb->getQmark() == false && bomb->getUncover() == true) {
		game->checkLoss(posX, posY);
	}
	game->redraw();
}

void Game::MinhCallback(Fl_Widget* minh, void* v) {
	Game* game = static_cast<Game*>(v);
}

void Game::AmyCallback(Fl_Widget* amy, void* v) {
	Game* game = static_cast<Game*>(v);
}

void Game::JulianCallback(Fl_Widget* julian, void* v) {
	Game* game = static_cast<Game*>(v);
}

void Game::TaylorCallback(Fl_Widget* taylor, void* v) {
	Game* game = static_cast<Game*>(v);
}
void Game::NewGameCallback(Fl_Widget* newGame, void* v) {
	Game* game = static_cast<Game*>(v);
	game->resetGame();
}

void Game::NumbersCallback(Fl_Widget* numbers, void* v) {
	Game* game = static_cast<Game*>(v);
	Numbers* num = static_cast<Numbers*>(numbers);
	vector<int> position = num->getLocation();
	int posX = position.at(0);
	int posY = position.at(1);
	if ((game->findAdjacentBombs(posX, posY) == 0  && !num->getFlag()) && ((game->findAdjacentBombs(posX, posY) == 0 && !num->getQmark()))) {
		game->cascade(posX, posY);
	}
	game->checkWin();
	game->getRemainingBombs();
}

void Game::DebugCallback(Fl_Widget* debug, void* v) {
	Game* game = static_cast<Game*>(v);
	game->clickcount++;
	if (game->clickcount % 2 == 0) {
		for (int i = 0; i < game->listOfBoxes.size(); i++) {
			for (int j = 0; j < game->listOfBoxes.at(i).size(); j++) {
				if (game->listOfBoxes.at(i).at(j)->getType() == Box::Bomb && game->listOfBoxes.at(i).at(j)->getFlag() == false && game->listOfBoxes.at(i).at(j)->getQmark() == false) {
					game->listOfBoxes.at(i).at(j)->setUncover(false);
					game->listOfBoxes.at(i).at(j)->image(new Fl_JPEG_Image("Covered.jpg"));
					game->listOfBoxes.at(i).at(j)->redraw();
				}
			}
		}
	}
	else {
		for (int i = 0; i < game->listOfBoxes.size(); i++) {
			for (int j = 0; j < game->listOfBoxes.at(i).size(); j++) {
				if (game->listOfBoxes.at(i).at(j)->getType() == Box::Bomb && game->listOfBoxes.at(i).at(j)->getFlag() == false && game->listOfBoxes.at(i).at(j)->getQmark() == false) {
					game->listOfBoxes.at(i).at(j)->setUncover(false);
					game->listOfBoxes.at(i).at(j)->image(new Fl_JPEG_Image("Debug Bomb.jpg"));
					game->listOfBoxes.at(i).at(j)->redraw();
				}
			}
		}
	}
}

// Game constructor
Game::Game(int sizeX, int sizeY, int numBombs, int width, int height) : Fl_Window(width, height, "MINESWEEPER")
{
	
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->numBombs = numBombs;
	newgame = new NewGame((sizeX - 1) * 15, 515);
	newgame->callback(NewGameCallback, static_cast<void*>(this));
	debug = new Debug();
	debug->callback(DebugCallback, static_cast<void*>(this));
	minh = new Minh();
	minh->callback(MinhCallback, static_cast<void*>(this));
	amy = new Amy();
	amy->callback(AmyCallback, static_cast<void*>(this));
	julian = new Julian();
	julian->callback(JulianCallback, static_cast<void*>(this));
	taylor = new Taylor();
	taylor->callback(TaylorCallback, static_cast<void*>(this));
	vector<Box*> boxList;
	vector<int> randNums;
	vector< vector<int> > board(sizeX, vector<int>(sizeY, 0));
	srand(time(NULL));
	for (int i = 0; i < sizeX*sizeY; i++) {
		if (i < numBombs) {
			randNums.push_back(1);
		}
		else {
			randNums.push_back(0);
		}
	}
	for (int i = 0; i < sizeX; i++) {
		boxList.clear();
		for (int j = 0; j < sizeY; j++)
		{
			int spot = rand() % randNums.size();
			int num = randNums.at(spot);
			randNums.erase(randNums.begin() + spot);
			if (num == 1) {
				boxList.push_back(new Bomb(i, j));
				boxList.at(j)->callback(BombCallback, static_cast<void*>(this));
				board.at(i).at(j) = 1;
			}
			else {
				boxList.push_back(new Numbers(i, j, 0));
				boxList.at(j)->callback(NumbersCallback, static_cast<void*>(this));
			}
		}
		listOfBoxes.push_back(boxList);
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (board.at(i).at(j) == 0) {
				int adjacentBombs = findAdjacentBombs(i, j);
				listOfBoxes.at(i).at(j)->setAdjacentBombs(adjacentBombs);
			}
		}
	}
	Fl::add_timeout(1, nmTimerCallback, this);
}

// Resets game when the newGame button is pressed
void Game::resetGame() {
	vector<Box*> boxList;
	vector<int> randNums;
	vector< vector<int> > board(sizeX, vector<int>(sizeY, 0));
	srand(time(NULL));
	newgame->image(new Fl_JPEG_Image("NewGame.jpg"));
	for (int i = 0; i < sizeX - 1; i++) {
		for (int j = 0; j < sizeY - 1; j++) {
			remove(listOfBoxes.at(i).at(j));
			delete listOfBoxes.at(i).at(j);
		}
	}
	listOfBoxes.clear();
	for (int i = 0; i < sizeX*sizeY; i++) {
		if (i < numBombs) {
			randNums.push_back(1);
		}
		else {
			randNums.push_back(0);
		}
	}
	for (int i = 0; i < sizeX; i++) {
		boxList.clear();
		for (int j = 0; j < sizeY; j++)
		{
			int spot = rand() % randNums.size();
			int num = randNums.at(spot);
			randNums.erase(randNums.begin() + spot);
			if (num == 1) {
				boxList.push_back(new Bomb(i, j));
				boxList.at(j)->callback(BombCallback, static_cast<void*>(this));
				add(boxList.at(j));
				board.at(i).at(j) = 1;
			}
			else {
				boxList.push_back(new Numbers(i, j, 0));
				boxList.at(j)->callback(NumbersCallback, static_cast<void*>(this));
				add(boxList.at(j));
			}
		}
		listOfBoxes.push_back(boxList);
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (board.at(i).at(j) == 0) {
				int adjacentBombs = findAdjacentBombs(i, j);
				listOfBoxes.at(i).at(j)->setAdjacentBombs(adjacentBombs);
			}
			listOfBoxes.at(i).at(j)->show();
		}
	}
	this->redraw();
	this->show(0, nullptr);
}

void Game::buttonPressed(Fl_Widget* button) {
	return;
}

// Finds the adjacent bombs around an uncovered box
int Game::findAdjacentBombs(int posX, int posY) {
	int count = 0;
	for (int i = posX - 1; i <= posX + 1; i++) {
		for (int j = posY - 1; j <= posY + 1; j++) {
			if ((i >= 0 && i <= sizeX - 1) && (j >= 0 && j <= sizeY - 1)) {
				if (listOfBoxes.at(i).at(j)->getType() == Box::Bomb) {
					count++;
				}
			}
		}
	}
	return count;
}

// Sets the debug button true or false if "Shift-D" is pressed
void Game::setDebug(bool debug) {
	this->bug = debug;
}

void Game::cascade(int posX, int posY) {
	for (int i = posX - 1; i <= posX + 1; i++) {
		for (int j = posY - 1; j <= posY + 1; j++) {
			if ((i >= 0 && i <= sizeX - 1) && (j >= 0 && j <= sizeY - 1)) { //checks range
				if ((listOfBoxes.at(i).at(j)->getUncover() == false) && (listOfBoxes.at(i).at(j)->getType() != Box::Bomb) && (listOfBoxes.at(i).at(j)->getFlag() == false && listOfBoxes.at(i).at(j)->getFlag() == false)) {
					listOfBoxes.at(i).at(j)->setUncover(true);
					listOfBoxes.at(i).at(j)->imageSet();
					if ((findAdjacentBombs(i, j) == 0)){
						cascade(i, j);
						redraw();
					}
				}
			}
		}
	}
}

// Bomb count decreases everytime a flag is placed on the grid
void Game::getRemainingBombs() {
	remove(bombCount);
	delete bombCount;
	bombCount = new Fl_Box((sizeX * 15) - 45, 525, 100, 100, "");
	int count = numBombs;
	string lab = "Bomb Count: " + to_string(count);
	bombCount->copy_label(lab.c_str());
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (listOfBoxes.at(i).at(j)->getFlag() == true) {
				count--;
			}
		}
	}
	lab = "Bomb Count: " + to_string(count);
	bombCount->hide();
	bombCount->copy_label(lab.c_str());
	add(bombCount);
	bombCount->redraw();
	bombCount->show();
}

// Checks if the button clicked is a bomb
void Game::checkLoss(int posX, int posY) {
	if (listOfBoxes.at(posX).at(posY)->getType() == Box::Bomb) {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				listOfBoxes.at(i).at(j)->setGameOver(true);
			}
		}
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				if (listOfBoxes.at(i).at(j)->getType() == Box::Numbers && (listOfBoxes.at(i).at(j)->getFlag() == true || listOfBoxes.at(i).at(j)->getQmark() == true)) {
					listOfBoxes.at(i).at(j)->image(new Fl_JPEG_Image("False Bomb.jpg"));
				}
				if (listOfBoxes.at(i).at(j)->getType() == Box::Bomb && (listOfBoxes.at(i).at(j)->getFlag() == false || listOfBoxes.at(i).at(j)->getQmark() == false) && listOfBoxes.at(i).at(j)->getUncover() == false) {
					listOfBoxes.at(i).at(j)->image(new Fl_JPEG_Image("Bomb.jpg"));
				}
			}
		}
		newgame->image(new Fl_JPEG_Image("lose.jpg"));
		redraw();
	}
}

// Checks to see if the game is won
void Game::checkWin() {
	int count = 0;
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			if (listOfBoxes.at(i).at(j)->getType() == Box::Numbers && listOfBoxes.at(i).at(j)->getUncover() == true) {
				count++;
			}
		}
	}
	if (count + numBombs == sizeX*sizeY) {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				listOfBoxes.at(i).at(j)->image(new Fl_JPEG_Image("win.jpg"));
				listOfBoxes.at(i).at(j)->setGameOver(true);
			}
		}
		redraw();
	}
}


void Game::timerCallback() {
		timerCount++;
		remove(timer);
		delete timer;
		timer = new Fl_Box((sizeX * 15) + 150, 525, 100, 100, "");
		string lab = "Timer " + to_string(timerCount);
		timer->copy_label(lab.c_str());
		timer->hide();
		timer->copy_label(lab.c_str());
		add(timer);
		timer->redraw();
		timer->show();
		Fl::repeat_timeout(1, nmTimerCallback, this);

}

// Gets the boolean codition of debug
bool Game::getDebug() const {
	return this->bug;
}
