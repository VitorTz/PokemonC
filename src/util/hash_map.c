#include "hash_map.h"


void hash_map_init(
	hash_map_t* h,
	const size_t v_size,
	const size_t nbuckets,
	size_t(*hash)(const void*)
) {	
	h->buckets = (vector_t*)malloc(sizeof(vector_t) * nbuckets);
	h->hash = hash;
	h->nbuckets = nbuckets;
	h->v_size = v_size;
	h->size = 0;
	const iterator_t iter = hash_map_iter(h);
	for (vector_t* v = iter.begin; v < iter.end; v += iter.step) {
		vector_init(v, sizeof(size_t) + v_size, 4);
	}
}

iterator_t hash_map_iter(hash_map_t* h) {
	const iterator_t iter = { h->buckets, h->buckets + h->nbuckets, 1 };
	return iter;
}

void hash_map_close(hash_map_t* h) {
	const iterator_t iter = hash_map_iter(h);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}
	free(h->buckets);	
}

void hash_map_insert(hash_map_t* h, const void* key, const void* value) {
	const size_t k = h->hash(key);
	vector_t* v = h->buckets + (k % h->nbuckets);
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == k) {
			return;
		}
	}
	h->size++;
	char* new_pair = vector_allocate(v);
	*((size_t*)new_pair) = k;
	memcpy(new_pair + sizeof(size_t), value, h->v_size);
}

query_t hash_map_allocate(hash_map_t* h, const void* key) {
	query_t q = { 0, NULL };
	const size_t k = h->hash(key);
	vector_t* v = h->buckets + (k % h->nbuckets);
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == k) {
			q.data = p + sizeof(size_t);
			return q;
		}
	}
	h->size++;
	char* new_pair = vector_allocate(v);
	*((size_t*)new_pair) = k;	
	q.success = 1;
	q.data = new_pair + sizeof(size_t);
	return q;
}

query_t hash_map_try_insert(hash_map_t* h, const void* key, const void* value) {
	query_t q = { 0, NULL };
	const size_t k = h->hash(key);
	vector_t* v = h->buckets + (k % h->nbuckets);
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == k) {
			return q;			
		}
	}
	h->size++;
	char* new_pair = vector_allocate(v);
	*((size_t*)new_pair) = k;
	memcpy(new_pair + sizeof(size_t), value, h->v_size);
	q.success = 1;
	q.data = new_pair + sizeof(size_t);
	return q;
}


query_t hash_map_find(hash_map_t* h, const void* key, const void* value) {
	query_t q = { 0, NULL };
	const size_t k = h->hash(key);
	vector_t* v = h->buckets + (k % h->nbuckets);
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == k) {
			q.success = 1;
			q.data = p + sizeof(size_t);
			return q;
		}
	}
	return q;
}


void* hash_map_at(hash_map_t* h, const void* key) {
	const size_t k = h->hash(key);
	vector_t* v = h->buckets + (k % h->nbuckets);
	const iterator_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == k) {
			return p + sizeof(size_t);			
		}
	}
	return NULL;
}



void hash_map_erase(hash_map_t* h, const void* key) {
	const size_t k = h->hash(key);
	vector_t* v = h->buckets + (k % h->nbuckets);
	const iterator_t iter = vector_iter(v);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == k) {
			vector_erase(v, i);
			h->size--;
			return;			
		}
		i++;
	}
}

void hash_map_clear(hash_map_t* h) {
	const iterator_t iter = hash_map_iter(h);
	for (vector_t* v = iter.begin; v < iter.end; v += iter.step) {
		vector_clear(v);
	}
	h->size = 0;
}

int hash_map_is_empty(hash_map_t* h) {
	return h->size == 0;
}

size_t hash_map_size(hash_map_t* h) {
	return h->size;
}
