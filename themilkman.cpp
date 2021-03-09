
#include "themilkman.h"
#include "utils/global.h"
#include "scenes/displays.h"
#include "player/player.h"
#include "enemy/enemy.h"
#include "utils/fonts.h"
#include "utils/x11_wrapper.h"
#include <GL/glx.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern Global* gl;
extern Displays* display;
X11_Wrapper x11 = X11_Wrapper();

int main() {
	Enemy::init();
	srand(time(NULL));
	clock_t begin;
	double duration;
	initOpengl();
	int done = 0;

	display->select(start);
	while (!done) {
		begin = clock();
		physics();
		render();
		while (x11.getXPending() ) {
			XEvent e = x11.getXNextEvent();
			x11.checkResize(&e);			
			done = checkKeys(&e);
		}
		x11.swapBuffers();
		duration = (double)( clock() - begin ) / (double) CLOCKS_PER_SEC;			
		while (duration < gl->fps) {
			duration = (double)( clock() - begin ) / (double) CLOCKS_PER_SEC;
		};
	}
	cleanup_fonts();
	return 0;
}

void initOpengl() {
	//OpenGL initialization
	glViewport(0, 0, gl->xres, gl->yres);

	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();

	//This sets 2D mode (no perspective)
	glOrtho(0, gl->xres, 0, gl->yres, -1, 1);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);

	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//glClear(GL_COLOR_BUFFER_BIT);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
}

int checkKeys(XEvent *e) {
	static int shift = 0;

	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	
	int key = XLookupKeysym(&e->xkey, 0);
	if (key >= 65536) return 0;

	if (e->type == KeyRelease) {
		gl->keys[key] = 0;
	} else if (e->type == KeyPress) {
		gl->keys[key] = 1;
	}
	gl->keys[key] = 1;
	if (e->type == KeyRelease) {
		gl->keys[key] = 0;
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift = 0;
		}
		return 0;
	}
	gl->keys[key] = 1;
	if (key == XK_Shift_L || key == XK_Shift_R) {
		shift = 1;
		return 0;
	}
	(void)shift;

	if (gl->keys[XK_Escape]) {
		display->select(exit_out);
		return 1;
	}
	
	return 0;
}

void render() {
	display->show();
}

void physics() {}
