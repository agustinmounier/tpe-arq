#ifndef _terminal_
#define _terminal_

void terminal_init();
void terminal_input(char input);
int read_from_terminal(char * shBuffer, int cant);
int write_to_terminal_buffer(char * buffer, int cant);
int write_to_terminal(char * buffer, int cant);

#endif
