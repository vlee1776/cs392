#include "list.h"

void empty_list(struct s_node** head){
	if (head==NULL || *(head)==NULL){
		return;
	}
	while (*(head)!=NULL){
		remove_node(head);
	}
//	head=NULL;
}
