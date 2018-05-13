#include "my.h"
/*
I pledge my honor that I have abided by the Stevens Honor System. -Vincent Lee
*/
void my_str(char* str){
	if (str==NULL){
		return;
	}
	//print the first letter first
	else{
		int i=0;
		while(str[i]!='\0'){
			my_char(str[i]);
			i++;
		}
	}
}
