#include "../../include/kasm.h"
#include "../../include/syscall_hand.h"
#include "../../include/software.h"

void sounds(){
	
	_syscall(SET_FREQ, 0, 500, 0);
	_syscall(PLAY_SPEAKER, 0, 500, 0);
	_syscall(SET_FREQ, 0, 300, 0);
	_syscall(PLAY_SPEAKER, 0, 500, 0);
	_syscall(SET_FREQ, 0, 700, 0);
	_syscall(PLAY_SPEAKER, 0, 500, 0);

}
