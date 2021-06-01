
#include "level_1.h"
#include "../utils/global.h"
#include "displays.h"
#include <stdio.h>
// #include <algorithm>

extern Global* gl;
extern Displays* display;

Level_1::Level_1() {
	printf("Lvl 1 in\n");
	setForeground("./images/level1/levfore.png");
	setBackground("./images/level1/levback.png");
	enemies_num = 2;
	refreshEnemies();
	player.refresh();
}

Level_1::~Level_1() {
	printf("Lvl 1 out\n");
}

void Level_1::on() {
	drawScene(background_tex);
	drawPlayers();
	drawScene(foreground_tex);
	checkKeys();
}

void Level_1::drawPlayers() {
	size_t i;
	for (i = 0; i < enemies.size(); i++)  {
		if (player.ypos < enemies[i].ypos)
			enemies[i].Display();
		else break;
	}
	player.display();
	for (; i < enemies.size(); i++)  {
		enemies[i].Display();
	}
	for (i = 0; i < enemies.size(); i++)  {
		enemies[i].Move(player.xpos, player.ypos);
	}
	sortEnemies();
}

int Level_1::checkKeys() {
	// player movement
	if (gl->keys[XK_w]) player.moveUp();
	if (gl->keys[XK_s]) player.moveDown();
	if (gl->keys[XK_a]) player.moveLeft();
	if (gl->keys[XK_d]) player.moveRight();

	if ( !gl->keys[XK_w] && !gl->keys[XK_s] && !gl->keys[XK_a] && !gl->keys[XK_d] )
		player.mov = false;

	// attack
	if (gl->keys[XK_Up]) player.attack(up);
	if (gl->keys[XK_Down]) player.attack(down);
	if (gl->keys[XK_Left]) player.attack(left);
	if (gl->keys[XK_Right]) player.attack(right);

	// check player bounds
	if (player.xpos > gl->xres) {
		if (frame == 3) {
			display->select(lvl_2);
		} else {
			frame++;
			player.frame++;
			player.xpos = 0;
			refreshEnemies();
		}
	}

	if (gl->keys[XK_0])
		display->select(start);
	if (gl->keys[XK_2])
		display->select(lvl_2);
	if (gl->keys[XK_equal])
		display->select(test);

	return 0;
}
