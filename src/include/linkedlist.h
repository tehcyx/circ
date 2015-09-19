#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct node_struct node; // make node available for use within node_struct

struct node_struct {
	void* data;
	node* next;
};

typedef struct linkedlist {
	node* head;
	void (*free_data)(void*); // pass in a function to free the node's data
} list;

node* create_node(void* data); // create a new list

list* list_create(void (*free_fnc)(void*)); // create a new list and pass in function to free data for deletion

void list_add(list* lst, node* n); // add node n to list lst and return new head

void list_poll(list* lst); // removes first element and returns "rest" of the list and free data

int list_size(list* lst); // returns size of the list

void list_remove(list* lst, void* data); // remove element that particular data, free data

void list_clear(list* lst); // remove all elements and free data

bool list_empty(list* lst); // is list empty?

bool list_contains(list* lst, void* data); // does list contain element?

#endif