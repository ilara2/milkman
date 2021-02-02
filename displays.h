
#ifndef DISPLAYS_H_
#define DISPLAYS_H_

// #include "themilkman.h"
#include "global.h"
#include "scenes.h"

class Displays {
	Displays();
	static Displays instance;
public:
	Scenes* display;

	void select(stages);
	void show();
	int checkKeys();
	void next();
	void prev();

	static Displays& getInstance();
};

#endif
