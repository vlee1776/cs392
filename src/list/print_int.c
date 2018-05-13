#include "list.h" 

void print_int(struct s_node *node){
	if (node==NULL){
		return;
	}
	if (node->elem==NULL){
		my_str("NULL");
	}
	else{
		my_int(*(int*)node->elem);
	}	
}
