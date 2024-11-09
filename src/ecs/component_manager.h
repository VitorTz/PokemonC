#pragma once
#include "../util/hash_map.h"
#include "../util/types.h"
#include "../util/constants.h"
#include "../util/util.h"
#include "components.h"

typedef struct component_manager {
	hash_map_t* component_map;
} component_manager_t;


void component_manager_init(component_manager_t* c);

void component_manager_close(component_manager_t* c);

void component_manager_add(component_manager_t* c, entity_t e, component_t id, const void* component);

void* component_manager_get(component_manager_t* c, entity_t e, component_t id);

void* component_manager_allocate(component_manager_t* c, entity_t e, component_t id);

void component_manager_entity_destroy(component_manager_t* c, entity_t e);

void component_manager_clear(component_manager_t* c);