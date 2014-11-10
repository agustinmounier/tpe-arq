#ifndef _syscall_hand_
#define _syscall_hand_


#define WRONG_FILE_DESC -1
#define READ		0
#define WRITE		1

int int_80(int func, int file_desc, int arg1, int arg2);

#endif
