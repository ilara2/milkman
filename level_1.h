
#ifndef LVL_1_H_
#define LVL_1_H_

#include "scenes.h"

class Level_1: public Scenes {
public:
	Level_1();
	~Level_1();
	void on();
	int checkKeys();
	void drawPlayers();
};

#endif
