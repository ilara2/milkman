
#include "start.h"
#include "../utils/global.h"
#include "displays.h"
#include <stdio.h>
#include <stdlib.h>

extern Global* gl;
extern Displays* display;

Start::Start() {
	printf("Start in\n");
	clouds = new Cloud[10];
	setForeground("./images/startmenu/title.png");
	enemies_num = 0;
	frame = 0;
	selected = 0;
	initMenu();
}

Start::~Start() {
	printf("Start out\n");
}

void Start::on() {
	float   red =  78.0 / 255;
	float green = 173.0 / 255;
	float  blue = 245.0 / 255;

	glClearColor(red, green, blue, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	showClouds();
	showTitle();
	showOptions();
	checkKeys();
}

void Start::showOptions() {
	unsigned char font_size ;
	unsigned char font_width;
	for (int i = 0; i < (int)(sizeof(menu)/sizeof(menu[0])); i++) {
		if (i == selected) {
			font_size = gl->yres / 40;
			font_width = gl->xres / 9;
		} else {
			font_size = gl->yres / 50;
			font_width = gl->xres / 10;
		}
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(gl->xres/2, gl->yres/3 - (50 * i), 0);
		glBindTexture(GL_TEXTURE_2D, menu[i]);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1);  glVertex2i (-font_width, -font_size );
			glTexCoord2f( 1, 1);  glVertex2i ( font_width, -font_size );
			glTexCoord2f( 1, 0);  glVertex2i ( font_width,  font_size );
			glTexCoord2f( 0, 0);  glVertex2i (-font_width,  font_size );
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_ALPHA_TEST);
	}	
}

void Start::initMenu() {
	Image menu_imgs[] = {
		Image("./images/startmenu/start.png"),
		Image("./images/startmenu/controls.png"),
		Image("./images/startmenu/credits.png")
	};
	
	for (int i = 0; i < (int)(sizeof(menu)/sizeof(menu[0])); i++) {
		glGenTextures(1, &menu[i]);
		glBindTexture(GL_TEXTURE_2D, menu[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    
		unsigned char* new_img = Image::buildAlphaData(&menu_imgs[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, menu_imgs[i].width, menu_imgs[i].height, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, new_img);
		free(new_img);		
	}
}

int Start::checkKeys() {
	static bool flag = true;
	bool up = (gl->keys[XK_Up] || gl->keys[XK_w]);
	bool down = (gl->keys[XK_Down] || gl->keys[XK_s]);
	bool space = (gl->keys[XK_space]) ? true : false;
	if (gl->keys[XK_1] && flag)
		display->select(lvl_1);
	if (gl->keys[XK_2] && flag)
		display->select(lvl_2);
	if (gl->keys[XK_equal] && flag)
		display->select(test);
	if ( up && flag) {
		selected = (selected + 2) % 3;
		flag = false;
	}
	if ( down && flag) {
		selected = (selected + 1) % 3;
		flag = false;
	}
	if (space && flag) {
		flag = false;
		switch(selected) {
			case 0:
				display->select(lvl_1);
				break;

			case 1:
				display->select(control);
				break;

			case 2:
				display->select(credits);
				break;
			
			default:
				display->select(err_stage);
		}
	}
	if (!up and !down and !space)
		flag = true;
	return 0;
}

void Start::showTitle() {
	static float  width = 14;
	static float height =  2;

	int max_width = 1050 * gl->yres/ 700;

	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(gl->xres/2, gl->yres*(5.0 / 6.0), 0);
	glBindTexture(GL_TEXTURE_2D, foreground_tex);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i (-width/2, -height/2);
		glTexCoord2f(1.0f, 1.0f); glVertex2i ( width/2, -height/2);
		glTexCoord2f(1.0f, 0.0f); glVertex2i ( width/2,  height/2);
		glTexCoord2f(0.0f, 0.0f); glVertex2i (-width/2,  height/2);
	glEnd();

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);

	float rate = 1.2;

	static int d_width = 200;
	if (width < max_width + d_width) {
		width *= rate;
		height *= rate;
		d_width = 0;
	} else {
		width = max_width;
		height = width / 7;
	}
}

void Start::showClouds() {
	for (int i = 0; i < 10; i++) {
		clouds[i].draw();
		clouds[i].move();
	}
}
