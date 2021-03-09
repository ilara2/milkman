
#include "global.h"
#include <string.h>
#include <stdio.h>

Global Global::instance;

Global::Global() {
	xres = 900;
	yres = 500;
	fps = 1.0 / 60;
	memset(keys, 0, 65536);	
}

Global::~Global() {}

Global& Global::getInstance() { return instance; }

Global* gl = &gl->getInstance();
