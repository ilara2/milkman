
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <GL/glx.h>
#include "image.h"
#include "nn/network.h"

class Enemy {
public:
	int enemy_num;
	static GLuint enemy_tex[];

	int xpos, ypos;
	int size, step;
	int  rand_diff;
	int  health;
	int  frame;

	// Display
	bool  near;
	bool stood;
	bool alive;
	int  slice;
	int hitbox[4][2];

	bool fwd;
	bool mov;

	// Methods
	Enemy();
	Enemy(int);
	static void init();
	void Display();
	void refresh();
	void move();
	void standDraw();

	static bool cmp(Enemy, Enemy);

	void sitDraw();
	void moveDraw();
	void standupDraw();
	void sitdownDraw();
	void Move(int, int);

	void drawHitBox();
	void setLoc(int, int, int);
	void Attack();
	void Die();
};

#endif
