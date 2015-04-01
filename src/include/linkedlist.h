#ifndef _LINKEDLIST
#define _LINKEDLIST

typedef struct node_struct node;

typedef struct node_struct {
	void* data;
	node* next;
} list_node;

typedef struct linkedlist {
	node* head;
	void (*free_data)(void*); //Function that frees the data in node. 
} list;

#endif