#include "../include/kasm.h"
#include "../include/keyboard_handler.h"
#include "../include/terminal.h"


static int count = 0;

static char* keyboard_number_values[] = {"1!","2@","3\"","4$","5%","6&","7/","8(","9)","0=","'?"};
static char* keyboard_row1[] = {"qQ","wW","eE","rR","tT","yY","uU","iI","oO","pP","`^","+*"};
static char* keyboard_row2[] = {"aA","sS","dD","fF","gG","hH","jJ","kK","lL"};
static char* keyboard_row3[] = {"zZ","xX","cC","vV","bB","nN","mM",",;",".:","-_"};

void keyboard_hand() {

	unsigned int scancode = _inb(READ_PORT);
	char input = INVALID;
	if(IS_PRESSED(scancode)) {

		if(scancode == BACKSPACE) {
			input = ASCII_BACKSPACE;
		} else if(scancode == ENTER) {
			input = ASCII_ENTER;
		} else if(scancode == SPACE) {
			input = ' ';
		} else {
			input = scancode_to_char(scancode);
		}

		terminal_input(input);
		
	} 
	
	
	_Sti();
}

static char scancode_to_char(unsigned int scancode) {
	
	int type = classify(scancode);
	if(type == INVALID)
		return type;
	
	switch(type) {
		case NUMBER:
			return keyboard_number_values[scancode - NUMBER_INIT][0];
			break;
		case ROW1:
			return keyboard_row1[scancode - ROW1_INIT][0];
			break;
		case ROW2:
			return keyboard_row2[scancode - ROW2_INIT][0];
			break;
		case ROW3:
			return keyboard_row3[scancode - ROW3_INIT][0];
			break;
	}
}

static int classify(unsigned int scancode) {

	if(NUMBER_INIT <= scancode & scancode<= NUMBER_END) {
		return NUMBER;
	} else if(ROW1_INIT <= scancode & scancode <= ROW1_END){
		return ROW1;
	} else if(ROW2_INIT <= scancode & scancode <= ROW2_END){
		return ROW2;
	} else if(ROW3_INIT <= scancode & scancode <= ROW3_END){
		return ROW3;
	} else {
		return INVALID;
	}
}
