#include "component_manager.h"


void component_manager_init(component_manager_t* c) {
	hash_map_init(&c->components[TRANSFORM_ID], sizeof(transform_t), MAX_ENTITIES / 4, hash_entity_t);
	hash_map_init(&c->components[SPRITE_ID], sizeof(sprite_t), MAX_ENTITIES / 4, hash_entity_t);
	hash_map_init(&c->components[SPRITE_ANIMATION_ID], sizeof(sprite_animation_t), MAX_ENTITIES / 4, hash_entity_t);	
}


void component_manager_close(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_map_close(&c->components[i]);
	}	
}


void component_manager_add(
	component_manager_t* c,
	const entity_t e,
	const component_t id,
	const void* component
) {	
	hash_map_insert(&c->components[id], &e, component);
}


void* component_manager_allocate(component_manager_t* c, entity_t e, component_t id) {
	return hash_map_allocate(&c->components[id], &e).data;
}


void* component_manager_get(
	component_manager_t* c,
	const entity_t e,
	const component_t id
) {	
	return hash_map_at(&c->components[id], &e);
}


void component_manager_entity_destroy(component_manager_t* c, entity_t e) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {		
		hash_map_erase(&c->components[i], &e);
	}
}


void component_manager_clear(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {		
		hash_map_clear(&c->components[i]);
	}
}