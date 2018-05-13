#include "list.h"

struct s_node* node_at(struct s_node* head, int n){
	if (head==NULL){
		return NULL;
	}
	s_node* temp= head;
	if (n<=0){
		return head;
	}
	int i=0;
	while (i<n && temp->next!=NULL){
		temp=temp->next;
		i++;
	}
	return temp;
}
