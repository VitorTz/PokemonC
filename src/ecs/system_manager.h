#pragma once
#include "../util/hash_set.h"
#include "../util/hash_map.h"
#include "../util/vector.h"
#include "../util/types.h"
#include "../util/constants.h"
#include "../util/util.h"
#include "../util/entity_pair.h"
#include "components.h"


typedef struct system {
	void (*update)(float, const entity_t e);
	void (*draw)(const entity_t);
} system_t;


typedef struct system_manager {	
	system_t systems[NUM_COMPONENTS];
	component_t update_order[NUM_UPDATABLE_COMPONENTS];
	component_t draw_order[NUM_DRAWABLE_COMPONENTS];	
	hash_set_t components_to_entities[NUM_COMPONENTS];
	entity_pair_t* entity_pair_vec;
} system_manager_t;


void system_manager_init(system_manager_t* s);

void system_manager_close(system_manager_t* s);

void system_manager_add(system_manager_t* s, entity_t e, component_t id);

void system_manager_entity_destroy(system_manager_t* s, entity_t e);

void system_manager_update(system_manager_t* s, float dt);

void system_manager_draw(system_manager_t* s);

void system_manager_clear(system_manager_t* s);

hash_set_t* system_manager_get_entities_from_system(system_manager_t* s, component_t id);


// Systems
void sprite_draw(const entity_t e);
void sprite_animation_update(float dt, const entity_t e);
void sprite_animation_draw(const entity_t e);

