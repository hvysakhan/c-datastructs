#include "named_list.h"
#include <stdlib.h>
#include <string.h>

int init_list(named_list_t* list, size_t bytes, int max_elements){
	list->data_bytes = bytes;
	list->num_elements = 0;
	list->max_elements = max_elements;
	list->head = NULL;
	list->tail = NULL;
	return 0;
}

int deinit_list(named_list_t* list){
	named_element_t* current = list->head;
	named_element_t* next;
	while(current != NULL){
		next = current->nxt_element;
		free(current->data);
		free(current->name);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->num_elements = 0;
	return 0;
}

int append_to_list(named_list_t* list, const char* name, void* data){
	if(name == NULL){
		return -1; // Name cannot be NULL
	}

	if(list->max_elements != -1 && list->num_elements >= list->max_elements){
		return -1; // List is full
	}
	named_element_t* new_element = (named_element_t*)malloc(sizeof(named_element_t));
	if(new_element == NULL){
		return -1; // Memory allocation failed
	}
	new_element->name = strdup(name);
	new_element->data = malloc(list->data_bytes);
	if(new_element->data == NULL){
		free(new_element);
		return -1; // Memory allocation failed
	}
	memcpy(new_element->data, data, list->data_bytes);
	new_element->nxt_element = NULL;
	if(list->head == NULL){
		list->head = new_element;
		list->tail = new_element;
	} else {
		list->tail->nxt_element = new_element;
		list->tail = new_element;
	}
	list->num_elements++;
	return 0;
}

int remove_from_list(named_list_t* list, const char* name){
	named_element_t* current = list->head;
	named_element_t* previous = NULL;
	while(current != NULL){
		if(strcmp(current->name,  name) == 0){
			if(previous == NULL){
				list->head = current->nxt_element;
			} else {
				previous->nxt_element = current->nxt_element;
			}
			if(current == list->tail){
				list->tail = previous;
			}
			free(current->name);
			free(current->data);
			free(current);
			list->num_elements--;
			return 0; // Successfully removed
		}
		previous = current;
		current = current->nxt_element;
	}
	return -1; // Element not found
}

int print_list(named_list_t* list, void (*print_fn)(void*)){
	named_element_t* current = list->head;
	while(current != NULL){
		print_fn(current->data);
		current = current->nxt_element;
	}
	return 0;
}