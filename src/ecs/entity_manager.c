#include "entity_manager.h"
#include "assert.h"


void entity_manager_init(entity_manager_t* ent) {
	vector_init(&ent->entities, sizeof(entity_t), MAX_ENTITIES);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		vector_push_back(&ent->entities, &e);
	}	
	ent->size = 0;
}


void entity_manager_close(entity_manager_t* ent) {
	vector_close(&ent->entities);
}


entity_t entity_manager_create_entity(entity_manager_t* ent) {
	assert(ent->size < MAX_ENTITIES);
	entity_t e; vector_pop_back(&ent->entities, &e);
	ent->size++;
	return e;
}


void entity_manager_destroy_entity(entity_manager_t* ent, const entity_t e) {
	vector_push_back(&ent->entities, &e);	
	ent->size--;
}


void entity_manager_clear(entity_manager_t* ent) {
	vector_clear(&ent->entities);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		vector_push_back(&ent->entities, &e);
	}
	ent->size = 0;
}

size_t entity_manager_num_entities(entity_manager_t* ent) {
	return ent->size;
}