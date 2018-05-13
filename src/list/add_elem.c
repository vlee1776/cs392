#include "list.h"

void add_elem(void* elem, struct s_node** head)
{
	if (elem==NULL || head==NULL){
		return;
	}
	s_node* temp= new_node(elem, NULL, NULL);
	add_node(temp,head);
}
