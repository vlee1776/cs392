#include "my.h"
/*
I pldege my honor that I have abided by the Stevens Honor System -Vincent Lee
*/
int my_strindex(char* str ,char l){
	int i=0;
	//check till terminator and return first instance
	if (str!=NULL){
		while (str[i]!='\0'){
			if (str[i]==l){
				return i;
			}
		i++;
		}
	}
	return -1;
	
}
