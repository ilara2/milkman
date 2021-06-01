
#include "player.h"
#include <stdlib.h>
#include <stdio.h>

extern Global* gl;

Player::Player() {
	xpos = 0;
	ypos = 100;
	size = gl->yres / 7;
	step = size / 10;

	fwd = true;
	mov = false;
	frame = 0;    

	timer = 0;
	time = 0;
	shoot = true;
		
	fireRate = 30;
	fireSpeed = size / 7;
}

Player::~Player() {}

void Player::addBottles() {
	for (int i = 0; i < 3; i++)
	bottles.push_back( Bottle() );
}

void Player::bindTex() {
	int num = 4;
	Image player_img[] = {
		Image("./images/player/stand_right.png"),
		Image("./images/player/stand_left.png"),
		Image("./images/player/walk_right.png"),
		Image("./images/player/walk_left.png")
	};
	player_tex = new GLuint[num];
	for (int i = 0; i < num; i++) {
		glGenTextures(1, &player_tex[i]);
		glBindTexture(GL_TEXTURE_2D, player_tex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		unsigned char *new_img = Image::buildAlphaData(&player_img[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, player_img[i].width, player_img[i].height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, new_img);
		free(new_img);
	}
}

void Player::refresh() {
	xpos = 0;
	ypos = 100;
	size = gl->yres / 7;
	step = size / 10;

	fwd = true;
	mov = false;
	frame = 0; 
}

void Player::display() {
	timer = (timer + 1) % fireRate;
	if (timer == time)
		shoot = true;

	step = size / 10;
	
	float inc = 0.125;
	static int count = 0;
	int    old_count = count;

	int depth = gl->yres - ypos;
	float depthRatio = ((float)depth + 2*gl->yres) / (3 * gl->yres); 
	size = gl->yres / 7 * depthRatio;

	if (mov) {
		count++;
		count = count % 8;
	}

	float frame = inc * count;

	if (old_count == count) {
		count = 0;
	}

	GLuint texture;
	if (mov) {
		if (fwd) texture = player_tex[2];
		else     texture = player_tex[3];

		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(xpos, ypos, 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(frame       , 1); glVertex2i(-size,      0);
			glTexCoord2f(frame + .125, 1); glVertex2i( size,      0);
			glTexCoord2f(frame + .125, 0); glVertex2i( size, 2*size);
			glTexCoord2f(frame       , 0); glVertex2i(-size, 2*size);
		glEnd();
		glPopMatrix();
		glDisable(GL_ALPHA_TEST);
		glBindTexture(GL_TEXTURE_2D, 0);
	} else {
		if (fwd) texture = player_tex[0];
		else     texture = player_tex[1];

		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(xpos, ypos, 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2i(-size,      0);
			glTexCoord2f(1, 1); glVertex2i( size,      0);
			glTexCoord2f(1, 0); glVertex2i( size, 2*size);
			glTexCoord2f(0, 0); glVertex2i(-size, 2*size);
		glEnd();
		glPopMatrix();
		glDisable(GL_ALPHA_TEST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	showAttack();
}

void Player::moveUp() {
	if ( (ypos + size/3) < gl->yres / 2)
		ypos += step;
	mov = true;
}

void Player::moveDown() {
	if (ypos > 0)
		ypos -= step;
	mov = true;
}

void Player::moveLeft() {
	if (xpos > 0)
		xpos -= step;
	mov = true;
	fwd = false;
}

void Player::moveRight() {
	xpos += step;
	mov = true;
	fwd = true;
}

void Player::resetBottles() {
	for (unsigned int i = 0; i < bottles.size(); i++)
		bottles[i].reset();
}

Bottle* Player::nextBottle() {
	size_t i;
	for (i = 0; i < bottles.size(); i++) {
		if (!bottles[i].active) return &bottles[i];
	}
	return NULL;
}

void Player::attack(attack_dir dir ) {
	if (!shoot) return;
	shoot = false;
	timer = 0;
	Bottle* ptr = nextBottle();
	if (ptr)
		ptr->throwBottle(dir, xpos, ypos+size);
}

void Player::showAttack() {
	size_t i;
	for (i = 0; i < bottles.size(); i++) 
		bottles[i].display();
}

// testing
void Player::randpos() {
	xpos = rand() % gl->xres;
	ypos = rand() % (gl->yres / 2);
}
