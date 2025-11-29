#ifndef COMMON_H
#define COMMON_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

typedef struct element{
	void* data;
	struct element *nxt_element;
}element_t;

typedef struct named_element{
	char* name;
	void* data;
	struct named_element *nxt_element;
}named_element_t;

typedef struct sized_element{
	size_t data_bytes;
	void* data;
	struct sized_element *nxt_element;
}sized_element_t;

#ifdef __cplusplus
}
#endif
#endif