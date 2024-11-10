#include "entity_manager.h"
#include "assert.h"


void entity_manager_init(entity_manager_t* ent) {
	ent->entities = (entity_t*) malloc(sizeof(entity_t) * MAX_ENTITIES);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		ent->entities[e] = e;
	}	
	ent->size = 0;
}


void entity_manager_close(entity_manager_t* ent) {
	free(ent->entities);
}


entity_t entity_manager_create_entity(entity_manager_t* ent) {
	assert(ent->size < MAX_ENTITIES);
	return ent->entities[ent->size++];	
}


void entity_manager_destroy_entity(entity_manager_t* ent, const entity_t e) {
	ent->entities[--ent->size] = e;	
}


void entity_manager_clear(entity_manager_t* ent) {
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		ent->entities[e] = e;		
	}	
	ent->size = 0;
}

size_t entity_manager_num_entities(entity_manager_t* ent) {
	return ent->size;
}