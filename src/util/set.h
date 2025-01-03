#ifndef POKE_SET_H
#define POKE_SET_H
#include "vector.h"


typedef struct _set_node {
	struct _set_node* left;
	struct _set_node* right;
	size_t key;	
	void* data;
	int height;
} SetNode;


typedef struct _set_iterator {
	Vector* node_arr;
	SetNode* begin;
	SetNode* end;	
} SetIterator;

typedef struct _set {
	SetNode* root;
	size_t (*hash)(const void*);
	size_t type_size;	
	size_t size;
	SetIterator iter;
} Set;


Set* set_create(size_t type_size, size_t(*hash)(const void*));

void set_init(Set* set, size_t type_size, size_t(*hash)(const void*));

void set_destroy(Set* set);

void set_close(Set* set);

void set_insert(Set* set, const void* key);

void set_erase(Set* set, const void* key);

void set_clear(Set* set);

SetIterator* set_iter(Set* set);

void* set_iter_next(SetIterator* iter);


#endif // !POKE_SET_H
