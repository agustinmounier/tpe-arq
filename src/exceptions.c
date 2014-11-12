#include "../include/exceptions.h"
#include "../include/stdio.h"
#include "../include/kasm.h"


void div_by_zero(){

	printf("Exception: Divide-by-zero ocurred.\n");
}

void overflow_ocurr(){

	printf("Exception: Overflow ocurred.\n");
}

void index_out_bounds(){

	printf("Exception: Bound Range Exceeded ocurred.\n");
}

void triger_bound_excep(){

	int index = 12;
	int bounds[] = {0, 10};
	
	_check_bounds(index, bounds);

}


