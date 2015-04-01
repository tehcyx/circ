#ifndef _LINKEDLIST
#define _LINKEDLIST

typedef struct node_struct node;

typedef struct node_struct {
	void* data;
	node* next;
} list_node;

typedef struct linkedlist {
	node* head;
	void (*free_data)(void*); // pass in a function to free the node's data
} list;

#endif