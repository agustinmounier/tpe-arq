#include "../include/sh.h"
#include "../include/stdio.h"
#include "../include/lib.h"
#include "../include/stdlib.h"
#include "../include/keyboard_handler.h"
#include "../include/software.h"
#include "../include/exceptions.h"

static char query[SH_BUFFER_SIZE];



static shComand comands[] = {{"clear", clear},
			     {"infoidt", printIDT},
			     {"sounds", sounds},
			     {"biosinfo", print_BIOS_info},
			     {"exception", trigger_excp},
			     {"setfreq", set_freq}
			    };

static char exceptions[3][10] = {"zero", "bounds", "opcode"};

void shell_init(){
	
	int bytesRead = 0;
	char shBuffer[SH_BUFFER_SIZE];
	
	printf("Welcome user!. \n");
	printf("$:");

	while(1){
		
		bytesRead = read(STDIN, shBuffer, SH_BUFFER_SIZE);
		if(shBuffer[0] != '\n')
			parse_shBuffer(shBuffer);
		else if(bytesRead > 0)
			printf("$:");
		
	}
	

}

void parse_shBuffer(char * shBuffer){

	int comandIndex;
	int index = 0;
	char comand[3][15];
	int excp;
	int freq;
	while(shBuffer[index] != '\n'){

		if(index == SH_BUFFER_SIZE)
			return;

		query[index] = shBuffer[index];
		index++;
	}
	query[index] = '\n';
	
	if((comandIndex = getComand(query, comand)) != -1){
		if(comandIndex >= 4){
			excp = validExcp(comand[1]);
			if(excp != -1){
				if(comandIndex == 5){
					freq = atoi(comand[2]);
					if(freq < 20 || freq > 20000){
						printf("The frequency must be between 20 and 20.000 Hz.\n");
						return;
					}
					comands[comandIndex].func(excp, freq);
				}else			
					comands[comandIndex].func(excp + 1);
			}else
				printf("Invalid exception.\n");
		}else
			comands[comandIndex].func();

	}else
		printf("Comand not found.\n");
	

	shBuffer[index] = BUFFER_EMPTY;
	if(comandIndex != 0)
		printf("$:");
	

}

int getComand(char * query, char  comand[3][15]){

	int i = 0;
	int j = 0;
	int h = 0;
	while(query[h] != '\n'){

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

int validExcp(char * excp){

	int i;

	for (i = 0; i < 3; i++){
		if(strcmp(excp, exceptions[i]))
			return i;
	}
	return -1;

}

void shell_display_more(){

	int bytesRead = 0;
	char shBuffer[SH_BUFFER_SIZE];

	printf("Do you wish to display more? [y/n]: ");

	while(1){
		
		bytesRead = read(STDIN, shBuffer, SH_BUFFER_SIZE);
		if(shBuffer[0] != 'y'){
			printf("%c", (char)CLEAR_FUNC);
			break;
		}else if(shBuffer[0] != 'n'){
			printf("%c", (char)CLEAR_FUNC);
			break;
		}else if(bytesRead > 0)
			printf("Invalid character.\n");
		
	}

}

