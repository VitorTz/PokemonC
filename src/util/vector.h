#pragma once
#include <stdlib.h>
#include <string.h>
#include "iterator.h"


typedef struct vector {
	size_t v_size;
	size_t size;
	size_t capacity;
	char* data;
} vector_t;

void vector_init(vector_t* vec, size_t v_size, size_t capacity);

void vector_close(vector_t* vec);

void vector_grow(vector_t* vec);

void vector_push_back(vector_t* vec, const void* data);

void vector_pop_back(vector_t* vec, void* data);

void* vector_allocate(vector_t* vec);

void* vector_at(vector_t* vec, size_t i);

void vector_set(vector_t* vec, size_t i, const void* data);

void vector_erase(vector_t* vec, size_t i);

void vector_cpy_to(vector_t* vec, size_t i, void* data);

void vector_clear(vector_t* vec);

int vector_is_empty(vector_t* vec);

iterator_t vector_iter(vector_t* vec);

size_t vector_size(vector_t* vec);
