#include "my.h"

char *my_vect2str(char **x){
	int i=0;
	int len=0;
	if (x==NULL){
		return NULL;
	}
	char *ret=(char*)malloc(200*sizeof(char));
	while (x[i]!=NULL){
		int pos=0;
		while (x[i][pos]!='\0'){
			ret[len]=x[i][pos];
			pos++;
			len++;
		}
		i++;
		if (x[i]!=NULL){	
			ret[len]=' ';
			len++;
		}
	}
	return ret;
}
