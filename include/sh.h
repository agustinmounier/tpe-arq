#ifndef _sh_
#define _sh_

#define SH_BUFFER_SIZE 512
#define CANT_COMANDS 7
#define BUFFER_EMPTY -1


#include "software.h"

/*
typedef struct {
	int cantArgs;
	char (*args)[10];
}tParams;
*/

typedef void (* tFunc)();

typedef struct {
	char * name;
	tFunc func;
} shComand;



void shell_init();
void parse_shBuffer(char * shBuffer);
int getComand(char * query, char comand[3][15]);
int isComand(char * comand);
void shell_display_more();
void help();


#endif
