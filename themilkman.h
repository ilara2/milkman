
#ifndef THEMILKMAN_H_
#define THEMILKMAN_H_

#include <X11/Xlib.h>
// #include "player.h"

void initOpengl();
int checkKeys(XEvent *e);
void render();
void physics();

// enum stages {err, start, lvl_1, lvl_2, credits, control};
// enum dir {err, up, down, left, right};

#endif
