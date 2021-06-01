
#include "ai_enemy.h"
#include "../utils/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern Global* gl;
GLuint AI_Enemy::enemy_tex[8];

void AI_Enemy::init() {
	Image imgs[] = {
		Image("./images/enemy/stand_right.png"),
		Image("./images/enemy/stand_left.png"),
		Image("./images/enemy/walk_right.png"),
		Image("./images/enemy/walk_left.png"),
		Image("./images/enemy/stand_up_right.png"),
		Image("./images/enemy/stand_up_left.png"),
		Image("./images/enemy/die_right.png"),
		Image("./images/enemy/die_left.png")
	};

	int size = sizeof(imgs) / sizeof(imgs[0]);
	for (int i = 0; i < size; i++) {
		glGenTextures(1, &enemy_tex[i]);
		glBindTexture(GL_TEXTURE_2D, enemy_tex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		unsigned char *new_img = Image::buildAlphaData(&imgs[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgs[i].width, imgs[i].height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, new_img);
		free(new_img);
	}
}

AI_Enemy::AI_Enemy() {
	size = gl->yres / 7;
	step = size/ 12;
	rand_diff = rand() % 4 + 11;

	xpos = rand() % (gl->xres / 2) + gl->xres / 2;
	ypos = rand() % (gl->yres / 2);

	// health = 2;
	// near = false;
	// stood = false;
	// alive =  true;
	// fwd = rand() % 2;
	// mov = false;
	// slice = 0;
	// frame = 0;
}

void AI_Enemy::refresh() {
	size = gl->yres / 7;
	step = size/ 12;
	rand_diff = rand() % 4 + 11;


	xpos = rand() % (gl->xres / 2) + gl->xres / 2;
	ypos = rand() % (gl->yres / 2);
}


void AI_Enemy::Display() {
	// if (alive) drawHitBox();
	step = size / rand_diff;
	int depth = gl->yres - ypos;
	float depthRatio = ((float)depth + 2*gl->yres) / (3 * gl->yres);
	size = gl->yres / 7 * depthRatio;
	standDraw();
}

void AI_Enemy::standDraw() {
	// slice = 0;
	GLuint texture;
	texture = enemy_tex[1];

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

bool AI_Enemy::cmp(AI_Enemy a, AI_Enemy b) {
	return a.ypos > b.ypos;
}

void AI_Enemy::Move(int x, int y) {
}