#include <stdio.h>
#include "ds/queue.h"
#include "ds/stack.h"

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
	return 0;
}