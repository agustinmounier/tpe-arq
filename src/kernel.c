#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/timertick_handler.h"
#include "../include/terminal.h"
#include "../include/sh.h"
#include "../include/stdio.h"

DESCR_INT idt[0x100];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/

kmain() 
{

        int i,num;

/* Borra la pantalla. */ 

	k_clear_screen();

/* Inicializa la terminal */

	terminal_init();

/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

        setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);
	
/* Carga de IDTR    */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

/* Habilito interrupciones */
	_Cli();	

        _mascaraPIC1(0xF0);
        _mascaraPIC2(0xFF);
        
	_Sti();

        shell_init((int) &idt[0x09]);
	
}

