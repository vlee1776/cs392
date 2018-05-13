#ifndef _MYLIST_H_
#define _MYLIST_H_

#include "my.h"

/*
 What to create
 ~~~~/src/list/ *.c
 ~~~~/include/mylist.h
 ~~~~/lib/liblist.a
 ~~~~/test/testlist.c
*/

struct s_node {
 void* elem;
 struct s_node* next;
 struct s_node* prev;
};

typedef struct s_node s_node;
/*
 Allocates and returns a new node with the given pointers. You may
 create nodes with NULLs.
*/
struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous);

/*
 Inserts a node at the start of the list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 DOES NOT PARSE
*/
void add_node(struct s_node* node, struct s_node** head);

/* 
 Creates a new node with elem and adds it to head. DO NOT add a NULL 
 elem.
 DOES NOT PARSE
*/
void add_elem(void* elem, struct s_node** head);

/*
 Adds a node to the end of a list. DO NOT add a NULL pointer or
 a node with a NULL elem.
 Parse once
*/
void append(struct s_node* node, struct s_node** head);

/*
 Adds a node at index n of a list or at the end of the list if n is 
 too large.
 Parse once
*/
void add_node_at(struct s_node* node, struct s_node** head, int n);

/* 
 Removes the given node from the list. Returns elem and frees the 
 node from memory.
 DOES NOT PARSE.
*/
void* remove_node(struct s_node** node);

/*
 Removes the last node from the list.
 Parse Once.
*/
void* remove_last(struct s_node**);

/*
 Removes the node at index n or the last node.
 Parse once
*/
void* remove_node_at(struct s_node** head, int n);

/*
 Returns the value the length of the list
 Parse Once.
*/
int count_s_nodes(struct s_node* head);

/*
 Frees all the nodes in the list.
 CHALLENGE: Write in two lines (allowed to use other methods in 
 this assignment)
*/
void empty_list(struct s_node** head);

/*
 Returns a pointer to the node at index n or the last node.
 Parse once
*/
struct s_node* node_at(struct s_node* head, int n);

/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
*/
void* elem_at(struct s_node* head, int n);

/*
 Prints all the elems as ints separated by a space
*/
void traverse_int(struct s_node* head);

/*
 Prints all the elems as chars separated by a space
*/
void traverse_char(struct s_node* head);

/*
 Prints all the elems as strings separated by a space
*/
void traverse_string(struct s_node* head);

/*
 Prints all the elems as ints separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_int(struct s_node* head);

/*
 Prints all the elems as chars separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_char(struct s_node* head);
/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL) 
*/
void debug_string(struct s_node* head);

/*
 Prints the elem of node as a in
*/
void print_int(struct s_node* node);

/*
 Prints the elem of node as a char
*/
void print_char(struct s_node* node);

/*
 Prints the elem of node as a string
*/
void print_string(struct s_node* node);

#endif
