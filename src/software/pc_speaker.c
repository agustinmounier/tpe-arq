#include "../../include/software.h"
#include "../../include/timertick_handler.h"

/* SACADO DE OSDEV */

void set_speaker_frec(int freq){

	int div = 1193180 / freq; /* 1193180 is the PIT frequency */
	
	_outb(0x43,0xb6); /* sets the mode of the PIT */
	_outb(0x42, (short int)div); /* sets frec on channel 2 of the PIT */
	_outb(0x42, (short int)(div >> 8));

}

void play_speaker(int ms){

	short int tmp;
	tmp = _inb(0x61);
	if (tmp != (tmp | 3)){
		_outb(0x61, tmp | 3);
	}
	wait(ms);
	stop_speaker();
}

void stop_speaker(){

	short int tmp;
	tmp = (_inb(0x61) & 0xFC);
	_outb(0x61, tmp);

}

void wait(int ms){
	
	int end = getTicks() + ms;
	while (getTicks() < end){};

}