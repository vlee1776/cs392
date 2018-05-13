#include "my.h"
char *my_strnconcat(char *a, char *b, int n){
	if (a==NULL && b==NULL){
		return NULL;
	}
	if (n<0){
		n=0;	
	}
	int stra= my_strlen(a);
	if (stra==-1){
		stra=0;
	}
	int size=stra+n+1;	
	char* ret=(char*)malloc(size*sizeof(char));
	int i=0;
        if (a!=NULL){
                while (a[i]!='\0'){
                        ret[i]=a[i];
                        i++;
                }
        }
	if (b!=NULL){
		int z=0;
		while (z<n && b[z]!='\0'){
			ret[i]=b[z];
			i++;
			z++;
		}
	}
	ret[i]='\0';
	return ret;
}
