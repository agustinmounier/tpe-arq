#include "../include/stdlib.h"


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
			aux[index] = 'A' + (digit-10);

		index++;	
	}while(value != 0);

	aux[index] = '\0';

	for(i = 0; i < index; i++){
		str[i] = aux[index - i -1];
	}
	str[index] = '\0';
	
	return str;	

}

int atoi(char * num){
	
	int i = 0;
	int resp = 0;
	int curr = 0;
	int isNeg = 0;
	int length = strlen(num) - 1;

	if(num[0] == '-'){
		isNeg = 1;
		i++;
		length--;
	}
	
	while(num[i] != '\0'){
		
		curr = (int)num[i] - '0';

		if(curr < 0 || curr > 9)
			return resp;

		curr *= pow(10, length);
		length--;
		resp += curr;
		i++;

	}
	if(isNeg)
		return resp*(-1);
	return resp;

}

int pow(int n, int pot){
	if(pot == 0)
		return 1;
	return n*pow(n, pot -1);
}

int strlen(const char * str){
    int i = 0;
    while (str[i] != '\0'){
        i++;
    }
    return i;
}

int strcmp(char * str1, char * str2){
	
	int index = 0;
	while(str1[index] != '\0'){
		if(str1[index] != str2[index])
			return 0;
		index++;
	}
	if(str2[index] == '\0')
		return 1;
	else
		return 0;

}





