#include "list.h"
#include <stdio.h>
int main(){
	int x=1;
	int y=2;
	int z=3;
	int a=7;
	int b=12;
	int c=8;
	s_node* last=new_node( &x, NULL,NULL);
	s_node* first=new_node(&y,NULL,NULL);
	s_node* B=new_node(&c, first,last);
	s_node* next= new_node( &z, NULL,NULL);
	s_node* A=new_node(&b, next,next);
	s_node* temp=NULL;
	s_node** head=&last;
	append(first, head);
	append(B, head);
	append(next, head);
	/*add_elem(&y,head);
	add_node(last,head);
	add_node(next,head);
	append(A, head);
	add_elem(&a,head);
	add_node_at(B, head, 1);*/
	remove_node_at(head,-200);
	remove_node_at(head,200);
	remove_node_at(head,200);
	remove_node(head);
	debug_int(*head);
	
	/*remove_node(&A);
	remove_node_at(head,4);
	my_str("\n size of list is: ");
	my_int(count_s_nodes(*head));
	my_str("\n");
	my_str("int at index 5:");
	my_int(*(int*)elem_at(*head,7));
	my_str("\n");
	my_str("print_int at node index");
	print_int(node_at(*head,-10));
	my_str("\n");
	traverse_int(*head);
	my_str("\n");
	my_int(*(int*)remove_last(head));
	my_str("\n");
	my_int(*(int*)remove_last(head));
	my_str("\n");	
	my_int(*(int*)remove_last(head));
	//remove_last(NULL);
	my_str("\n");
	debug_int(*head);
	my_str("\n");	
	my_str("size of list is: ");
	my_int(count_s_nodes(*head));
	my_char('\n');
	//empty_list(head);
	//remove_node_at(head,420);
	remove_node_at(head,420);
	debug_int(*head);
	my_str("\n");
	my_str("size of list is: ");
	my_int(count_s_nodes(*head));
	my_str("\n \n \n");

	char d='D';
	char e='E';
	s_node** list2;
	s_node* D=new_node(&d,NULL,NULL);
	s_node* E=new_node(&e,NULL,NULL);
	list2= &D;
	add_node(E,list2);
	debug_char(*list2);
	my_str("\n");
	traverse_char(*list2);
	my_str("\n");
	print_char(node_at(*list2,-10));
	my_str("\n");
	*/	
	char* f="HELLO";
	char* g="HI";
	printf(g);
	s_node** list3;
	s_node* F=new_node(f, NULL, NULL);
	s_node* G= new_node(g, NULL,NULL);
	list3= &F;
	add_node(G,list3);
	debug_string(*list3);
	my_str("\n");
	traverse_string(*list3);
	my_str("\n");
	print_string(node_at(*list3,-10));
	my_str("\n");	

	void* h=NULL;
	s_node** n;
	s_node* q= new_node (h,NULL,NULL);
	*n= q;
	remove_node(n);	
}

