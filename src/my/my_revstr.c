#include "my.h"
/*
I pledge my honor that I have abided by the Stevens Honor System. -Vincent Lee
*/
// this is only possible for inputs of mutable strings
int my_revstr(char* str){ 
	int size= my_strlen(str);
	int len= size-1;
	int start=0;
	//have start and end meet in the middle
	while (start<len){
		char temp=str[len];
		str[len]= str[start];
		str[start]=temp;
		start++;
		len--;
	} 
	return size;
}
