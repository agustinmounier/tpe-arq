#ifndef _syscall_hand_
#define _syscall_hand_


#define WRONG_FILE_DESC -1
#define READ		0
#define WRITE		1
#define CLEAR_FUNC    -10
#define INFO_IDT      -11
#define SET_FREQ      -12
#define PLAY_SPEAKER  -13
#define GET_SMBIOS    -14
#define EXCEPTION     -15
#define DIV_ZERO      -16
#define BOUNDS        -17
#define OVERFLOW      -18

int int_80(int func, int file_desc, int arg1, int arg2);


#endif
