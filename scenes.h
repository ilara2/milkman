
#ifndef SCENES_H_
#define SCENES_H_

#include "image.h"
#include <GL/glx.h>
#include <vector>
#include "player.h"
#include "enemy.h"

class Scenes {
public:
	
	GLuint background_tex;
	GLuint foreground_tex;

	int enemies_num;
	int frame;

	static Player player;
	std::vector<Enemy> enemies;

	Scenes();
	virtual ~Scenes();
	void setBackground(const char*);
	void setForeground(const char*);
	void drawScene(GLuint);
	void sortEnemies();
	void refreshEnemies();
	virtual void on() = 0;
	virtual int checkKeys() = 0;
};

#endif
