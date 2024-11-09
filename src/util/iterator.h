#pragma once
#include <stddef.h>


typedef struct iterator {
	void* begin;
	void* end;
	size_t step;
} iterator_t;