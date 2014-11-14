#ifndef _mouse_handler_
#define _mouse_handler_

#define MAX_X 80
#define MAX_Y 25

#define MOUSE_COLOR 0x57
#define LCLICK_COLOR 0xC7
#define RCLICK_COLOR 0x17

#define SENS_X 10
#define SENS_Y 10

typedef struct{
	int x, y;
	unsigned char l_click, r_click;
} tMouse;

void int_74_handler(unsigned char m_byte);
void wait_to_write();
void wait_to_read();
void send_mouse_comand(unsigned char comand);
void set_compaq_status();
int is_ack();
void mouse_init();
void set_mouse_settings();
void enable_ps2_aux_input();

#endif
