#include "my.h"

char *my_strdup(char *str){
	if (str==NULL){
		return NULL;
	}
	char* ret;
	int size=my_strlen(str)+1;
	ret=(char*)malloc(size*sizeof(char));
	int i=0;
	while (str[i]!='\0'){
		ret[i]=str[i];
		i++;
	}
	ret[i]='\0';
	return ret;
}
