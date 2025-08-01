#ifndef STACK_H
#define STACK_H
#include <stddef.h>
#include "common.h"


typedef struct{
	size_t data_bytes;
	int num_elements;
	element_t *head;
}ds_stack_t;

int print_stack(ds_stack_t* stack, void (*print_fn)(void*));
int init_stack(ds_stack_t* stack, size_t bytes);
int deinit_stack(ds_stack_t* stack);
int push(ds_stack_t* stack, void* data);
int pop(ds_stack_t* stack, void* element);

#endif