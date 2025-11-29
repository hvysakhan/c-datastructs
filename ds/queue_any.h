#ifndef QUEUE_ANY_H
#define QUEUE_ANY_H
#include <pthread.h>
#include <stddef.h>
#include "common.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	int num_elements;
	int max_elements;
	sized_element_t *head;
	sized_element_t *tail;
	pthread_cond_t is_empty_cond;
	pthread_mutex_t queue_lock;
	bool is_empty;
}queue_any_t;

int print_queue_any(queue_any_t* queue_any, void (*print_fn)(void*));
int init_queue_any(queue_any_t* queue_any, int max_elements); // -1 for no max element
int deinit_queue_any(queue_any_t* queue_any);
int enqueue_any(queue_any_t* queue_any, void* data, size_t data_bytes);
int dequeue_any(queue_any_t* queue_any, void* element);
int return_size_before_dequeue(queue_any_t* queue);
int return_size_before_dequeue_wait(queue_any_t* queue);
int dequeue_any_wait(queue_any_t* queue, void *element);
#ifdef __cplusplus
}
#endif

#endif