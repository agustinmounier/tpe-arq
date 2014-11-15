#include "../include/buffer.h"




void buffer_init(bufferCDT * buffer, char * start, int size){
	
	buffer->start = start;
	buffer->head = 0;
	buffer->tail = 0;
	buffer->size = size;

}

void add_to_buffer(bufferCDT * buffer, char input){
	if(((buffer->head + 1)%buffer->size) == buffer->tail) /* buffer is full */
		buffer_pop(buffer);
	buffer->start[buffer->head] = input;
	buffer->head = (buffer->head + 1)%buffer->size;
}

void clear_buffer(bufferCDT * buffer){
	buffer->tail = buffer->head;
}

char buffer_pop(bufferCDT * buffer){
	if(buffer->head != buffer->tail) {
		char ans = buffer->start[buffer->tail];
		buffer->tail = (buffer->tail + 1)%buffer->size;
		return ans;
	}
	return -1;
}
