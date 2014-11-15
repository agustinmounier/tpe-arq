#include "../../include/software.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/kasm.h"

void printIDT(){
	
	IDTR idtr;

	_syscall(INFO_IDT, 0, (int)&idtr,0);
	
	int idtIndex = 0;
	for (; idtIndex < idtr.limit; idtIndex+=8){
		if((byte)(((DESCR_INT *)(idtr.base + idtIndex))->selector) == (byte)0x08){
			printf("Description of gate 0x%x.\n", idtIndex/8);
			printINTinfo((DESCR_INT *)(idtr.base + idtIndex));
		}
	}				
}

void printINTinfo(DESCR_INT * inter){

	printf("offset = 0x%x0%x ", inter->offset_h, inter->offset_l);
	printf("segment selector = 0x%x ", inter->selector);
	printf("zero = %d ", inter->cero);
	printf("access = %b.\n", inter->access);
	
}
