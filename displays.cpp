
#include "displays.h"
#include <stdio.h>
#include <stdlib.h>
#include "start.h"
#include "level_1.h"
#include "level_2.h"

Displays Displays::instance;

Displays::Displays() {}

Displays& Displays::getInstance() {
	return instance;
}

void Displays::show() {
	display->on();
}

int Displays::checkKeys() {
	return display->checkKeys();
}

void Displays::select(stages val) {
	delete display;
	switch(val) {
		case err_stage:
			printf("\n\tSomething when wrong\n\n");
			break;
		
		case start:
			display = new Start;
			break;

		case lvl_1:
			display = new Level_1;
			break;

		case lvl_2:
			display = new Level_2;
			break;

		case credits:
			printf("\nTODO:\n\tCredits\n\n");
			display = new Start;
			break;

		case control:
			printf("\nTODO:\n\tControl\n\n");
			display = new Start;
			break;

		case exit_out:
			printf("\nTODO:\n\tExit\n\n");
			display = nullptr;
			break;

		default:
			printf("Default Screen (from displays.cpp)\n");
			break;
	}
}

void Displays::next() {
}

void Displays::prev() {
}

Displays* display = &display->getInstance();
