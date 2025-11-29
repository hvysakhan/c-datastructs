#include "queue_any.h"
#include "common.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int print_queue_any(queue_any_t* queue, void (*print_fn)(void*)) {
	if(queue == NULL || print_fn == NULL){
		return -1;
	}

	sized_element_t* ele = queue->head;
	while(ele != NULL){
		print_fn(ele->data);
		printf("\t");
		ele = ele->nxt_element;
	}
	printf("\n");
	return 0;
}


int init_queue_any(queue_any_t* queue, int max_elements){
	if(queue == NULL) return -1;
	queue->max_elements = max_elements;
	queue->num_elements = 0;
	queue->head = NULL;
	queue->tail = NULL;
	pthread_mutex_init(&queue->queue_lock, NULL);
	pthread_cond_init(&queue->is_empty_cond, NULL);
	return 0;
}

int deinit_queue_any(queue_any_t* queue){
	if(queue == NULL)
		return -1;

	sized_element_t* ele = queue->head;
	sized_element_t *tmp;
	while(ele != NULL){
		tmp = ele;
		ele = ele->nxt_element;
		free(tmp->data);
		free(tmp);
	}
	queue->head = NULL;
	queue->tail = NULL;
	queue->num_elements = 0;
	pthread_mutex_destroy(&queue->queue_lock);
	pthread_cond_destroy(&queue->is_empty_cond);
	return 0;
}

int enqueue_any(queue_any_t* queue, void* data, size_t data_bytes){	
	if(queue == NULL){
		return -1;
	}
	pthread_mutex_lock(&queue->queue_lock);
	if(queue->max_elements >= 0 && queue->num_elements >= queue->max_elements){
		pthread_mutex_unlock(&queue->queue_lock);
		return -1;
	}
	sized_element_t *el = (sized_element_t*)malloc(sizeof(sized_element_t));
	el->nxt_element = NULL;
	el->data = malloc(data_bytes);
	el->data_bytes = data_bytes;
	memcpy(el->data, data, data_bytes);
	queue->num_elements+=1;
	if(queue->tail == NULL){
		assert(queue->head == NULL);
		queue->tail = el;
		queue->head = queue->tail;
		pthread_cond_broadcast(&queue->is_empty_cond);
		pthread_mutex_unlock(&queue->queue_lock);
		return 0;
	}	
	queue->tail->nxt_element = el;
	queue->tail = el;
	pthread_cond_broadcast(&queue->is_empty_cond);
	pthread_mutex_unlock(&queue->queue_lock);
	return 0;
}

int dequeue_any_wait(queue_any_t* queue, void *element){
	if(queue == NULL){
		return -1;
	}
	pthread_mutex_lock(&queue->queue_lock);
	while(queue->head == NULL){
		pthread_cond_wait(&queue->is_empty_cond, &queue->queue_lock);
	}
	if(queue->head == NULL){
		assert(queue->tail == NULL);
		pthread_mutex_unlock(&queue->queue_lock);
		return -1;
	}
	sized_element_t *old_head = queue->head; 
	size_t data_bytes = old_head->data_bytes;
	memcpy(element, queue->head->data, data_bytes);
	queue->head = queue->head->nxt_element;
	if(queue->head == NULL){
		queue->tail = NULL;
		pthread_cond_broadcast(&queue->is_empty_cond);
	}
	queue->num_elements -= 1;
	free(old_head->data);
	free(old_head);
	pthread_mutex_unlock(&queue->queue_lock);
	return data_bytes;
}

int dequeue_any(queue_any_t* queue, void* element){
	if(queue == NULL){
		return -1;
	}
	pthread_mutex_lock(&queue->queue_lock);
	if(queue->head == NULL){
		assert(queue->tail == NULL);
		pthread_mutex_unlock(&queue->queue_lock);
		return -1;
	}
	sized_element_t *old_head = queue->head; 
	size_t data_bytes = old_head->data_bytes;
	memcpy(element, queue->head->data, data_bytes);
	queue->head = queue->head->nxt_element;
	if(queue->head == NULL){
		queue->tail = NULL;
	}
	queue->num_elements -= 1;
	free(old_head->data);
	free(old_head);
	pthread_mutex_unlock(&queue->queue_lock);
	return data_bytes;
}

int return_size_before_dequeue(queue_any_t* queue){
	if(queue == NULL){
		return -1;
	}
	pthread_mutex_lock(&queue->queue_lock);
	if(queue->head == NULL){
		pthread_mutex_unlock(&queue->queue_lock);
		assert(queue->tail == NULL);
		return -1;
	}
	size_t data_bytes = queue->head->data_bytes;
	pthread_mutex_unlock(&queue->queue_lock);
	return data_bytes;
}

int return_size_before_dequeue_wait(queue_any_t* queue){	
	if(queue == NULL){
		return -1;
	}
	pthread_mutex_lock(&queue->queue_lock);
	while(queue->head == NULL){
		pthread_cond_wait(&queue->is_empty_cond, &queue->queue_lock);
	}
	// if(queue->head == NULL){
	// 	assert(queue->tail == NULL);
	// 	pthread_mutex_unlock(&queue->queue_lock);
	// 	return -1;
	// }
	size_t data_bytes = queue->head->data_bytes;
	pthread_mutex_unlock(&queue->queue_lock);
	return data_bytes;
}
