#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "ds/queue.h"
#include "ds/stack.h"
#include "ds/hash_table.h"

void print_int(void* data) {
	printf("%d", *(int*)data);
}


void test_queue(){
	queue_t queue;
	int a = 3;
	init_queue(&queue, sizeof(int));
	assert(queue.head == NULL && queue.tail == NULL && queue.num_elements == 0);
	enqueue(&queue, &a);
	assert(queue.num_elements == 1);
	a = 4;
	enqueue(&queue, &a);
	print_queue(&queue, print_int);
	int el;
	dequeue(&queue, &el);
	assert(queue.num_elements == 1);
	print_queue(&queue, print_int);
	dequeue(&queue, &el);
	assert(queue.num_elements == 0 && queue.head == NULL && queue.tail == NULL);
	print_queue(&queue, print_int);
	dequeue(&queue, &el);
	print_queue(&queue, print_int);
	enqueue(&queue, &a);
	deinit_queue(&queue);
	assert(queue.num_elements == 0 && queue.head == NULL && queue.tail == NULL);
	init_queue(&queue, sizeof(int));
	assert(queue.head == NULL && queue.tail == NULL && queue.num_elements == 0);
	enqueue(&queue, &a);
	assert(queue.num_elements == 1);
}

void test_stack(){
	ds_stack_t stack;
	int el;
	int a = 4;
	init_stack(&stack, sizeof(int));
	assert(stack.head == NULL && stack.num_elements == 0);
	push(&stack, &a);
	assert(stack.num_elements == 1);
	a = 5;
	push(&stack, &a);
	assert(stack.num_elements == 2);
	print_stack(&stack, print_int);
	pop(&stack, &el);
	assert(stack.num_elements == 1);
	print_stack(&stack, print_int);
	pop(&stack, &el);
	assert(stack.num_elements == 0 && stack.head == NULL);
	pop(&stack, &el);
	pop(&stack, &el);
	print_stack(&stack, print_int);
	push(&stack, &a);
	assert(stack.num_elements == 1 && stack.head != NULL);
	deinit_stack(&stack);
	assert(stack.num_elements == 0 && stack.head == NULL);
}



void test_hashtable(){
	ht_t ht;
	char *key = "hello";
	typedef struct rand{
		int a, b;
	}rand_t;
	rand_t rand;
	rand.a = 99;
	rand.b = 96;
	void *value2;


	ht_create(&ht, 100);
	ht_add(&ht, key, &rand, sizeof(rand_t));
	assert(ht_find(&ht, key, &value2) == 0);
	rand_t *el2 = (rand_t*)value2;
	printf("value is %d %d\n", el2->a, el2->b);
	assert(ht_find(&ht, "abcd", &value2) != 0);
	assert(ht_delete(&ht, key) == 0);
	assert(ht_delete(&ht, "abcd")!=0);
	assert(ht_find(&ht, key, &value2) !=0);
	ht_destroy(&ht);
	assert(ht.num_hashes == 0 && ht.head == NULL);
}

int main(void){	
	
	test_queue();
	test_stack();
	test_hashtable();
	
	return 0;
}