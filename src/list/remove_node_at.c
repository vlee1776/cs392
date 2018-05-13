#include "list.h"

void* remove_node_at(struct s_node** head, int n){
	if (head==NULL || *(head)==NULL){
		return NULL;
	}
	void* ret;
	if (n<=0){
		ret=(remove_node(head));
		return ret;
	}
	int i=0;
	s_node* temp= *(head);	
	while (i<n && temp->next!=NULL){
		temp=temp->next;
		i++;
	}
	if (i<n){
		return (remove_last(head));
	}
	if (temp==*head){
		return(remove_node(head));
	}
	ret= remove_node(&temp);
	return ret;
}
