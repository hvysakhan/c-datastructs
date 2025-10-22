#include "hash_table.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ht_create(ht_t *ht, int num_hashes){
	if(ht == NULL || num_hashes <= 0)
		return -1;

	ht->num_hashes = num_hashes;
	ht->head = malloc(sizeof(ht_head_t)*num_hashes);
	for(int i=0; i<num_hashes; i++){
		ht->head[i].num_hash_elmnts = 0;
		ht->head[i].head = NULL;
	}
	return 0;
}


int compute_hash_djb2(ht_t *ht, char* key, int *hash_value){
	if(ht == NULL || key == NULL)
		return -1;
	*hash_value = 5381;
	char *key_head = key;
	while(*key_head != '\0'){
		*hash_value = (*hash_value * 33 + *key_head);
		key_head += 1;
	}
	*hash_value = *hash_value%ht->num_hashes;
	return 0;
}

int ht_add(ht_t *ht, char* key, void *value, size_t value_bytes){
	if(ht == NULL || key == NULL || value == NULL)
		return -1;
	void *val;
	if(ht_find(ht, key, &val) == 0){
		return -1;
	}

	int hash_value;
	uint64_t key_len = strlen(key);
	compute_hash_djb2(ht, key, &hash_value);
	
	ht->head[hash_value].num_hash_elmnts += 1;
	ht_element_t *old_head = ht->head[hash_value].head;
	ht_element_t *el = malloc(sizeof(ht_element_t));
	ht->head[hash_value].head  = el;
	el->next = old_head;

	el->key  = malloc(sizeof(char)*(key_len+1));
	el->value = malloc(value_bytes);
	strncpy(el->key, key, key_len+1);
	memcpy(el->value, value, value_bytes);
	// printf("hash value is %d\n", hash_value);
	// printf("key is %s\n", el->key);
	return 0;

}

int ht_find(ht_t *ht, char* key, void **value){
	if(ht == NULL || key == NULL)
		return -1;

	int hash_value;
	compute_hash_djb2(ht, key, &hash_value);
	ht_element_t *el = ht->head[hash_value].head;
	while(el != NULL){
		if(strcmp(el->key, key) == 0){
			// printf("FOUND\n");
			*value = el->value;
			// printf("value is %s\n", el->value);
			return 0;
		}
		el = el->next;
	}
	return -1;
}

int ht_delete(ht_t *ht, char *key){
	if(ht == NULL || key == NULL)
		return -1;

	int hash_value;
	compute_hash_djb2(ht, key, &hash_value);
	ht_element_t *el = ht->head[hash_value].head;
	ht_element_t *prev_el = NULL;
	while(el != NULL){

		if(strcmp(el->key, key) == 0){
			if(prev_el == NULL){
				ht->head[hash_value].head = el->next;
			}else{
				prev_el->next = el->next;
			}
			free(el->key);
			free(el->value);
			free(el);
			return 0;
		}
		prev_el = el;
		el = el->next;
	}
	return -1;
}


int ht_destroy(ht_t *ht){
	if(ht == NULL)
		return -1;
	ht_element_t *el, *prev_el;
	for (int i = 0; i < ht->num_hashes; i++){
		el = ht->head[i].head;
		while(el != NULL){
			prev_el = el;
			el = el->next;
			free(prev_el->key);
			free(prev_el->value);
			free(prev_el);
		}
		
	}
	free(ht->head);
	ht->head = NULL;
	ht->num_hashes = 0;
	return 0;
}
