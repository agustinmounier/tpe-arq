#include "../include/syscall_hand.h"
#include "../include/video_handler.h"
#include "../include/stdio.h"
#include "../include/io.h"
#include "../include/defs.h"
#include "../include/kc.h"
#include "../include/pc_speaker.h"
#include "../include/exceptions.h"

int int_80_handler(int func, int file_desc, int arg1, int arg2){
	
	int ans = 0;	

	switch(func){

		case READ:
			ans = read_io(file_desc, (char *)arg1, arg2);
			break;
		case WRITE:
			ans = write_io(file_desc, (char *)arg1, arg2);
			break;
		case CLEAR_FUNC:
			video_clear();
			break;
		case INFO_IDT:
			ans = get_idt((IDTR *)arg1);
			break;
		case SET_FREQ:
			ans = set_speaker_freq((int)arg1);
			break;
		case PLAY_SPEAKER:
			ans = play_speaker((int)arg1);
			break;
		case GET_SMBIOS:
			ans = getSMBIOS((char **)arg1);
			break;
		case SET_EXCP_FREQ:
			set_excp_freq(arg1, arg2);
			break;
		case EXCEPTION:
			switch( arg1 ){

				case 1:
					_div_zero();
					break;
				case 2:
					triger_bound_excep();
					break;
				case 3:
					_invalid_opcode();
					break;

			}
			break;
	}
	
	return ans;

}
