
#ifndef PLAYER_H_
#define PLAYER_H_

#include <GL/glx.h>
#include "global.h"
#include "image.h"
#include "bottle.h"
#include <vector>

class Player {
public:
	GLuint* player_tex;
	std::vector<Bottle> bottles;

	int  timer;
	int   time;
	bool shoot;

	// Positions
	int xpos, ypos;		// refers to bottom center of player
	int size, step;		// player is (2*size) X (2*size)

	// Display
	bool     fwd;
	bool     mov;
	int    frame;

	// Abilities
	int  fireRate;		// gl->fps/fireRate = shots/second
	int fireSpeed;

	// Methods
	Player();
	~Player();
	void display();
	void bindTex();
	void addBottles();
	void refresh();
	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void attack(attack_dir);
	Bottle* nextBottle();

	void showAttack();
};


#endif
