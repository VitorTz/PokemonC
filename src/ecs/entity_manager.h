#pragma once
#include "../util/vector.h"
#include "../util/types.h"
#include "../util/constants.h"


typedef struct entity_manager {
	vector_t entities;	
	size_t size;
} entity_manager_t;


void entity_manager_init(entity_manager_t* ent);

void entity_manager_close(entity_manager_t* ent);

entity_t entity_manager_create_entity(entity_manager_t* ent);

void entity_manager_destroy_entity(entity_manager_t* ent, entity_t e);

void entity_manager_clear(entity_manager_t* ent);

size_t entity_manager_num_entities(entity_manager_t* ent);