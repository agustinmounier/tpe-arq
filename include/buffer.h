#ifndef _buffer_
#define _buffer_

#define BUFFER_SIZE 	512

typedef struct {
	char * start;
	int size;
	int head;
	int tail;
} bufferCDT;

void buffer_init(bufferCDT * buffer, char * start, int size);
void add_to_buffer(bufferCDT * buffer, char input);
void clear_buffer(bufferCDT * buffer);
char buffer_pop(bufferCDT * buffer);


#endif
