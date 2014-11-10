#include "../include/video_handler.h"
#include "../include/lib.h"
#include "../include/kasm.h"
#include "../include/kc.h"

char *video = (char *) 0xb8000;	
static int cursor_pos = 0;
static int cursor_row = 0;
static char comand_prompt[] = "$:";

void video_handler(){



}

void video_input(char input){
	video[cursor_pos]= input;
	cursor_pos+=2;
	cursor_row+=2;
	video_update_cursor(cursor_pos);
}

void video_backspace(){
	if (cursor_row > 4){
		cursor_pos-=2;
		cursor_row-=2;
		video[cursor_pos] = ' ';
		video_update_cursor(cursor_pos);	
	}
}

void video_enter(){
	int cursor_row_pos = ((cursor_pos%80)/2) + 1;
	for (; cursor_row_pos <= 80; cursor_row_pos++){
		cursor_pos+=2;		
	}
	cursor_row = 0;
	video_string(comand_prompt);
}
void video_string(char * string){
	
	int lenght = strlen(string);
	int i = 0;
	for (; i < lenght; i++){
		video_input(string[i]);
	}

}

void video_clear(){
	
	int i = 0;
	while(i < (80*25*2))
	{
		video[i]=' ';
		i++;
		video[i]=WHITE_TXT;
		i++;
	};
	cursor_pos = 0;
	cursor_row = 0;
	video_string(comand_prompt);
	video_update_cursor(cursor_pos);
	
	
}

/* SACADO DE OSDEV */
void video_update_cursor(int cursor_pos){

	_outb(0x03D4, 0x0E);
	_outb(0x03D5, (cursor_pos/2) >> 8);
	
	_outb(0x03D4, 0x0F);
	_outb(0x03D5, (cursor_pos)/2);

}