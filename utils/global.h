
#ifndef GLOBAL_H_
#define GLOBAL_H_

enum stages {err_stage, start, lvl_1, lvl_2, credits, control, exit_out};
enum attack_dir {err_shoot, up, down, left, right};

class Global {
	Global();
	static Global instance;
public:
	~Global();
	Global(const Global&) = delete;
	void operator=(const Global&) = delete;
	static Global& getInstance();
	unsigned char keys[65536];
	int xres, yres;
	double fps;
};


#endif
