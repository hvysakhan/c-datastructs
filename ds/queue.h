#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	size_t data_bytes;
	int num_elements;
	int max_elements;
	element_t *head;
	element_t *tail;
}queue_t;

int print_queue(queue_t* queue, void (*print_fn)(void*));
int init_queue(queue_t* queue, size_t bytes, int max_elements); // -1 for no max element
int deinit_queue(queue_t* queue);
int enqueue(queue_t* queue, void* data);
int dequeue(queue_t* queue, void* element);

#ifdef __cplusplus
}
#endif

#endif