#include "my.h" 
/*
I pledge my honor that I have abided by the Stevens Honor System. -Vincent Lee
*/
int my_strlen(char* str){
	//null condition
	if (str==NULL){
		return -1;
	}
	int i=0;
	//empty string will print 0
	while (str[i]!= '\0'){
		i++;
	}
	return i;
}
