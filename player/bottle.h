
#ifndef BOTTLE_H_
#define BOTTLE_H_

#include "../utils/global.h"
#include "../utils/image.h"
#include <GL/glx.h>

class Bottle {
public:
	// Texture
	static GLuint bottle_tex;

	// Positions
	int xpos, ypos;
	int hitbox[4][2];

	// Variables
	int  size, step;
	attack_dir direction;
	float ds;
	bool active;

	bool debug = false;
	static bool flag;
	static void init();

	// Methods
	Bottle();
	void display();
	void throwBottle(attack_dir, int, int);
	void update();
	void checkBounds();
	void reset();
};

#endif