#include "../include/kasm.h"
#include "../include/keyboard_handler.h"
#include "../include/terminal.h"

static char keyboard[4][32] = {{"0012345678900000qwertyuiop00\n0as"},
			       {"dfghjkl00000zxcvbnm,.-000 000000"},
			       {"00!\"#$%&/()=0000QWERTYUIOP00\n0AS"},
			       {"DFGHJKL00000ZXCVBNM;:_000 000000"}};


static int shift = 0;

void int_09_handler() {

	char input;
	int scancode = _inb(0x60);

	if(is_make_code(scancode)) {

		if(is_shift(scancode)){
			shift = 2;
			_Sti();
			return;
		}
		
		int r = get_scancode_row(scancode);
		int c = get_scancode_col(scancode);

		if(r < 0 || r > 1 || c < 0 || c > 31){
			_Sti();
			return;
		}
		

		if(scancode == BACKSPACE) {
			input = '\b';
		}else {
			if(keyboard[r][c] == '0'){
				if(r == 0 && c == 11)/* row and col of the real 0 */
					input = keyboard[r + shift][c];
				else{
					_Sti();
					return;
				}
			}
			input = keyboard[r + shift][c];
		}

		terminal_input(input);
		
	}else if(is_shift_released(scancode))
		shift = 0; 
	_Sti();
}

/* The first 3 bits of the scancode byte indicate the row in the keyboard matrix,
 * the other 5 indicate the colum */

int get_scancode_row(int scanc){
	return (int)(scanc >> 5);
}
int get_scancode_col(int scanc){
	return (int)(scanc & 0x1F);
}

int is_shift(int scancode){
	return (scancode == 0x2A || scancode == 0x36);
}
int is_shift_released(int scancode){
	return (scancode == 0xAA || scancode == 0xB6);
}

int is_make_code(int scancode){
	return (scancode >> 7) == 0;
}
int is_break_code(int scancode){
	return !is_make_code(scancode);
}

