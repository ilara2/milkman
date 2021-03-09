
#ifndef THEMILKMAN_H_
#define THEMILKMAN_H_

#include <X11/Xlib.h>

void initOpengl();
int checkKeys(XEvent *e);
void render();
void physics();

#endif
