#include <stdio.h>
#include "queue/queue.h"

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
	
	return 0;
}