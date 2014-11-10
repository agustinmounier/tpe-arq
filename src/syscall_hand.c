#include "../include/syscall_hand.h"
#include "../include/stdio.h"
#include "../include/io.h"

int int_80(int func, int file_desc, int arg1, int arg2){
	
	int ans = WRONG_FILE_DESC;	

	switch(func){
		case READ:
			ans = read_io(file_desc, (char *)arg1, arg2);
			break;
		case WRITE:
			ans = write_io(file_desc, (char *)arg1, arg2);
			break;
	}
	
	return ans;

}
