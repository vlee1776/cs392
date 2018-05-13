#include "list.h"

void* remove_last(struct s_node** head){
	if (head==NULL || *head==NULL){
		return NULL;
	}
	s_node* temp= *(head);
	if (temp->next==NULL){
		void* ret=remove_node(head);
		return ret;
	}
	while (temp->next!=NULL){
		temp=temp->next;
	}
	return(remove_node(&temp));
}
