#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <FL/Fl.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Timer.H>
#include "Box.h"
#include "Bomb.h"
#include "Numbers.h"
#include "NewGame.h"
#include "Debug.h"
#include "Minh.h"
#include "Amy.h"
#include "Julian.h"
#include "Taylor.h"

class Game : public Fl_Window {
private:
	int sizeX;
	int sizeY;
	int numBombs;
	int clickcount = 0;
	int timerCount = 0;
	std::vector<std::vector<Box*>> listOfBoxes;
	NewGame* newgame;
	Debug* debug;
	Fl_Box* bombCount;
	Fl_Box* timer;
	Minh* minh;
	Amy* amy;
	Julian* julian;
	Taylor* taylor;
	bool bug = false;
	int bombsRemaining;
	int adjacentBombs;
public:
	bool gameOver = false;
	Game(int sizeX, int sizeY, int numBombs, int width = 1000, int height = 1000);
	static void BombCallback(Fl_Widget* widget, void* viewerPtr);
	static void NewGameCallback(Fl_Widget* newGame, void* v);
	static void DebugCallback(Fl_Widget* debug, void* v);
	static void NumbersCallback(Fl_Widget* numbers, void* v);
	static void MinhCallback(Fl_Widget* minh, void* v);
	static void AmyCallback(Fl_Widget* amy, void* v);
	static void JulianCallback(Fl_Widget* julian, void* v);
	static void TaylorCallback(Fl_Widget* taylor, void* v);
	void resetGame();
	void buttonPressed(Fl_Widget* button);
	int findAdjacentBombs(int posX, int posY);
	void setDebug(bool debug);
	bool getDebug() const;
	void cascade(int posX, int posY);
	void getRemainingBombs();
	void checkLoss(int posX, int posY);
	void checkWin();
	void timerCallback();
};