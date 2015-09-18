#include <stdio.h>
#include <stdlib.h>
#include <linkedlist.h>

void free_nothing () {
	// do nothing;
}

typedef struct values_struct {
	int v;
} values;

int main(int argc, char **argv) {
	list* lst = list_create( (void(*)(void*))free_nothing ); //function pointer

	if (list_empty(lst)) {
		printf("List is empty %s\n", "");
	} else {
		printf("List is NOT empty %s\n", "");
	}

	short i = 5;

	node* n = create_node(i);

	list_add(lst, n);

	if (list_empty(lst)) {
		printf("List is empty %s\n", "");
	} else {
		printf("List is NOT empty %s\n", "");
	}

	int number = 5;

	if (list_contains(lst, number)) {
		printf("List contains %i\n", number);
	} else {
		printf("List does not contain %i\n", number);
	}

	number = 8;

	if (list_contains(lst, number)) {
		printf("List contains %i\n", number);
	} else {
		printf("List does not contain %i\n", number);
	}

	list_poll(lst);

	if (list_empty(lst)) {
		printf("List is empty %s\n", "");
	} else {
		printf("List is NOT empty %s\n", "");
	}

	values* val1 = (values*) malloc(sizeof(values));
	values* val2 = (values*) malloc(sizeof(values));
	values* val3 = (values*) malloc(sizeof(values));

	val1->v = 20;
	val2->v = 40;
	val3->v = 60;
	node* m = create_node(val1);
	node* o = create_node(val2);
	node* p = create_node(val3);

	list_add(lst, m);
	list_add(lst, o);
	list_add(lst, p);

	printf("The list has %i elements\n", list_size(lst));

	list_remove(lst, val2);

	printf("The list has %i elements\n", list_size(lst));

	if (list_contains(lst, val1)) {
		printf("List contains %i\n", val1->v);
	} else {
		printf("List does not contain %i\n", val1->v);
	}
	if (list_contains(lst, val3)) {
		printf("List contains %i\n", val3->v);
	} else {
		printf("List does not contain %i\n", val3->v);
	}

	list_clear(lst);

	printf("The list has %i elements\n", list_size(lst));

	return 0; // ANSI C requires main to return int.
}