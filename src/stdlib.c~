#include "../include/stdlib.h"
#include "../include/lib.h"

char * itoa(int value, char * str, int base){
	int digit;	
	int i;	

	if(value == 0){
		str[0] = '0';
		str[1] = '\0';
		return str;
	}
	int index = 0;
	char aux[33];
	if(value < 0 && base == 10){
		aux[index] = '-';
		value *= -1;
		index++;
	}
	do{
		digit = value%base;
		value = value/base;

		if(digit <= 9)
			aux[index] = '0' + digit;
		else
			aux[index] = 'A' + digit;

		index++;	
	}while(value != 0);

	aux[index] = '\0';

	for(i = 0; i < index; i++){
		str[i] = aux[index - i -1];
	}
	str[index] = '\0';
	
	return str;	

}
