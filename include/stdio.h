#ifndef _stdio_
#define _stdio_

#define STDIN  0
#define STDOUT 1
#define STDERR 2

#include "sh.h"
#include "stdargs.h"

typedef struct {
	int file_desc;
	char lastChar;
} FILE;



int printf(const char * fmt, ...);
int vprintf(const char * fmt, va_list args);
int vfprintf(FILE * stream, const char * fmt, va_list args);
int print_str(char * str, FILE * stream);
int print_dec(int num, FILE * stream);
int print_hex(int num, FILE * stream);
void putc(int ch, FILE * stream);
int getc(FILE * stream);
void putChar(int ch);
int getChar();
int isDigit(int ch);
int read(int file_desc, char * buffer, int cant);
int write(int file_desc, char * buffer, int cant);


#endif
