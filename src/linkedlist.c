#include <stdbool.h>
#include "include/linkedlist.h"

node* create_node(void* data) { // create a new list
	node* n = (node*) malloc(sizeof(node));
	n->data = data;
	n->next = NULL;
	return n;
}

list* create_list(void (*free_fnc)(void*)) { // create a new list and pass in function to free data for deletion if needed
	list* lst = (list*) malloc(sizeof(list));
	lst->free_data = free_fnc;
	lst->head = NULL;
	return lst;
}

void list_add(list* lst, node* n) { // add node n to list lst, original is modified because of the pointer, no need to return
	n->next = lst->head;
	lst->head = n;
}

void list_poll(list* lst) { // removes first element and returns "rest" of the list and free data
	if (list_size(lst) > 1) { // list will contain 1 item less
		node* n = lst->head;
		lst->head = n->next;
	} else { // list will be empty after remove
		free(lst->head);
		lst->head = NULL;
	}
}

int list_size(list* lst) { // returns size of the list
	if (lst == NULL) { // list has no nodes
		return 0;
	} else { // list has 1 or more nodes
		node* iterate = lst->head;
		int count = 0;
		while (iterate != NULL) {
			count += 1;
			iterate = iterate->next;
		}
		return count;
	}
}

void list_remove(list* lst, void* data) { // remove first occurence element with particular data, free data
	if(list_contains(lst, data)) {
		node* old = lst->head;
		if (old->data == data) {
			lst->head = old->next;
			free(old->data);
			free(old);
		} else {
			node* iterate = old->next;
			while(iterate != NULL) {
				if (iterate->data == data) {
					node* tmp = iterate;
					old->next = iterate->next;
					free(tmp->data);
					free(tmp);
					break;
				}
				old = iterate;
				iterate = iterate->next;
			}
		}
	}
}

void list_clear(list* lst) { // remove all elements and free data
	while(list_size(lst) > 0) {
		list_poll(lst);
	}
}

bool list_empty(list* lst) { // is list empty?
	if (lst != NULL) {
		if (lst->head != NULL) {
			return false;
		}
	}
	return true;
}

bool list_contains(list* lst, void* data) { // does list contain element?
	if (lst != NULL) {
		node* iterate = lst->head;
		while (iterate != NULL) {
			if (iterate->data == data) {
				return true;
			}
			iterate = iterate->next;
		}
	}
	return false;
}