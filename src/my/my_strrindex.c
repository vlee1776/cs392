#include "my.h"
/*
I pledge my honor that I have abided by the Stevens Honor System -Vincent Lee
*/
int my_strrindex(char* str, char l){
	int i=0;
	int ret=-1;
	if (str!=NULL){
	//keep track of last position of target
		while (str[i]!='\0'){
			if (str[i]==l){
				ret=i;
			}
		i++;
		}
	}
	return ret;
}
