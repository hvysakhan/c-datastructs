#ifndef LIST_H
#define LIST_H
#include <stddef.h>
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct{
	size_t data_bytes;
	int num_elements;
	int max_elements;
	named_element_t *head;
	named_element_t *tail;
}named_list_t;
int print_list(named_list_t* list, void (*print_fn)(void*));
int init_list(named_list_t* list, size_t bytes, int max_elements); // -1 for no max element
int deinit_list(named_list_t* list);
int append_to_list(named_list_t* list, const char* name, void* data);
int remove_from_list(named_list_t* list, const char* name);
#ifdef __cplusplus
}
#endif
#endif
