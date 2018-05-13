#include "my.h"

char* my_strrfind(char* str, char find){
	int ret= my_strrindex(str,find);
	if (ret==-1){
		return NULL;
	}
	return &(str[ret]);
}
