#include "hash_set.h"


void hash_set_init(
	hash_set_t* h,
	size_t v_size,
	size_t nbuckets,
	size_t(*hash)(const void*),
	int (*equal)(const void*, const void*)
) {
	h->buckets = (vector_t*)malloc(sizeof(vector_t) * nbuckets);
	h->hash = hash;
	h->equal = equal;
	h->nbuckets = nbuckets;
	h->size = 0;
	const iterator_t iter = hash_set_iter(h);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_init(v, v_size, 4);
	}
}


void hash_set_close(hash_set_t* h) {
	const iterator_t iter = hash_set_iter(h);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}
	free(h->buckets);
}


iterator_t hash_set_iter(hash_set_t* h) {
	const iterator_t iter = { h->buckets, h->buckets + h->nbuckets, 1 };
	return iter;
}


void hash_set_insert(hash_set_t* h, const void* data) {
	const size_t k = h->hash(data);
	vector_t* v = h->buckets + k % h->nbuckets;
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p++) {
		if (h->equal(p, data)) {
			return;
		}
	}	
	memcpy(vector_allocate(v), data, v->v_size);
	h->size++;
}


void hash_set_erase(hash_set_t* h, const void* data) {
	const size_t k = h->hash(data);
	size_t i = 0;
	vector_t* v = h->buckets + k % h->nbuckets;
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p++) {
		if (h->equal(p, data)) {
			vector_erase(v, i);
			h->size--;
			return;
		}
		i++;
	}
}


int hash_set_contains(hash_set_t* h, const void* data) {
	const size_t k = h->hash(data);
	vector_t* v = h->buckets + k % h->nbuckets;
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p++) {
		if (h->equal(p, data)) {
			return 1;
		}
	}
	return 0;
}


void hash_set_clear(hash_set_t* h) {
	const iterator_t iter = hash_set_iter(h);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_clear(v);
	}
	h->size = 0;
}