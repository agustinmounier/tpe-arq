

/* scans from address 0xF0000 to 0xFFFFF in order to find the _SM_ string */
/* getSMBIOS is based on an example code from  http://wiki.osdev.org/System_Management_BIOS */
int getSMBIOS(char * SMBIOS){
	
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
				SMBIOS = SM_dir;
				return 1;
			}
		}
	}
	
	if ((unsigned int) SM_dir == 0xFFFFF) {
        	printf("No SMBIOS found!");
		return 0;
    	}
}
