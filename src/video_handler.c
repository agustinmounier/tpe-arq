#include "../include/video_handler.h"
#include "../include/lib.h"
#include "../include/kasm.h"
#include "../include/kc.h"
#include "../include/sh.h"
char *video = (char *) 0xb8000;	
static int cursor_pos;
static int cursor_row;
static char comand_prompt[] = "$:";

void video_init(){

	cursor_pos = 0;
	cursor_row = 0;
}

void video_input(char input){

	if(cursor_pos >= (25 * 80 * 2)){
		/*if(video[cursor_pos - 160] != '$')
			display_more();
		else*/
			video_screen_up();
	}


	video[cursor_pos] = input;

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

	int cursor_col_pos = (cursor_pos % 160);

	cursor_pos+= (160 - cursor_col_pos);		
	
	cursor_row = 0;

}
void video_string(char * string){
	
	int lenght = strlen(string);
	int i = 0;

	for (; i < lenght; i++)
		video_input(string[i]);
	

}

void video_clear(){
	
	int i = 0;

	while(i < (80*25*2)){
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

void video_screen_up(){
	
	int i = 160;

	while(i < (80*25*2)){
		video[i - 160] = video[i];
		i += 2;
	};
	
	for(i -= 160; i <= (80*25*2); i += 2){
		video[i] = ' ';
	}

	cursor_pos -= 160;
	
}

void display_more(){

	video_screen_up();
	shell_display_more();

}

/* SACADO DE OSDEV */
void video_update_cursor(int cursor_pos){

	_outb(0x03D4, 0x0E);
	_outb(0x03D5, (cursor_pos/2) >> 8);
	
	_outb(0x03D4, 0x0F);
	_outb(0x03D5, (cursor_pos)/2);

}
