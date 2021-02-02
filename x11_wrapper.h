
#ifndef X11_H_
#define X11_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>

class X11_Wrapper {
	Display *dpy;
	Window win;
public:
	X11_Wrapper();
	~X11_Wrapper();
	void setTitle();
	void setupScreenRes(const int, const int);
	void reshapeWindow(int, int);
	void checkResize(XEvent*);
	XEvent getXNextEvent();
	void swapBuffers();
	bool getXPending() { return XPending(dpy); }
};

#endif
