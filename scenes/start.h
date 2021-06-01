
#ifndef START_H_
#define START_H_

#include "scenes.h"
#include "cloud.h"

class Start: public Scenes {
public:
	Start();
	~Start();
	void on();
	int checkKeys();
	void initMenu();
	void showClouds();
	void showTitle();
	void showOptions();

	Cloud* clouds;
	GLuint menu[3];
	int selected;
};

#endif
