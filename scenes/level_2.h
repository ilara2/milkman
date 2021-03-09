
#ifndef LVL_2_H_
#define LVL_2_H_

#include "scenes.h"

class Level_2: public Scenes {
public:
	Level_2();
	~Level_2();
	void on();
	int checkKeys();
	void drawPlayers();
};

#endif
