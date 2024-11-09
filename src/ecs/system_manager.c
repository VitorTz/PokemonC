#include "system_manager.h"


static const component_t transform_id = TRANSFORM_ID;
static const component_t sprite_id = SPRITE_ID;
static const component_t sprite_animation_id = SPRITE_ANIMATION_ID;


void system_manager_init(system_manager_t* s) {
	s->systems = (system_t*) malloc(sizeof(system_t) * NUM_COMPONENTS);
	// Register Systems
	(s->systems + TRANSFORM_ID)->update = NULL;
	(s->systems + TRANSFORM_ID)->draw = NULL;

	(s->systems + SPRITE_ID)->update = NULL;
	(s->systems + SPRITE_ID)->draw = sprite_draw;

	(s->systems + SPRITE_ANIMATION_ID)->update = sprite_animation_update;
	(s->systems + SPRITE_ANIMATION_ID)->draw = sprite_animation_draw;

	// Init component_to_entities_map
	hash_map_init(&s->component_to_entities_map, sizeof(hash_set_t), MAX_ENTITIES / 4, hash_component_t);
	for (component_t id = 0; id < NUM_COMPONENTS; id++) {
		query_t q = hash_map_allocate(&s->component_to_entities_map, &id);
		hash_set_t* set = (hash_set_t*)q.data;
		hash_set_init(set, sizeof(entity_t), MAX_ENTITIES / 4, hash_entity_t, equal_entity_t);
	}

	// Init entities_to_drawable_components_map
	hash_map_init(&s->entities_to_drawable_components_map, sizeof(vector_t), MAX_ENTITIES / 4, hash_entity_t);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		query_t q = hash_map_allocate(&s->entities_to_drawable_components_map, &e);
		vector_t* vec = (vector_t*) q.data;
		vector_init(vec, sizeof(component_t), 4);		
	}

	// Register drawable components	
	hash_set_init(&s->drawable_components, sizeof(component_t), 2, hash_component_t, equal_component_t);		
	hash_set_insert(&s->drawable_components, &sprite_id);	// sprite
	hash_set_insert(&s->drawable_components, &sprite_animation_id);	// sprite animation

	// Update Order
	vector_init(&s->system_order, sizeof(component_t), NUM_COMPONENTS);
	vector_push_back(&s->system_order, &sprite_animation_id);
}


void system_manager_close(system_manager_t* s) {
	iterator_t iter, viter;
	
	iter = hash_map_iter(&s->component_to_entities_map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		viter = vector_iter(v);
		for (char* p = viter.begin; p < viter.end; p += viter.step) {
			hash_set_t* set = (hash_set_t*) (p + sizeof(size_t));
			hash_set_close(set);
		}
	}
	hash_map_close(&s->component_to_entities_map);
	
	iter = hash_map_iter(&s->entities_to_drawable_components_map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		viter = vector_iter(v);
		for (char* p = viter.begin; p < viter.end; p += viter.step) {
			vector_t* v1 = (vector_t*)(p + sizeof(size_t));
			vector_close(v1);
		}
	}
	hash_map_close(&s->entities_to_drawable_components_map);
	hash_set_close(&s->drawable_components);
	vector_close(&s->system_order);	
	free(s->systems);
}


void system_manager_add(
	system_manager_t* s,
	const entity_t e,
	const component_t id
) {
	hash_map_insert(&s->component_to_entities_map, &id, &e);
	if (hash_set_contains(&s->drawable_components, &id)) {
		vector_t* vec = hash_map_at(&s->entities_to_drawable_components_map, &e);
		vector_push_back(vec, &id);
	}
}


void system_manager_update(system_manager_t* s, const float dt) {
	const iterator_t iter = vector_iter(&s->system_order);
	for (component_t* id = iter.begin; id < iter.end; id++) {
		system_t* system = s->systems + *id;
		hash_set_t* set = (hash_set_t*) hash_map_at(&s->component_to_entities_map, id);
		iterator_t set_iter = hash_set_iter(set);
		for (vector_t* v = set_iter.begin; v < set_iter.end; v++) {
			iterator_t viter = vector_iter(v);
			for (entity_t* e = viter.begin; e < viter.end; e++) {
				system->update(dt, e);
			}
		}		
	}
}


void system_manager_draw(system_manager_t* s, vector_t* entities) {
	const iterator_t iter = vector_iter(entities);
	for (entity_pair_t* p = iter.begin; p < iter.end; p++) {		
		vector_t* vec = (vector_t*) hash_map_at(&s->entities_to_drawable_components_map, &p->e);
		iterator_t viter = vector_iter(vec);
		for (component_t* id = viter.begin; id < viter.end; id++) {
			system_t* system = s->systems + *id;
			system->draw(p->e);
		}
	}
}


void system_manager_entity_destroy(system_manager_t* s, const entity_t e) {	
	for (component_t id = 0; id < NUM_COMPONENTS; id++) {
		hash_set_t* set = (hash_set_t*) hash_map_at(&s->component_to_entities_map, &id);
		hash_set_erase(set, &e);
	}	
	vector_t* vec = (vector_t*) hash_map_at(&s->entities_to_drawable_components_map, &e);
	vector_clear(vec);
}


void system_manager_clear(system_manager_t* s) {
	for (component_t id = 0; id < NUM_COMPONENTS; id++) {
		hash_set_t* set = (hash_set_t*)hash_map_at(&s->component_to_entities_map, &id);
		hash_set_clear(set);
	}
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		vector_t* vec = (vector_t*)hash_map_at(&s->entities_to_drawable_components_map, &e);
		if (vec != NULL) {
			vector_clear(vec);
		}
	}
}