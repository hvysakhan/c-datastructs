#include "stack.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int init_stack(ds_stack_t* stack, size_t bytes){
	if(stack == NULL)
		return -1;
	if(bytes <= 0)
		return -1;

	stack->data_bytes = bytes;
	stack->head = NULL;
	stack->num_elements = 0;
	return 0;
}

int deinit_stack(ds_stack_t *stack){
	if(stack == NULL)
		return -1;

	element_t* ele = stack->head;
	element_t *tmp;
	while(ele != NULL){
		tmp = ele;
		ele = ele->nxt_element;
		free(tmp->data);
		free(tmp);
	}

	stack->head = NULL;
	stack->num_elements = 0;
	return 0;
}

int print_stack(ds_stack_t* stack, void (*print_fn)(void*)){
	if(stack == NULL || print_fn == NULL)
		return -1;

	element_t* ele = stack->head;
	while(ele != NULL){
		print_fn(ele->data);
		printf("\t");
		ele = ele->nxt_element;
	}
	printf("\n");
	return 0;
};

int push(ds_stack_t *stack, void *data){
	if(stack == NULL)
		return -1;

	element_t *el = (element_t*)malloc(sizeof(element_t));
	el->nxt_element = NULL;
	el->data = malloc(stack->data_bytes);
	memcpy(el->data, data, stack->data_bytes);

	element_t *old_head = stack->head;
	stack->head = el;
	el->nxt_element = old_head;
	stack->num_elements += 1;
	return 0;
}

int pop(ds_stack_t* stack, void* element){
	if(stack == NULL)
		return -1;

	if(stack->head == NULL){
		return -1;
	}

	element_t *old_head = stack->head; 
	memcpy(element, stack->head->data, stack->data_bytes);
	stack->head = stack->head->nxt_element;
	
	stack->num_elements -= 1;
	free(old_head->data);
	free(old_head);
	return 0;
}
