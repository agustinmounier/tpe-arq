#ifndef _mouse_handler_
#define _mouse_handler_

#define MAX_X 80
#define MAX_Y 25

void int_74_handler(unsigned char m_byte);
void wait_to_write();
void wait_to_read();
void mouse_write(unsigned char input);
unsigned char mouse_read();
void mouse_init();
void disable_vga_cursor();

#endif
