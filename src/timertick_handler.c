#include "../include/timertick_handler.h"


static int ticks = 0;


void int_08(){
	ticks++;
}

int getTicks(){
	return ticks;
}
