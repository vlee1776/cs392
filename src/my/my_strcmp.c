#include "my.h"

int my_strcmp( char *a, char *b){
	if (a==NULL && b==NULL){
		return 0;
	}
	if (a==NULL){
		return -1;
	}
	if (b==NULL){
		return 1;
	}
	int i=0;
	while (a[i]!='\0' && b[i]!='\0'){
		int dif= (int)a[i]-(int)b[i];
		if (dif!=0){
			return dif;
		}
	i++;
	}
	return (int)a[i]-(int)b[i];
}
