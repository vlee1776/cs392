#include <stdio.h>

int main(){
	int a=10;
	char c= 'X';
	char array[4];
	char array2[]= {'X', 'Y', 'Z'};
	
	printf ("please enter:\n");

	scanf ("%s", array);

	printf ("addr of array2[1] is %p\n", &array2[1]);

	if (c=='Y'){
		printf("Welcome to overflow\n");
	}
		else{
			printf("something");
		}
		return 0;
}
