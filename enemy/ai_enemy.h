
#ifndef _AI_ENEMY_H_
#define _AI_ENEMY_H_

#include <GL/glx.h>
#include "../utils/image.h"

class AI_Enemy {
public:
	int enemy_num;
	static GLuint enemy_tex[];

	int xpos, ypos;
	int size, step;
	int  rand_diff;
	// int  health;
	// int  frame;

	// Display
	// bool  near;
	// bool stood;
	// bool alive;
	// int  slice;

	// bool fwd;
	// bool mov;

	// Methods
	AI_Enemy();
	static void init();
	void Display();
	void refresh();

	static bool cmp(AI_Enemy, AI_Enemy);

	void standDraw();
	void Move(int, int);
};

#endif
