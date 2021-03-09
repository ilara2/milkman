
#include "scenes.h"
#include "../utils/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

extern Global* gl;
Player Scenes::player;

Scenes::Scenes() {
	frame = 0;
	enemies_num = 0;
	player.bindTex();
	player.addBottles();
	player.resetBottles();
}

Scenes::~Scenes() {}

void Scenes::setForeground(const char* fore) {
	if (fore) {
		Image foreground_img = Image(fore);
		glGenTextures(1, &foreground_tex);
		glBindTexture(GL_TEXTURE_2D, foreground_tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    
		unsigned char* new_img = Image::buildAlphaData(&foreground_img);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, foreground_img.width, foreground_img.height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, new_img);
		free(new_img);
	}	
}

void Scenes::setBackground(const char* back) {
	if (back) {
		Image background_img = Image(back);
		glGenTextures(1, &background_tex);
		glBindTexture(GL_TEXTURE_2D, background_tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, background_img.width, background_img.height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, background_img.data);	
	}
}


void Scenes::drawScene(GLuint tex) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(      0.2 * frame, 1);  glVertex2i (      0,       0);
		glTexCoord2f(0.2 * frame + 0.2, 1);  glVertex2i (gl->xres,       0);
		glTexCoord2f(0.2 * frame + 0.2, 0);  glVertex2i (gl->xres, gl->yres);
		glTexCoord2f(      0.2 * frame, 0);  glVertex2i (      0, gl->yres);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);
}

void Scenes::sortEnemies() {
	std::sort(enemies.begin(), enemies.end(), Enemy::cmp);
}

void Scenes::refreshEnemies() {
	enemies.clear();
	for (int i = 0; i < 4; i++) enemies.push_back(Enemy());
	sortEnemies();
}
