#include "my.h"

char *my_strconcat(char *a, char *b){
	if (a==NULL && b==NULL){
		return NULL;
	}
	int stra=my_strlen(a);
	int strb= my_strlen(b);
	if (strb==-1){
		strb=0;
	}
	if (stra==-1){
		stra=0;
	}
	/*
	if (a==NULL){
		return NULL;
	}*/
	int size=stra+strb+1;
	char* ret=(char*)malloc(size*sizeof(char));
	int i=0;
	if (a!=NULL){
        	while (a[i]!='\0'){
                	ret[i]=a[i];
                	i++;
        	}
	}
	if (b!=NULL){	
		int len=my_strlen(b);
        	for (int z=0; z<len; z++){
               	 	ret[i]=b[z];
                	i++;
        	}
	}
	ret[i]='\0';
	return ret;
}
