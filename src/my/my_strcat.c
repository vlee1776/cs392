#include "my.h"
char *my_strcat(char *dst, char *src){
	if (src==NULL && dst==NULL){
		return NULL;
	}
	if (dst==NULL || src==NULL){
		return dst;
	}
	int len=my_strlen(src);
	int end=my_strlen(dst);
	for (int i=0; i<len; i++){
		dst[end]=src[i];
		end++;
	}
	dst[end]='\0';
	return dst;
}
