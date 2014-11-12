#include "../include/sh.h"
#include "../include/stdio.h"
#include "../include/lib.h"
#include "../include/keyboard_handler.h"
#include "../include/software.h"
#include "../include/kasm.h" /*TODO: sacar */
#include "../include/exceptions.h"

static char query[SH_BUFFER_SIZE];
static char comand[10];


static shComand comands[] = {{"clear", clear},
			     {"infoidt", printIDT},
			     {"sounds", sounds},
			     {"biosinfo", print_BIOS_info}
			    };

void shell_init(){
	
	int bytesRed = 0;
	char shBuffer[SH_BUFFER_SIZE];
	
	printf("Welcome user!. \n");


	while(1){
		
		bytesRed = read(STDIN, shBuffer, SH_BUFFER_SIZE);
		if(shBuffer[0] != ASCII_ENTER)
			parse_shBuffer(shBuffer);
		
	}
	

}

void parse_shBuffer(char * shBuffer){
	
	/* TODO: parsear parametros de funcs */

	
	int index = 0;
	while(shBuffer[index] != ASCII_ENTER){

		if(index == SH_BUFFER_SIZE)
			return;

		query[index] = shBuffer[index];
		index++;
	}
	query[index] = ASCII_ENTER;
	
	/* TODO: parse de comands */
	
	if(getComand(query, comand) != 1)
		printf("Comand not found.\n");
	

	shBuffer[index] = BUFFER_EMPTY;
		

	

}

int getComand(char * query, char * comand){

	int i = 0;
	int comandIndex;

	while(query[i] != ' ' && query[i] != ASCII_ENTER){
		comand[i] = query[i];	
		i++;
	}

	comand[i] = '\0';
	
	if((comandIndex = isComand(comand)) != -1){
		/*_div_zero();*/
		comands[comandIndex].func();
		/*triger_bound_excep();*/
		/*_overflow();*/
	}else
		return 0;

	return 1;
	
	
}

int isComand(char * comand){

	int i;

	for (i = 0; i < CANT_COMANDS; i++){
		if(strcmp(comand, comands[i].name))
			return i;
	}

	return -1;

}




