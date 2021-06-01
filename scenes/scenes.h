
#ifndef SCENES_H_
#define SCENES_H_

#include "../utils/image.h"
#include <GL/glx.h>
#include <vector>
#include "../player/player.h"
#include "../enemy/enemy.h"
#include "../enemy/ai_enemy.h"

class Scenes {
public:
	
	GLuint background_tex;
	GLuint foreground_tex;

	int enemies_num;
	int frame;

	static Player player;
	std::vector<Enemy> enemies;
	std::vector<AI_Enemy> ai_enemies;

	Scenes();
	virtual ~Scenes();
	void setBackground(const char*);
	void setForeground(const char*);
	void drawScene(GLuint);
	void sortEnemies();
	void sortAIEnemies();
	void refreshEnemies();
	void refreshAIEnemies();
	virtual void on() = 0;
	virtual int checkKeys() = 0;
};

#endif
