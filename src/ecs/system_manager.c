#include "system_manager.h"
#include "ecs_manager.h"
#include "search.h"


void system_manager_init(system_manager_t* s) {
	s->systems[TRANSFORM_ID].update = NULL;
	s->systems[TRANSFORM_ID].draw = NULL;
	s->systems[SPRITE_ID].update = NULL;
	s->systems[SPRITE_ID].draw = sprite_draw;
	s->systems[SPRITE_ANIMATION_ID].update = sprite_animation_update;
	s->systems[SPRITE_ANIMATION_ID].draw = sprite_animation_draw;

	s->update_order[0] = SPRITE_ANIMATION_ID;
	
	s->draw_order[0] = SPRITE_ID;
	s->draw_order[1] = SPRITE_ANIMATION_ID;

	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_init(&s->components_to_entities[i], sizeof(entity_t), MAX_ENTITIES / 4, hash_entity_t, equal_entity_t);
	}
	s->entity_pair_vec = (entity_pair_t*)malloc(sizeof(entity_pair_t) * MAX_ENTITIES);
}


void system_manager_close(system_manager_t* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_close(&s->components_to_entities[i]);
	}
	free(s->entity_pair_vec);
}


void system_manager_add(system_manager_t* s, const entity_t e, const component_t id) {	
	hash_set_insert(&s->components_to_entities[id], &e);
}


void system_manager_entity_destroy(system_manager_t* s, const entity_t e) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_erase(&s->components_to_entities[i], &e);
	}
}


void system_manager_update(system_manager_t* s, const float dt) {
	for (int i = 0; i < NUM_UPDATABLE_COMPONENTS; i++) {
		const component_t id = s->update_order[i];
		system_t* system = &s->systems[id];
		hash_set_t* entities = &s->components_to_entities[id];
		iterator_t iter = hash_set_iter(entities);
		for (vector_t* v = iter.begin; v < iter.end; v++) {
			iterator_t viter = vector_iter(v);
			for (entity_t* e = viter.begin; e < viter.end; e++) {
				system->update(dt, *e);
			}
		}
	}
}

static int entity_pair_cmp(const void* l, const void* r) {
	const entity_pair_t* a = (const entity_pair_t*)l;
	const entity_pair_t* b = (const entity_pair_t*)r;
	if (a->zindex == b->zindex) {
		return a->y > b->y;
	}
	return a->zindex > b->zindex;
}


void system_manager_draw(system_manager_t* s) {
	ecs_t* ecs = ecs_manager_get_ecs();

	camera_begin_drawing(&ecs->camera);
		for (int i = 0; i < NUM_DRAWABLE_COMPONENTS; i++) {
			const component_t id = s->draw_order[i];
			system_t* system = &s->systems[id];
			hash_set_t* entities = &s->components_to_entities[id];
			iterator_t iter = hash_set_iter(entities);
			size_t ent_vec_size = 0;
			for (vector_t* v = iter.begin; v < iter.end; v++) {
				iterator_t viter = vector_iter(v);
				for (entity_t* e = viter.begin; e < viter.end; e++) {
					transform_t* t = ecs_get_transform(ecs, *e);
					s->entity_pair_vec[ent_vec_size++] = (entity_pair_t){ t->zindex, t->pos.y + t->size.y / 2.0f, *e };				
				}
			}
			qsort(
				s->entity_pair_vec,
				ent_vec_size,
				sizeof(entity_pair_t),
				entity_pair_cmp
			);
			for (entity_pair_t* pair = s->entity_pair_vec; pair < s->entity_pair_vec + ent_vec_size; pair++) {
				system->draw(pair->e);
			}
		}
	camera_end_drawing();
}


hash_set_t* system_manager_get_entities_from_system(system_manager_t* s, component_t id) {
	return &s->components_to_entities[id];
}


void system_manager_clear(system_manager_t* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_clear(&s->components_to_entities[i]);
	}
}