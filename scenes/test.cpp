
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
	enemies_num = 10;
	refreshAIEnemies();
	player.refresh();
	player.randpos();
}

Test::~Test() {
	printf("Test out\n");
}

void Test::drawEnemies() {
	size_t i;
	for (i = 0; i < ai_enemies.size(); i++)  {
		if (player.ypos < ai_enemies[i].ypos)
			ai_enemies[i].Display();
		else break;
	}
	player.display();
	for (; i < ai_enemies.size(); i++)  {
		ai_enemies[i].Display();
	}
	for (i = 0; i < ai_enemies.size(); i++)  {
		ai_enemies[i].Move(player.xpos, player.ypos);
	}
	sortAIEnemies();
	// printEnemies();
}

void Test::printEnemies() {
	size_t i;
	for (i = 0; i < enemies.size(); i++)
		printf("%zu ->\tx: %d\ty: %d\n", i, enemies[i].xpos, enemies[i].ypos);
}

void Test::on() {
	drawScene(background_tex);
	drawEnemies();
	checkKeys();
}

int Test::checkKeys() {
	if (gl->keys[XK_0])
		display->select(start);
	if (gl->keys[XK_1])
		display->select(lvl_1);
	if (gl->keys[XK_2])
		display->select(lvl_2);
	if (gl->keys[XK_equal])
		display->select(test);

	return 0;	
}
