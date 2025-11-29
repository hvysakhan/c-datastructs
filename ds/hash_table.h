#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ht_element{
	char *key;
	void *value;
	size_t value_bytes;
	struct ht_element *next;
}ht_element_t;

typedef struct{
	int num_hash_elmnts;
	ht_element_t *head;
}ht_head_t;

typedef struct{
	int num_hashes;
	ht_head_t *head;
}ht_t;

int ht_create(ht_t *ht, int num_hashes);
int ht_add(ht_t *ht, const char *key, void *value, size_t value_bytes);
int ht_find(ht_t *ht, const char *key, void **value);
int ht_delete(ht_t *ht, const char *key);
int ht_destroy(ht_t *ht);

#ifdef __cplusplus
}
#endif

#endif