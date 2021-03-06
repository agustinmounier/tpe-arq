/*********************************************
kasm.h

************************************************/
#ifndef _kasm_
#define _kasm_

#include "defs.h"

unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void		_mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void		_mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void		_Cli(void);        /* Deshabilita interrupciones  */
void		_Sti(void);	 /* Habilita interrupciones  */

void		_int_08_hand();      /* Timer tick */
void		_int_09_hand();      /* Keyboard */
void		_int_80_hand();
void 		_int_74_hand(); 

void		_int_00_hand();
void            _div_zero_hand();

void		_int_06_hand();
void 		_invalid_opcode();

void		_int_05_hand();
void            _check_bounds(int index, int * bounds);

void            _outb(unsigned short int port, unsigned char value);
void		_sidt(IDTR *);

int		_syscall(int func, int file_desc, int arg1, int arg2);     

void		_debug (void);

#endif

