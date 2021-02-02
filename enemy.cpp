
#include "enemy.h"
#include "image.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern Global* gl;
GLuint Enemy::enemy_tex[8];

void Enemy::init() {
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

Enemy::Enemy() {
	size = gl->yres / 7;
	step = size/ 12;
	rand_diff = rand() % 4 + 11;

	xpos = rand() % (gl->xres / 2) + gl->xres / 2;
	ypos = rand() % (gl->yres / 2);

	health = 2;
	near = false;
	stood = false;
	alive =  true;
	fwd = rand() % 2;
	mov = false;
	slice = 0;
	frame = 0;
}

Enemy::Enemy(int _frame) {
	frame = _frame;
	size = gl->yres / 7;
	step = size/ 12;
	rand_diff = rand() % 4 + 11;

	xpos = rand() % (gl->xres / 2) + gl->xres / 2;
	ypos = rand() % (gl->yres / 2);

	health = 2;
	near = false;
	stood = false;
	alive =  true;
	fwd = rand() % 2;
	mov = false;
	slice = 0;
}

void Enemy::refresh() {
	size = gl->yres / 7;
	step = size/ 12;
	rand_diff = rand() % 4 + 11;


	xpos = rand() % (gl->xres / 2) + gl->xres / 2;
	ypos = rand() % (gl->yres / 2);

	health = 2;
	near = false;
	stood = false;
	alive =  true;
	fwd = rand() % 2;
	mov = false;
	slice = 0;
}

void Enemy::move() {
	// Network nn = Network(2, 4, 2);
	if (rand() % 2) ypos++;
	else ypos--;
	if (rand() % 2) xpos++;
	else xpos--;
}

void Enemy::Display() {
	// if (alive) drawHitBox();
	step = size / rand_diff;
	int depth = gl->yres - ypos;
	float depthRatio = ((float)depth + 2*gl->yres) / (3 * gl->yres);
	size = gl->yres / 7 * depthRatio;
	if (health < 1) alive = false;

	if (mov && alive)
		moveDraw();
	else if (alive) {
		if (near) {
			if (stood) standDraw();
			else standupDraw();
		} else {
			if (stood) sitdownDraw();
			else sitDraw();
		}
	} else {
		Die();
	}
}

void Enemy::standDraw() {
	slice = 0;
	GLuint texture;
	if (fwd)
		texture = enemy_tex[0];
	else
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

bool Enemy::cmp(Enemy a, Enemy b) {
	// if (a.frame > b.frame) return false;
	// if (a.frame < b.frame) return true;
	// if (a.ypos < b.ypos) return false;
	// if (a.ypos > b.ypos) return true;
	// return false;
	// if (a.frame == b.frame)
	// 	return a.ypos > b.ypos;
	// else return a.frame > b.frame;
	// return a.frame > b.frame || a.ypos > b.ypos;
	return a.ypos > b.ypos;
}

void Enemy::sitDraw() {
	GLuint texture;
	if (fwd)
		texture = enemy_tex[4];
	else
		texture = enemy_tex[5];

	slice = 0;

	float inc = 0.25;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(  0, 1); glVertex2i(-size,      0);
		glTexCoord2f(inc, 1); glVertex2i( size,      0);
		glTexCoord2f(inc, 0); glVertex2i( size, 2*size);
		glTexCoord2f(  0, 0); glVertex2i(-size, 2*size);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Enemy::moveDraw() {
	GLuint texture;
	if (fwd)
		texture = enemy_tex[2];
	else
		texture = enemy_tex[3];

	float inc = 0.125;
	float start = inc * slice;
	float end = start + inc;

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(start, 1); glVertex2i(-size,      0);
		glTexCoord2f(  end, 1); glVertex2i( size,      0);
		glTexCoord2f(  end, 0); glVertex2i( size, 2*size);
		glTexCoord2f(start, 0); glVertex2i(-size, 2*size);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);

	slice = (slice + 1) % 8;
}

void Enemy::standupDraw() {
	GLuint texture;
	if (fwd)
		texture = enemy_tex[4];
	else
		texture = enemy_tex[5];

	float inc = 0.25;
	float start = slice * inc;
	float   end = start + inc;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(start, 1); glVertex2i(-size,      0);
		glTexCoord2f(  end, 1); glVertex2i( size,      0);
		glTexCoord2f(  end, 0); glVertex2i( size, 2*size);
		glTexCoord2f(start, 0); glVertex2i(-size, 2*size);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (slice == 3) {
		stood = true;
		slice = 0;
	} else {
		slice++;
	}
}

void Enemy::sitdownDraw() {
	GLuint texture;
	if (fwd)
		texture = enemy_tex[4];
	else
		texture = enemy_tex[5];
	float inc = 0.25;
	slice = (slice + 3) % 4;
	float start = inc * slice;
	float   end = start + inc;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(start, 1); glVertex2i(-size,      0);
		glTexCoord2f(  end, 1); glVertex2i( size,      0);
		glTexCoord2f(  end, 0); glVertex2i( size, 2*size);
		glTexCoord2f(start, 0); glVertex2i(-size, 2*size);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (slice % 4 == 0) {
		stood = false;
		slice = 0;
	}
}

void Enemy::Move(int x, int y) {
	double dx = -((double)xpos - x);
	double dy = -((double)ypos - y);
	double dist = sqrt( pow(dx, 2.0) + pow(dy, 2.0) );
	if (dist < 0.3 * gl->xres && alive) {
		near = true;
		if (dx > 0) {
			fwd = true;
		} else {
			fwd = false;
		}
	} else {
		near = false;
	}

	if (near && dist < 0.2 * gl->xres) {
		mov = true;
	} else {
		mov = false;
	}

	if (dist < 50 && alive) {
		Attack();
	}

	if (mov && alive) {
		double dx_enemy = dx * step / dist;
		double dy_enemy = dy * step / dist;
		if (xpos > gl->xres + size) {
			frame++;
			xpos = -size;
		} else if (xpos < -size) {
			frame--;
			xpos = gl->xres + size;
		}
		xpos += dx_enemy;
		ypos += dy_enemy;
	}
}

void Enemy::Attack() {
	/*
	GLuint texture;
	if (fwd) texture = enemy_tex[8];
	else texture = enemy_tex[9];

	float inc = 0.125;
	float start = inc * slice;
	float   end = start + inc;

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(start, 1); glVertex2i(-size,      0);
		glTexCoord2f(  end, 1); glVertex2i( size,      0);
		glTexCoord2f(  end, 0); glVertex2i( size, 2*size);
		glTexCoord2f(start, 0); glVertex2i(-size, 2*size);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);
	* */
	  mov = false;
	stood = true;
}

void Enemy::Die() {
	alive = false;
	mov = false;
	GLuint texture;
	if (fwd)
		texture = enemy_tex[6];
	else
		texture = enemy_tex[7];

	float inc = 0.125;
	float start = inc * slice;
	float end = start + inc;

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(start, 1); glVertex2i(-size,      0);
		glTexCoord2f(  end, 1); glVertex2i( size,      0);
		glTexCoord2f(  end, 0); glVertex2i( size, 2*size);
		glTexCoord2f(start, 0); glVertex2i(-size, 2*size);
	glEnd();
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (slice < 7) slice++;
}
