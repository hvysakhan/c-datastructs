#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>

typedef struct element{
	void* data;
	struct element *nxt_element;
}element_t;

typedef struct{
	size_t data_bytes;
	int num_elements;
	element_t *head;
	element_t *tail;
}queue_t;

int print_queue(queue_t* queue, void (*print_fn)(void*));
int init_queue(queue_t* queue, size_t bytes);
int deinit_queue(queue_t* queue);
int enqueue(queue_t* queue, void* data);
int dequeue(queue_t* queue, void* element);

#endif