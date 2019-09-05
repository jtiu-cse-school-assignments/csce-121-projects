#include "LevelSelect.h"
#include <iostream>

using namespace std;

int main() {
	LevelSelect* selectLevel = new LevelSelect();
	selectLevel->show(0, nullptr);
	return Fl::run();
}