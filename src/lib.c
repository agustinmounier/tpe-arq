#include "../include/lib.h"

int
strlen(const char *s)
{
    int i = 0;
    while (*s++ != '\0')
    {
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
