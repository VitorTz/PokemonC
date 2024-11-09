#include "util.h"


size_t hash_entity_t(const void* k) {
	const size_t i = *((entity_t*)k);
	return i;
}


size_t hash_zindex_t(const void* k) {
	const size_t i = *((zindex_t*)k);
	return i;
}


size_t hash_component_t(const void* k) {
	const size_t i = *((component_t*)k);
	return i;
}


size_t hash_str(const void* s) {
	const char* str = (const char*)s;
	size_t h = 5381;
	int c;
	while ((c = *str++))
		h = ((h << 5) + h) + c;
	return h;	
}

int equal_entity_t(const void* l, const void* r) {
	return *((entity_t*)l) == *((entity_t*)r);
}


int equal_component_t(const void* l, const void* r) {
	return *((component_t*)l) == *((component_t*)r);
}