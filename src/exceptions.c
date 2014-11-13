#include "../include/exceptions.h"
#include "../include/stdio.h"
#include "../include/kasm.h"
#include "../include/syscall_hand.h"

static int freq_excp[] = {300, 500, 800};

void div_by_zero_hand(){

	_syscall(SET_FREQ, 0, freq_excp[0], 0);
	_syscall(PLAY_SPEAKER, 0, 10, 0);
	printf("Exception: Divide-by-zero ocurred.\n");
}

void overflow_ocurr_hand(){
	_syscall(SET_FREQ, 0, freq_excp[1], 0);
	_syscall(PLAY_SPEAKER, 0, 10, 0);
	printf("Exception: Overflow ocurred.\n");
}

void index_out_bounds_hand(){

	_syscall(SET_FREQ, 0, freq_excp[2], 0);
	_syscall(PLAY_SPEAKER, 0, 10, 0);
	printf("Exception: Bound Range Exceeded ocurred.");
	return;
}

void triger_bound_excep(){

	int index = 12;
	int bounds[] = {0, 10};
	
	_check_bounds(index, bounds);

}

void set_freq(int excp, int freq){

	freq_excp[excp] = freq;	

}

void trigger_excp(int excp){
	printf("%d", excp);
	_syscall(EXCEPTION, 0, excp, 0);

}
