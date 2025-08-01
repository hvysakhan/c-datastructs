#include "queue.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int print_queue(queue_t* queue, void (*print_fn)(void*)) {
	if(queue == NULL || print_fn == NULL)
		return -1;

	element_t* ele = queue->head;
	while(ele != NULL){
		print_fn(ele->data);
		printf("\t");
		ele = ele->nxt_element;
	}
	printf("\n");
	return 0;
}


int init_queue(queue_t* queue, size_t bytes){
	if(queue == NULL)
		return -1;
	if(bytes<=0)
		return -1;
	queue->data_bytes = bytes;
	queue->num_elements = 0;
	queue->head = NULL;
	queue->tail = NULL;
	return 0;
}

int deinit_queue(queue_t* queue){
	if(queue == NULL)
		return -1;

	element_t* ele = queue->head;
	element_t *tmp;
	while(ele != NULL){
		tmp = ele;
		ele = ele->nxt_element;
		free(tmp->data);
		free(tmp);
	}
	queue->head = NULL;
	queue->tail = NULL;
	queue->num_elements = 0;
	return 0;
}

int enqueue(queue_t* queue, void* data){
	if(queue == NULL)
		return -1;

	element_t *el = malloc(sizeof(element_t));
	el->nxt_element = NULL;
	el->data = malloc(queue->data_bytes);
	memcpy(el->data, data, queue->data_bytes);
	if(queue->tail == NULL){
		assert(queue->head == NULL);
		queue->tail = el;
		queue->head = queue->tail;
		return 0;
	}	
	queue->tail->nxt_element = el;
	queue->tail = el;
	queue->num_elements+=1;
	return 0;
}

int dequeue(queue_t* queue, void* element){
	if(queue == NULL)
		return -1;

	if(queue->head == NULL){
		assert(queue->tail == NULL);
		return -1;
	}
	element_t *old_head = queue->head; 
	memcpy(element, queue->head->data, queue->data_bytes);
	queue->head = queue->head->nxt_element;
	if(queue->head == NULL)
		queue->tail = NULL;
	queue->num_elements -= 1;
	free(old_head->data);
	free(old_head);
	return 0;
}

