#pragma once
#include "vector.h"

typedef struct hash_set {
	vector_t* buckets;
	size_t(*hash)(const void*);
	int (*equal)(const void*, const void*);
	size_t nbuckets;
	size_t size;
} hash_set_t;


void hash_set_init(
	hash_set_t* h,
	size_t v_size,
	size_t nbuckets,
	size_t (*hash)(const void*),
	int (*equal)(const void*, const void*)
);

iterator_t hash_set_iter(hash_set_t* h);

void hash_set_close(hash_set_t* h);

void hash_set_insert(hash_set_t* h, const void* data);

void hash_set_erase(hash_set_t* h, const void* data);

int hash_set_contains(hash_set_t* h, const void* data);

void hash_set_clear(hash_set_t* h);