
#include "test.h"
#include "../utils/global.h"
#include "displays.h"
#include <stdio.h>

extern Global* gl;
extern Displays* display;

Test::Test() {
	printf("Test in\n");
	setForeground("./images/level1/levfore.png");
	setBackground("./images/level1/levback.png");
	refreshEnemies();
	player.refresh();
}

Test::~Test() {
	printf("Test out\n");
}

void Test::drawEnemies() {
	size_t i;
	for (i = 0; i < enemies.size(); i++)  {
		if (player.ypos < enemies[i].ypos)
			enemies[i].Display();
		else break;
	}
	for (; i < enemies.size(); i++)  {
		enemies[i].Display();
	}
	for (i = 0; i < enemies.size(); i++)  {
		enemies[i].Move(player.xpos, player.ypos);
	}
	sortEnemies();	
}

void Test::on() {
	drawScene(background_tex);
	drawEnemies();
	drawScene(foreground_tex);
	checkKeys();
}

int Test::checkKeys() {
	if (gl->keys[XK_0])
		display->select(start);
	if (gl->keys[XK_1])
		display->select(lvl_1);
	if (gl->keys[XK_2])
		display->select(lvl_2);

	return 0;	
}
