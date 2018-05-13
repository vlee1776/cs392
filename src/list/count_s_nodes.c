#include "list.h"

int count_s_nodes(struct s_node* head){
	if (head==NULL){
		return 0;
	}
	s_node* temp=head;
	int ctr=0;
	while (temp!=NULL){
		ctr++;
		temp=temp->next;
	}
	return ctr;
}
