
#include "cloud.h"
#include "global.h"
#include <stdlib.h>

extern Global* gl;

const char* Cloud::cloud_img[] = {
	"./images/startmenu/cloud1.jpg",
	"./images/startmenu/cloud2.jpg",
	"./images/startmenu/cloud3.jpg",
	"./images/startmenu/cloud4.jpg",
	"./images/startmenu/cloud5.jpg",
	"./images/startmenu/cloud6.jpg",
	"./images/startmenu/cloud7.jpg",
	"./images/startmenu/cloud8.jpg",
};

Cloud::Cloud() {
	dx = rand() % 3 + 2;
	dy = 1;
	xpos = (rand() % gl->xres);
	ypos = (rand() % gl->yres);
	size = rand() % 100 + 200;
	Image img = Image(cloud_img[rand()%8]);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *new_img = Image::buildAlphaData(&img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, new_img);
	free(new_img);
}

void Cloud::draw() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(xpos-(size/2), ypos-(size/2), 0);
	glBindTexture(GL_TEXTURE_2D, texid);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i (   0,    0);
		glTexCoord2f(1.0f, 1.0f); glVertex2i (size,    0);
		glTexCoord2f(1.0f, 0.0f); glVertex2i (size, size);
		glTexCoord2f(0.0f, 0.0f); glVertex2i (   0, size);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);
}

void Cloud::refresh() {
	size = rand() % 100 + 200;
	dx = rand() % 3 + 2;
	dy = 1;
	xpos = -size/2;
	ypos = rand() % gl->yres - size;
}

void Cloud::move() {
	ypos += dy;
	xpos += dx;
	if (xpos > gl->xres+(size/2) || ypos > gl->yres+(size/2))
		refresh();
}
