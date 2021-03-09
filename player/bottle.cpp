
#include "bottle.h"
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

extern Global* gl;
extern Player player;
GLuint Bottle::bottle_tex;
bool Bottle::flag = false;

void Bottle::init() {
	Image img = Image("./images/player/bottle.png");
	glGenTextures(1, &bottle_tex);
	glBindTexture(GL_TEXTURE_2D, bottle_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *new_img = Image::buildAlphaData(&img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, new_img);
	free(new_img);
}

Bottle::Bottle() {
	if (!flag) {
		init();
		flag = true;
	}
	size = 15;
}

void Bottle::display() {
	if (active) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glPushMatrix();
		glTranslatef(xpos, ypos, 0);
		glRotatef( ds, 0.0f, 0.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, bottle_tex);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2i(-size, -size);
			glTexCoord2f(1, 1); glVertex2i( size, -size);
			glTexCoord2f(1, 0); glVertex2i( size,  size);
			glTexCoord2f(0, 0); glVertex2i(-size,  size);
		glEnd();
		glPopMatrix();
		glDisable(GL_ALPHA_TEST);
		glBindTexture(GL_TEXTURE_2D, 0);

		update();
		checkBounds();
	}

}

void Bottle::checkBounds() {
	if (xpos > gl->xres || xpos < 0)
		active = false;
	if (ypos > gl->yres || ypos < 0)
		active = false;
}

void Bottle::update() {
	switch(direction) {
		case up:
			ypos += 10;
			ds -= 25;
			break;

		case down:
			ypos -= 10;
			ds += 25;
			break;

		case left:
			xpos -= 10;
			ds += 25;
			break;

		case right:
			xpos += 10;
			ds -= 25;
			break;
		
		case err_shoot:
			break;

		default:
			break;
	}

}

void Bottle::throwBottle(attack_dir dir, int x, int y) {
	xpos = x;
	ypos = y;
	direction = dir;
	active = true;
}

