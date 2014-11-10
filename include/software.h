#ifndef _software_
#define _software_

#define CLEAR_FUNC -10
#include "defs.h"

int clear_func();
void printIDT();
void printINTinfo(DESCR_INT * inter);
void set_speaker_frec(int frec);
void play_speaker(int ms);
void stop_speaker();
void wait(int ms);
void print_BIOS_info();

#endif
