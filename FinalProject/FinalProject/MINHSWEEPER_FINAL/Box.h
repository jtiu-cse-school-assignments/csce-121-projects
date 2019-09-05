#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Button.H>

class Box : public Fl_Button {
private:
	int posX;
	int posY;
	bool debug = false;
protected:
	bool uncovered = false;
	bool flag;
	bool Qmark;
	bool gameOver;
public:
	Box();
	Box(int posX, int posY);
	//void BoxLocation(int posX, int PosY); might need again
	std::vector<int> getLocation();
	void setFlag(bool flag);
	bool getFlag() const;
	void setQmark(bool Qmark);
	bool getQmark() const;
	void setUncover(bool uncovered);
	bool getUncover() const;
	void setGameOver(bool over);
	enum boxType {
		Bomb,
		Numbers
	};

	virtual int handle(int event) = 0;
	virtual boxType getType() const = 0;
	virtual void setAdjacentBombs(int bombs);
	virtual void imageSet() = 0;
	//virtual int getAdjacentBombs();
};