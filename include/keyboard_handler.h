#ifndef _keyboard_handler_
#define _keyboard_handler_

#define BACKSPACE (0x0E)

void keyboard_hand();
int get_scancode_row(int scanc);
int get_scancode_col(int scanc);
int is_shift(int scancode);
int is_shift_released(int scancode);
int is_make_code(int scancode);
int is_break_code(int scancode);
#endif
