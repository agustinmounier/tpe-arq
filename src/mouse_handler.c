#include "../include/mouse_handler.h"

static unsigned char m_bytes[3];
static int m_byte_index = 0;
static int mouse_x = 0;
static int mouse_y = 0;

void int_74_handler(unsigned char m_byte){

	if(m_byte_index == 0 && (m_byte & 0x08) == 0)
		return;

	m_bytes[m_byte_index] = m_byte;
	m_byte_index++;

	if(m_byte_index >= 3){

		m_byte_index = 0;
		
		char x_byte = (signed char)m_bytes[1];
		char y_byte = (signed char)m_bytes[2];

		if(x_byte > 0){
			mouse_x++;
			if(mouse_x >= MAX_X)
				mouse_x = MAX_X - 1;	
		}else if(x_byte < 0){
			mouse_x--;
			if(mouse_x < 0)
				mouse_x = 0;	
		}

		if(y_byte > 0){
			mouse_y++;
			if(mouse_y >= MAX_Y)
				mouse_y = MAX_Y - 1;	
		}else if(y_byte < 0){
			mouse_y--;
			if(mouse_y < 0)
				mouse_y = 0;	
		}

	}
}

void wait_to_write(){
	unsigned int timeout = 10000;

	while(timeout){

		if((_inb(0x64) & 2) == 0)
	      		return;
		timeout--;
	}

}

void wait_to_read(){
	unsigned int timeout = 10000;

	while(timeout){

		if((_inb(0x64) & 1) == 1)
	      		return;
		timeout--;
	}

}

void mouse_write(unsigned char input){

  	wait_to_write(); /*Esperamos hasta que podamos Escribir*/
 
  	_outb(0x64, 0xD4);/*Le indica al mouse que vamos a escribirlo*/
  
  	wait_to_write(); /*Esperamos hasta que podamos Escribir*/
  
  	_outb(0x60, input); /*Escribimos el comando*/
}

unsigned char mouse_read(){

  	wait_to_read(); /*Esperamos hasta poder leer*/

  	return _inb(0x60);
}

void mouse_init(){
	
	disable_vga_cursor();

	wait_to_write();
  	_outb(0x64,0xA8); // Habilita el dispositivo secundario PS/2
  
 	/*Habilitamos la IRQ12*/
  
  	wait_to_write();
  	_outb(0x64,0x20); //Lee el byte 0 de RAM interna y coloca su valor en el registro 0x60
  
  	wait_to_read();
 	unsigned char mouse_flags = _inb(0x60) | 2; // |2 setea el flag Nº 1 en 1, lo que indica que el mouse puede usar la IRQ12
  
 	wait_to_write();
  	_outb(0x64,0x60); //Indicamos que queremos escribir el byte 0 de la ram interna
  
  	wait_to_write();
  	_outb(0x60,mouse_flags);
  
  	mouse_write(0xF6); //Indica al mouse que use las default settings
  	mouse_read();
  
  	mouse_write(0xF4); //Le indica al mouse que envie automaticamente paquetes cuando el mouse se mueve o hay un click
 	
}

void disable_vga_cursor(){

  	char aux;
  	_outb(0x03D4,0x0A);
  	aux = _inb (0x03D5);
  	aux |= 32;
  	_outb(0x03D5,aux);
}