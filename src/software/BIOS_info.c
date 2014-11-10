#include "../../include/software.h"
#include "../../include/defs.h"


/* scans from address 0xF0000 to 0xFFFFF in order to find de _SM_ string*/

char * getSMBIOS(){
	
	char * SM_dir = (unsigned char *) 0xF0000;
	int i, sum, cant;
	for(;(unsigned int)SM_dir <= 0xFFFFF; SM_dir += 16){
		if(SM_dir[0] == '_' && SM_dir[1] == 'S' && SM_dir[2] == 'M' && SM_dir[3] == '_'){
			cant = SM_dir[5];
			sum = 0;
			for(i = 0; i < cant; i++)
				sum += SM_dir[i];

			if(sum == 0)
				return SM_dir;
		}
	}
}

void print_BIOS_info(){

	char * SMBIOS = getSMBIOS();

	printf("%d", ((SMBIOSEntryPoint *)SMBIOS)->TableAddress);

}
