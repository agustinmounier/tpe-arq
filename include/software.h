#ifndef _software_
#define _software_

#define CLEAR_FUNC -10
#define INFO_IDT -11
#include "defs.h"

void clear();
void printIDT();
void printINTinfo(DESCR_INT * inter);
void sounds();
void print_BIOS_info();

#endif
