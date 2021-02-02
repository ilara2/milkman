
#include "x11_wrapper.h"

#include <GL/glx.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "player.h"

extern Global* gl;

X11_Wrapper::~X11_Wrapper() {
	printf("x11_wrapper out\n");
	XDestroyWindow(dpy, this->win);
	XCloseDisplay(dpy);
}

X11_Wrapper::X11_Wrapper() {
	GLuint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
	XSetWindowAttributes swa;
	setupScreenRes(gl->xres, gl->yres);
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, (int*)att);
	if (vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, gl->xres, gl->yres, 0,
		vi->depth, InputOutput, vi->visual,
		CWColormap | CWEventMask, &swa);

	//-------------------------------------------------------------------------
	// Disable Window Resize
	XSizeHints *hints;
	hints = XAllocSizeHints();

	hints->min_width  = gl->xres;
	hints->max_width  = gl->xres;
	hints->min_height = gl->yres;
	hints->max_height = gl->yres;

	hints->flags |= PMinSize;
	hints->flags |= PMaxSize;

	XSetWMNormalHints(dpy, win, hints);
	//-------------------------------------------------------------------------

	GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	setTitle();
}

void X11_Wrapper::setTitle() {
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "The Milkman");
}

void X11_Wrapper::setupScreenRes(const int w, const int h) {
	gl->xres = w;
	gl->yres = h;
}

void X11_Wrapper::reshapeWindow(int width, int height) {
	//window has been resized.
	setupScreenRes(width, height);
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, gl->xres, 0, gl->yres, -1, 1);
	setTitle();
}

void X11_Wrapper::checkResize(XEvent *e) {
	//The ConfigureNotify is sent by the
	//server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != gl->xres || xce.height != gl->yres) {
		//Window size did change.
		reshapeWindow(xce.width, xce.height);
	}
}

XEvent X11_Wrapper::getXNextEvent() {
	XEvent e;
	XNextEvent(dpy, &e);
	return e;
}

void X11_Wrapper::swapBuffers() {
	glXSwapBuffers(dpy, win);
}
