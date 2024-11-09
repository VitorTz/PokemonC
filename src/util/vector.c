#include "vector.h"


void vector_init(vector_t* vec, const size_t v_size, const size_t capacity) {
	vec->v_size = v_size;
	vec->capacity = capacity;
	vec->size = 0;
	vec->data = (char*)malloc(v_size * capacity);	
}

void vector_close(vector_t* vec) {
	free(vec->data);	
}

void vector_grow(vector_t* vec) {
	const size_t new_capacity = vec->capacity * 2;
	void* tmp = realloc(vec->data, new_capacity * vec->v_size);
	if (tmp != NULL) {
		vec->data = tmp;
		vec->capacity = new_capacity;
	}
}

void vector_push_back(vector_t* vec, const void* data) {
	if (vec->size >= vec->capacity) {
		vector_grow(vec);
	}
	memcpy(vec->data + vec->v_size * vec->size++, data, vec->v_size);
}

void* vector_allocate(vector_t* vec) {
	if (vec->size >= vec->capacity) {
		vector_grow(vec);
	}
	return vec->data + vec->v_size * vec->size++;
}

void* vector_at(vector_t* vec, const size_t i) {
	return vec->data + vec->v_size * i;
}


void vector_erase(vector_t* vec, const size_t i) {
	memcpy(vec->data + vec->v_size * i, vec->data + vec->v_size * (vec->size - 1), vec->v_size);
	vec->size--;
}

void vector_pop_back(vector_t* vec, void* data) {
	memcpy(data, vec->data + vec->v_size * --vec->size, vec->v_size);	
}


void vector_set(vector_t* vec, const size_t i, const void* data) {
	memcpy(vec->data + vec->v_size * i, data, vec->v_size);
}

void vector_clear(vector_t* vec) {
	vec->size = 0;
}

void vector_cpy_to(vector_t* vec, const size_t i, void* data) {
	memcpy(data, vec->data + vec->v_size * i, vec->v_size);
}

int vector_is_empty(vector_t* vec) {
	return vec->size == 0;
}

iterator_t vector_iter(vector_t* vec) {
	const iterator_t iter = { vec->data, vec->data + vec->v_size * vec->size, vec->v_size };
	return iter;
}

size_t vector_size(vector_t* vec) {
	return vec->size;
}
