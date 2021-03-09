
#ifndef CLOUD_H_
#define CLOUD_H_

#include <GL/glx.h>
#include "../utils/image.h"

class Cloud {
	int    xpos, ypos;
	int    dx, dy;
	int    size;
	static const char* cloud_img[8];
	GLuint texid;
public:
	Cloud();
	void draw();
	void refresh();
	void move();
	int  getX() {return xpos;}
	int  getY() {return ypos;}
};

#endif
