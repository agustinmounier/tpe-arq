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
			printf("Descripcion de la gate %x h.\n", idtIndex/8);
			printINTinfo((DESCR_INT *)(idtr.base + idtIndex));
			printf("\n");
		}
	}		
	
	
		
}

void printINTinfo(DESCR_INT * inter){

	printf("offset_low = %d\n", inter->offset_l);
	printf("offset_high = %d\n", inter->offset_h);
	printf("code segment selector = %d\n", inter->selector);
	printf("zero = %d\n", inter->cero);
	printf("access = %b\n", inter->access);
	

}
