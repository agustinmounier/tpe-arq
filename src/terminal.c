#include "../include/terminal.h"
#include "../include/keyboard_handler.h"
#include "../include/buffer.h"
#include "../include/video_handler.h"
#include "../include/stdio.h" /* TODO: sacar */
#include "../include/software.h"

static bufferCDT * kBuffer;
static char keyboard_buffer[BUFFER_SIZE];
static int shBufferIndex = 0;

void terminal_init(){
	buffer_init(kBuffer, keyboard_buffer, BUFFER_SIZE);
}


void terminal_input(char input){

	add_to_buffer(kBuffer, input);

	if(input == '\b'){
		video_backspace();
	}else if(input == '\n'){
		video_enter();
	}else{
		video_input(input);
	}	
}

int read_from_terminal(char * shBuffer, int cant){
	
	int cantRead = 0;
	
	while(cantRead < cant){
	
		char input = buffer_pop(kBuffer);
		
		
		if(input == -1){ /* keyboard buffer is empty */
			return cantRead;
		}else if(input == '\n'){
			shBuffer[shBufferIndex] = input;
			shBufferIndex = 0;
			cantRead++;
			return cantRead;
		}else if(input != '\b'){
			shBuffer[shBufferIndex] = input;
			shBufferIndex++;
		}else if(shBufferIndex > 0)
			shBufferIndex--;

		cantRead++;
	}

	return cantRead;

}

int write_to_terminal_buffer(char * buffer, int cant){
	
	int i;

	for(i = 0; i < cant; i++){
		add_to_buffer(kBuffer, buffer[i]);
	}
	
	return i;

}

int write_to_terminal(char * buffer, int cant){

	int i;
	for(i = 0; i < cant; i++){
	
		switch(buffer[i]){
	
			case '\n':
				video_enter();
				break;
			default:
				video_input(buffer[i]);
				break;
		}
			
	}
	return i;
}
