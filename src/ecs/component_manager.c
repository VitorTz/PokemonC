#include "component_manager.h"


void component_manager_init(component_manager_t* c) {
	c->component_map = (hash_map_t*) malloc(sizeof(hash_map_t) * NUM_COMPONENTS);
	hash_map_init(c->component_map + TRANSFORM_ID, sizeof(transform_t), MAX_ENTITIES / 4, hash_entity_t);
	hash_map_init(c->component_map + SPRITE_ID, sizeof(sprite_t), MAX_ENTITIES / 4, hash_entity_t);
	hash_map_init(c->component_map + SPRITE_ANIMATION_ID, sizeof(sprite_animation_t), MAX_ENTITIES / 4, hash_entity_t);
}


void component_manager_close(component_manager_t* c) {
	hash_map_close(c->component_map + TRANSFORM_ID);
	hash_map_close(c->component_map + SPRITE_ID);
	hash_map_close(c->component_map + SPRITE_ANIMATION_ID);
	free(c->component_map);
}


void component_manager_add(
	component_manager_t* c,
	const entity_t e,
	const component_t id,
	const void* component
) {
	hash_map_t* h = c->component_map + id;
	hash_map_insert(h, &e, component);
}


void* component_manager_allocate(component_manager_t* c, entity_t e, component_t id) {
	hash_map_t* h = c->component_map + id;
	return hash_map_allocate(h, &e).data;
}


void* component_manager_get(
	component_manager_t* c,
	const entity_t e,
	const component_t id
) {
	hash_map_t* h = c->component_map + id;
	return hash_map_at(h, &e);
}


void component_manager_entity_destroy(component_manager_t* c, entity_t e) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_map_t* h = c->component_map + i;
		hash_map_erase(h, &e);
	}
}


void component_manager_clear(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_map_t* h = c->component_map + i;
		hash_map_clear(h);
	}
}