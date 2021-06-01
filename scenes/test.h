
#ifndef TEST_H_
#define TEST_H_

#include "scenes.h"

class Test: public Scenes {
public:
	Test();
	~Test();
	void on();
	int checkKeys();
	void drawEnemies();
	void printEnemies();
};

#endif
