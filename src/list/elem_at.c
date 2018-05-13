#include "list.h"

void* elem_at(struct s_node* head, int n){
	if (head==NULL){
		return NULL;
	}
	if (n<0){
		n=0;
	}
	s_node* temp=(node_at(head,n));
	return (temp->elem);
}
