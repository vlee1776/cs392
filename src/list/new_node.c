#include "list.h"

struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous){
	s_node* ret=(s_node*)malloc(sizeof(struct s_node));
	ret->elem=elem;
	ret->next= next;
	ret->prev= previous;
	return ret;
}
