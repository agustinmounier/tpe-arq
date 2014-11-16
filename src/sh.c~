#include "../include/sh.h"
#include "../include/stdio.h"
#include "../include/stdlib.h"
#include "../include/keyboard_handler.h"
#include "../include/software.h"
#include "../include/exceptions.h"

static char query[SH_BUFFER_SIZE];



static shComand comands[] = {{"clear", clear},
			     {"help", help},
			     {"infoidt", printIDT},
			     {"sounds", sounds},
			     {"biosinfo", print_BIOS_info},
			     {"exception", trigger_excp},
			     {"setfreq", set_freq}
			    };

static char exceptions[3][10] = {"zero", "bounds", "opcode"};

void shell_init(){
	

	char shBuffer[SH_BUFFER_SIZE];
	
	printf("Welcome user!. \n");
	printf("$:");

	while(1){
		
		read(STDIN, shBuffer, SH_BUFFER_SIZE - 1);
		
		if(shBuffer[0] != '\n')
			parse_shBuffer(shBuffer);
		else{
			printf("$:");
			shBuffer[0] = BUFFER_EMPTY;
		}
		
	}
	

}

void parse_shBuffer(char * shBuffer){

	int comandIndex;
	int index = 0;
	char comand[3][15];
	int excp;
	int freq;
	while(shBuffer[index] != '\n'){

		if(shBuffer[index] == '\0' || shBuffer[index] == BUFFER_EMPTY)
			return;
		
		index++;
	}

	if((comandIndex = getComand(shBuffer, comand)) != -1){
		if(comandIndex >= 5){
			excp = validExcp(comand[1]);
			if(excp != -1){
				if(comandIndex == 6){
					freq = atoi(comand[2]);
					if(freq < 20 || freq > 20000)
						printf("The frequency must be between 20 and 20.000 Hz.\n");
					else
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

		if(i > 2 || j > 14)
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
void help(){

	printf("COMAND                                DESCRIPTION\n");
	printf("infoidt                               Shows the content of the IDT.\n");

	printf("biosinfo                              Shows information about\n");
	printf("                                      the BIOS.\n");

	printf("sounds                                Emits different sounds\n");
	printf("                                      through the PC speaker.\n");

	printf("exception [exception-name]            Triggers exception-name.\n");

	printf("setfreq [exception-name] [freq]       Sets the frequency of the\n");
	printf("                                      sound emited by exception-name to freq.\n");
	printf("Available exception-names: zero, bounds, opcode.\n");



}

