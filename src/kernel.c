#include "../include/kasm.h"
#include "../include/kc.h"
#include "../include/defs.h"
#include "../include/timertick_handler.h"
#include "../include/terminal.h"
#include "../include/mouse_handler.h"
#include "../include/video_handler.h"
#include "../include/stdio.h"

DESCR_INT idt[0x100];			/* IDT de 256 entradas*/
IDTR idtr;				/* IDTR */

/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{

        int i,num;

	terminal_init();
	video_init();
	mouse_init();
	

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

	setup_IDT_entry (&idt[0x00], 0x08, (dword)&_int_00_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x06], 0x08, (dword)&_int_06_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x05], 0x08, (dword)&_int_05_hand, ACS_INT, 0);

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x74], 0x08, (dword)&_int_74_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

/* Habilito interrupciones */
	_Cli();	

        _mascaraPIC1(0xF8); // Vector offset 0x08. Unmasked IRQs: 0, 1, 2.
        _mascaraPIC2(0xEF); // Vector offset 0x70. Unmasked IRQ: 12.
        
	_Sti();

        shell_init();

}

int get_idt(IDTR * idtr){

	_sidt(idtr);
	return 1;
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}



/* scans from address 0xF0000 to 0xFFFFF in order to find the _SM_ string */
/* getSMBIOS is based on an example code from  http://wiki.osdev.org/System_Management_BIOS */

int getSMBIOS(char ** SMBIOS){
	
	char * SM_dir = (unsigned char *) 0xF0000;
	int i, cant;
	unsigned char sum;
	for(;(unsigned int)SM_dir <= 0xFFFFF; SM_dir += 16){
		if(SM_dir[0] == '_' && SM_dir[1] == 'S' && SM_dir[2] == 'M' && SM_dir[3] == '_'){
			cant = SM_dir[5];
			sum = 0;
			for(i = 0; i < cant; i++)
				sum += SM_dir[i];

			if(sum == 0){
				*SMBIOS = SM_dir;
				return 1;
			}
		}
	}
	
	if ((unsigned int) SM_dir == 0xFFFFF) {
        	printf("No SMBIOS found!");
		return 0;
    	}
}

void wait(int ms){
	
	int end = getTicks() + (ms/55);
	_Sti();
	while (getTicks() < end){};
	_Cli();

}

