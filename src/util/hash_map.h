#pragma once
#include "vector.h"
#include "query.h"


typedef struct hash_map {
	vector_t* buckets;
	size_t(*hash)(const void*);
	size_t nbuckets;
	size_t v_size;
	size_t size;
} hash_map_t;


void hash_map_init(
	hash_map_t* h,
	size_t v_size,
	size_t nbuckets,
	size_t(*hash)(const void*)
);


void hash_map_close(hash_map_t* h);

void hash_map_insert(hash_map_t* h, const void* k, const void* v);

query_t hash_map_allocate(hash_map_t* h, const void* k);

query_t hash_map_try_insert(hash_map_t* h, const void* k, const void* v);

query_t hash_map_find(hash_map_t* h, const void* k, const void* v);

void* hash_map_at(hash_map_t* h, const void* k);

iterator_t hash_map_iter(hash_map_t* h);

void hash_map_erase(hash_map_t* h, const void* k);

void hash_map_clear(hash_map_t* h);

size_t hash_map_size(hash_map_t* h);

int hash_map_is_empty(hash_map_t* h);
