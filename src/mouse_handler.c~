#include "../include/mouse_handler.h"
#include "../include/video_handler.h"
#include "../include/pc_speaker.h"

static unsigned char m_bytes[3];
static int m_byte_index = 0;

static int sens_x = 0;
static int sens_y = 0;

static tMouse mouse;


void int_74_handler(unsigned char m_byte){
	
	if(m_byte_index == 0 && (m_byte & 0x08) == 0)
		return;
	
	m_bytes[m_byte_index] = m_byte;
	m_byte_index++;

	if(m_byte_index >= 3){

		m_byte_index = 0;

		char info_byte = (signed char)m_bytes[0];

		if((info_byte & 0x80) != 0 || (info_byte & 0x40) != 0)
			return;

		char x_byte = (signed char)m_bytes[1];
		char y_byte = (signed char)m_bytes[2];
		
		if((info_byte & 1) == 1)
			mouse.l_click = 1;
		else
			mouse.l_click = 0;

		if((info_byte & 2) == 2)
			mouse.r_click = 1;
		else
			mouse.r_click = 0;

		if(x_byte > 0){
			sens_x += (int)x_byte;
			if(sens_x >= SENS_X){
				mouse.x++;
				sens_x = 0;
				if(mouse.x >= MAX_X)
					mouse.x = MAX_X - 1;
			}	
		}else if(x_byte < 0){
			sens_x += (int)x_byte;
			if(sens_x <= -SENS_X){
				mouse.x--;
				sens_x = 0;
				if(mouse.x < 0)
					mouse.x = 0;
			}	
		}

		if(y_byte > 0){
			sens_y += (int)y_byte;
			if(sens_y >= SENS_Y){
				mouse.y--;
				sens_y = 0;
				if(mouse.y < 0)
					mouse.y = 0;
			}	
		}else if(y_byte < 0){
			sens_y += (int)y_byte;
			if(sens_y <= -SENS_Y){
				mouse.y++;
				sens_y = 0;
				if(mouse.y >= MAX_Y){
					mouse.y = MAX_Y - 1;
				}
			}	
		}
		
		if(mouse.l_click)		
			update_mouse(mouse.x, mouse.y, LCLICK_COLOR);
		else if(mouse.r_click)
			update_mouse(mouse.x, mouse.y, RCLICK_COLOR);
		else
			update_mouse(mouse.x, mouse.y, MOUSE_COLOR);

	}
}

void wait_to_write(){ // Waits until bit 1 of port 0x64 is 0
	unsigned int timeout = 10000;

	while(timeout){

		if((_inb(0x64) & 2) == 0)
	      		return;
		timeout--;
	}

}

void wait_to_read(){// Waits until bit 0 of port 0x64 is 1. Indicates that a byte is available to be read on port 0x60
	unsigned int timeout = 10000;

	while(timeout){

		if((_inb(0x64) & 1) == 1) 
	      		return;
		timeout--;
	}

}

void send_mouse_comand(unsigned char comand){

	wait_to_write();
	_outb(0x64, 0xD4); // Before sending a command one must send this byte first.
	wait_to_write();
	_outb(0x60, comand);

}



int is_ack(){

	wait_to_read();
	if(_inb(0x60) == 0xFA)// ACK byte = 0xFA
		return 1;
	return 0;

}


void mouse_init(){

	mouse.x = 0;
	mouse.y = 0;

	mouse.l_click = 0;
	mouse.r_click = 0;

	enable_ps2_aux_input();
	set_compaq_status();
	set_mouse_settings();
 	
}

void set_compaq_status(){

	unsigned char status_byte;

	wait_to_write();
	_outb(0x64, 0x20); //request to get compaq status byte.
	wait_to_read();
	status_byte = _inb(0x60); // get compaq status byte.
	status_byte = (status_byte | 2); // sets bit number 1 to enable IRQ12.
	status_byte = (status_byte & 0xDF); //clears bit number 5 to disable mouse clock.
	wait_to_write();
	_outb(0x64, 0x60); // request to set compaq status byte.
	wait_to_write();
	_outb(0x60, status_byte); // sets the compaq status byte. 

}

void set_mouse_settings(){
	
	send_mouse_comand(0xF6);// comand 0xF6 sets the mouse on default settings.
	send_mouse_comand(0xF4);// comand 0xF4 enables packet streaming. 

}

void enable_ps2_aux_input(){
	wait_to_write();
	_outb(0x64, 0xA8);
}

