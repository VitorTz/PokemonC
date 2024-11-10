#include "ordered_entity_vec.h"
#include "constants.h"


static int compare_pairs(const void* l, const void* r) {
	const float a = ((const entity_pair_t*)l)->y;
	const float b = ((const entity_pair_t*)r)->y;
	return a < b;
}


void ordered_entity_vec_init(ordered_entity_vec_t* vec) {
	vec->entities = (entity_pair_t*) malloc(sizeof(entity_pair_t) * MAX_ENTITIES);
	vec->size = 0;
}

void ordered_entity_vec_close(ordered_entity_vec_t* vec) {
	free(vec->entities);
}

void ordered_entity_vec_insert(ordered_entity_vec_t* vec, const entity_t e) {
	*(vec->entities + vec->size++) = (entity_pair_t){ e, 0.0f };	
}


void ordered_entity_vec_erase(ordered_entity_vec_t* vec, const entity_t e) {
	entity_pair_t* begin = vec->entities;
	entity_pair_t* end = vec->entities + vec->size;
	for (entity_pair_t* p = begin; p < end; p++) {
		if (p->e == e) {
			*p = *(end - 1);
			vec->size--;
			return;
		}
	}
}


void ordered_entity_vec_sort(ordered_entity_vec_t* v) {
	qsort(v->entities, v->size, sizeof(entity_pair_t), compare_pairs);
}

void ordered_entity_vec_clear(ordered_entity_vec_t* vec) {
	vec->size = 0;
}