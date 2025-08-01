#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct ht_element{
	char *key;
	char *value;
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
int ht_add(ht_t *ht, char *key, char *value);
int ht_find(ht_t *ht, char *key, char **value);
#endif