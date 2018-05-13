#include <unistd.h>
#include <stdio.h>

void* arr[100];
int ctr=0;
/*
struct node;
typedef struct node* Node;
struct node{
	void* elem;
	Node next;
};
Node head=NULL;
typedef struct node node;	*/
void my_free(void* pos){
	int i=0;
	
	//printf ("%p",pos);
	while (arr[i]!=pos && i<ctr){
		i++;
	}	
	if (arr[i]==pos){
	//	printf ("HERE\n");
		*(char**)pos=NULL;
	}
}

void* my_malloc(int x){
	void* add= sbrk(3);
	arr[ctr]=add;
	ctr++;
	return add;
}

int main(){
	char* str= my_malloc(3);
	str[0]='h';
	str[1]='i';
	str[2]='\0';
	printf ("%s\n",str);
	str[3]='q';
	my_free(str);
	printf ("%s\n",str);
}
