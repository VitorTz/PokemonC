#pragma once
#include "types.h"
#include "constants.h"
#include "entity_pair.h"
#include "hash_map.h"
#include <stdlib.h>
#include <search.h>


typedef struct ordered_entity_vec {
	entity_pair_t* entities;
	hash_map_t dynamic_pos_entities;
	size_t size;
} ordered_entity_vec_t;

void ordered_entity_vec_init(ordered_entity_vec_t* vec);

void ordered_entity_vec_close(ordered_entity_vec_t* vec);

void ordered_entity_vec_insert_static_entity(ordered_entity_vec_t* vec, entity_t e);

void ordered_entity_vec_insert_dynamic_entity(ordered_entity_vec_t* vec, entity_t e);

void ordered_entity_vec_erase(ordered_entity_vec_t* vec, entity_t e);

void ordered_entity_vec_sort(ordered_entity_vec_t* vec);

void ordered_entity_vec_clear(ordered_entity_vec_t* vec);