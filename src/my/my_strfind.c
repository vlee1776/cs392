#include "my.h" 

char* my_strfind(char* str, char find){
	int ret= my_strindex(str,find);
	if (ret==-1){
		return NULL;
	}
	return &(str[ret]);
}
