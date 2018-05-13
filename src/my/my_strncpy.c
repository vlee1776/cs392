#include "my.h"
char* my_strncpy(char *dst, char *src, int n){
	if (n<0){
		n=0;
	}
	if ((dst==NULL && src==NULL) || dst==NULL){
		return NULL;
	}
	if (src==NULL){
		return dst;
	}
	//int len=my_strlen(src);
	int i=0;
	while (i<n && src[i]!='\0'){
		dst[i]=src[i];
		i++;
	}
	dst[i]='\0';
	return dst;
}
