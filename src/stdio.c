#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/kasm.h"
#include "../include/syscall_hand.h"
#include "../include/kc.h"
#include "../include/video_handler.h" /* TODO: sacar */
#include "../include/common.h"



FILE _stdin = {STDIN};
FILE _stdout = {STDOUT};
FILE _stderr = {STDERR};




int printf(const char * fmt, ...){
	int resp;
	va_list args;
	
	va_start(args, fmt);
	resp = vprintf(fmt, args);
	va_end(args);

	return resp;

}

int vprintf(const char * fmt, va_list args){
	return vfprintf(&_stdout, fmt, args);
}

int vfprintf(FILE * stream, const char * fmt, va_list args){
	
	int index = 0;
	int written = 0;
	while(fmt[index] != '\0'){

		if(fmt[index] == '%'){
			index++;
			switch(fmt[index]){
				
				case 's':
					written += print_str(va_arg(args, char *), stream);
					break;
				case 'c':
					putc((int)va_arg(args, char *), stream);
					written++;
					break;
				case 'd':
					written += print_dec(va_arg(args, int), stream);
					break;	
				case 'x':
					written += print_hex(va_arg(args, int), stream);
					break;
				case 'b':
					written += print_bin(va_arg(args, int), stream);
					break;		
				default:
					return -1;		
					

			}

		}else{
			putc(fmt[index], stream);
			written++;
		}
		index++;
			
	}

	return written;


}

int print_str(char * str, FILE * stream){

	int i = 0;
	while(str[i] != '\0'){
		putc(str[i], stream);
		i++;
	}
	return i;
}

int print_dec(int num, FILE * stream){
	
	char intStr[33];
	itoa(num, intStr, 10);	
	return print_str(intStr, stream);
	
}

int print_hex(int num, FILE * stream){
	
	char intStr[33];
	itoa(num, intStr, 16);	
	return print_str(intStr, stream);
	
}

int print_bin(int num, FILE * stream){
	
	char intStr[33];
	itoa(num, intStr, 2);	
	return print_str(intStr, stream);
	
}


void putc(int ch, FILE * stream){
	write(stream->file_desc, (char *)(&ch), 1);
}

int getc(FILE * stream){
	char ch;
	read(stream->file_desc, &ch, 1);
	stream->lastChar = 1;
	video_input(ch);
	return ch;
}


void putChar(int ch){
	putc(ch, &_stdout);
}

int getChar(){
	return getc(&_stdin);
}

int isDigit(int ch){
	return (ch >= '0' && ch <= '9');
}

int read(int file_desc, char * buffer, int cant) {
	return _syscall(READ, file_desc, (int)buffer, cant);
}

int write(int file_desc, char * buffer, int cant){
	return _syscall(WRITE, file_desc, (int)buffer, cant);
}



