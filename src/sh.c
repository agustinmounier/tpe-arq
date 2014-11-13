#include "../include/sh.h"
#include "../include/stdio.h"
#include "../include/lib.h"
#include "../include/keyboard_handler.h"
#include "../include/software.h"
#include "../include/kasm.h" /*TODO: sacar */
#include "../include/exceptions.h"

static char query[SH_BUFFER_SIZE];



static shComand comands[] = {{"clear", clear},
			     {"infoidt", printIDT},
			     {"sounds", sounds},
			     {"biosinfo", print_BIOS_info},
			     {"exception", trigger_excp}
			    };

void shell_init(){
	
	int bytesRead = 0;
	char shBuffer[SH_BUFFER_SIZE];
	
	printf("Welcome user!. \n");


	while(1){
		
		bytesRead = read(STDIN, shBuffer, SH_BUFFER_SIZE);
		if(shBuffer[0] != ASCII_ENTER && shBuffer[0] != BUFFER_EMPTY)
			parse_shBuffer(shBuffer);
		
	}
	

}

void parse_shBuffer(char * shBuffer){
	
	/* TODO: parsear parametros de funcs */

	int comandIndex;
	int index = 0;
	char comand[3][15];
	while(shBuffer[index] != ASCII_ENTER){

		if(index == SH_BUFFER_SIZE)
			return;

		query[index] = shBuffer[index];
		index++;
	}
	query[index] = ASCII_ENTER;
	
	/* TODO: parse de comands */
	
	if((comandIndex = getComand(query, comand)) != -1){
		
		if(comandIndex == 4){
			printf("%s.\n", comand[0]);
			printf("%s.\n", comand[1]);			
			comands[comandIndex].func((int)comand[1][0] - '0');
		}else
			comands[comandIndex].func();
		/*triger_bound_excep();*/
		/*_overflow();*/
	}else
		printf("Comand not found.\n");
	

	shBuffer[index] = BUFFER_EMPTY;
	
	

}

int getComand(char * query, char  comand[3][15]){

	int i = 0;
	int j = 0;
	int h = 0;
	while(query[h] != ASCII_ENTER){

		if(query[h] == ' '){
			comand[i][j] = '\0';
			i++;
			j = 0;
		}else{
			comand[i][j] = query[h];
			j++;
		}

		if(i > 3)
			return -1;
	
		h++;
	}
	comand[i][j] = '\0';
	
	return isComand(comand[0]);

	
	
}

int isComand(char * comand){

	int i;

	for (i = 0; i < CANT_COMANDS; i++){
		if(strcmp(comand, comands[i].name))
			return i;
	}

	return -1;

}




