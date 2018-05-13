#include "my.h" 

char* my_strcpy(char *dst, char* src){
	if ((dst==NULL && src==NULL) || dst==NULL){
		return NULL;
	}
	if (src==NULL){
		return dst;
	}
	int i=0;
	while (src[i]!='\0'){
		dst[i]=src[i];
		i++;
	}
	dst[i]='\0';
	return dst;
}
