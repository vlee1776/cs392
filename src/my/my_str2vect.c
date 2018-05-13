#include "my.h"

int words(char* input){
	int ret=0;
	int ctr=0;
	while (input[ctr]!='\0'){
		if (input[ctr]==' ' || input[ctr]=='\t' || input[ctr]=='\n'){
			while (input[ctr]==' ' || input[ctr]=='\t' || input[ctr]=='\n'){
				ctr++;
			} 
		}
		else{
			while (input[ctr]!=' ' && input[ctr]!='\t' && input[ctr]!= '\n' && input[ctr]!='\0'){
				ctr++;
			}
			ret++;
		}
	}
	return ret;		
}

char ** my_str2vect(char* input){
	if (input==NULL){
		return NULL;
	}
	int len=words(input);
	len++;
	char** ret=(char**)malloc(len*sizeof(char*));
	len--;
	int maxlen=my_strlen(input);
	int ctr=0;
	int x=0;

	while (input[ctr]!='\0'){
		if (input[ctr]==' ' || input[ctr]=='\t' || input[ctr]=='\n'){
			while (input[ctr]==' ' || input[ctr]=='\t' || input[ctr]=='\n'){
				ctr++;
				maxlen--;
			} 
		}
		else{
			char* add=(char*)malloc(maxlen*sizeof(char));
			//added for loop in
			for (int i=0; i<maxlen; i++){
				add[i]=' ';
			}
			int pos=0;
			while (input[ctr]!=' ' && input[ctr]!='\t' && input[ctr]!= '\n' && input[ctr]!='\0'){
				add[pos]=input[ctr];
				ctr++;
				pos++;
				maxlen--;
			}
			add[pos]='\0';
			ret[x]=add;
			x++;	
		}
	}
	ret[x]=NULL;
	return ret;
}
