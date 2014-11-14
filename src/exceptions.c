#include "../include/exceptions.h"
#include "../include/stdio.h"
#include "../include/kasm.h"
#include "../include/syscall_hand.h"

static int freq_excp[] = {400, 500, 600};
static char exceptions[3][25] = {"Zero divide", "Bound range exceeded", "Invalid opcode"};

void div_by_zero_hand(){

	_syscall(SET_FREQ, 0, freq_excp[0], 0);
	_syscall(PLAY_SPEAKER, 0, 10, 0);
	printf("Exception: Divide-by-zero ocurred.\n");
}

void invalid_opcode_hand(){
	_syscall(SET_FREQ, 0, freq_excp[2], 0);
	_syscall(PLAY_SPEAKER, 0, 10, 0);
	printf("Exception: Invalid opcode ocurred.\n");
}

void index_out_bounds_hand(){

	_syscall(SET_FREQ, 0, freq_excp[1], 0);
	_syscall(PLAY_SPEAKER, 0, 10, 0);
	printf("Exception: Bound Range Exceeded ocurred.\n");
}

void triger_bound_excep(){

	int index = 12;
	int bounds[] = {0, 10};
	
	_check_bounds(index, bounds);
}

void set_freq(int excp, int freq){

	freq_excp[excp] = freq;	
	printf("Frequency of exception: %s is now set to: %d Hz.\n", exceptions[excp], freq);

}

void trigger_excp(int excp){
	_syscall(EXCEPTION, 0, excp, 0);
}
