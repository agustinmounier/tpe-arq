#include "../../include/software.h"
#include "../../include/defs.h"
#include "../../include/stdlib.h"
#include "../../include/syscall_hand.h"


void print_BIOS_info(){

	char * SMBIOS;

	_syscall(GET_SMBIOS, 0, (unsigned int)&SMBIOS, 0);

	SMBIOSEntryPoint * entry;
	SMBIOSHeader * header;

	entry = (SMBIOSEntryPoint *)SMBIOS;
	header = (SMBIOSHeader *)(entry->TableAddress);
	
	if(header->Type == 0){ // BIOS information
	
		int sm_strings = (entry->TableAddress + header->Length);
		char * bios_brand = (char *)sm_strings;
		char * bios_version = (char *)(strlen(bios_brand) + sm_strings + 1);
		char * bios_date = (char *)(strlen(bios_version) + (int)bios_version + 1);

		printf("BIOS information.\n");
		printf("BIOS brand: %s.\n", bios_brand);
		printf("BIOS version: %s.\n", bios_version);
		printf("BIOS date: %s.\n", bios_date);

	}
}
