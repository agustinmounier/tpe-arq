#ifndef _sh_
#define _sh_

#define SH_BUFFER_SIZE 512
#define CANT_COMANDS 2
#define BUFFER_EMPTY -1



typedef struct {
	int cantArgs;
	char (*args)[10];
}tParams;

typedef int (*tFunc)(tParams * params);

typedef struct {
	char * name;
	tFunc func;
} shComand;

void shell_init();
void parse_shBuffer(char * shBuffer);
int getComand(char * query, char * comand);
int isComand(char * comand);


#endif
