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
	system_t* systems;
	hash_map_t component_to_entities_map;
	hash_map_t entities_to_drawable_components_map;
	hash_set_t drawable_components;
	vector_t system_order;
} system_manager_t;


void system_manager_init(system_manager_t* s);

void system_manager_close(system_manager_t* s);

void system_manager_add(system_manager_t* s, entity_t e, component_t id);

void system_manager_update(system_manager_t* s, float dt);

void system_manager_draw(system_manager_t* s, vector_t* entities);

void system_manager_entity_destroy(system_manager_t* s, entity_t e);

void system_manager_clear(system_manager_t* s);


// Systems
void sprite_draw(const entity_t e);
void sprite_animation_update(float dt, const entity_t e);
void sprite_animation_draw(const entity_t e);

