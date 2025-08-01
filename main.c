#include <stdio.h>
#include "ds/queue.h"
#include "ds/stack.h"
#include "ds/hash_table.h"

void print_int(void* data) {
	printf("%d", *(int*)data);
}


int main(void){	
	queue_t queue;
	int a = 3;
	init_queue(&queue, sizeof(int));
	enqueue(&queue, &a);
	a = 4;
	enqueue(&queue, &a);
	print_queue(&queue, print_int);
	int el;
	dequeue(&queue, &el);
	print_queue(&queue, print_int);
	dequeue(&queue, &el);
	print_queue(&queue, print_int);
	dequeue(&queue, &el);
	print_queue(&queue, print_int);
	
	ds_stack_t stack;
	init_stack(&stack, sizeof(int));
	push(&stack, &a);
	a = 5;
	push(&stack, &a);
	print_stack(&stack, print_int);
	pop(&stack, &el);
	print_stack(&stack, print_int);
	pop(&stack, &el);
	pop(&stack, &el);
	pop(&stack, &el);
	print_stack(&stack, print_int);
	push(&stack, &a);
	print_stack(&stack, print_int);

	ht_t ht;
	ht_create(&ht, 100);
	char *key = "hello";
	char *value = "world";
	char *value2;
	ht_add(&ht, key, value);
	if(ht_find(&ht, key, &value2) == 0){
		printf("value is %s\n", value2);
	};
	ht_delete(&ht, key);
	if(ht_find(&ht, key, &value2) == 0){
		printf("value is %s\n", value2);
	};
	ht_destroy(&ht);
	return 0;
}