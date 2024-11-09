#include "ecs.h"


void ecs_init(ecs_t* ecs) {
	entity_manager_init(&ecs->entity);
	component_manager_init(&ecs->component);
	system_manager_init(&ecs->system);
	vector_init(&ecs->static_collisions, sizeof(Rectangle), 1024);
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t), 512);
	ecs->camera = (camera_t*) malloc(sizeof(camera_t));
	camera_init(ecs->camera);
	ecs->should_destroy_all_entities = 0;
}


void ecs_close(ecs_t* ecs) {
	entity_manager_close(&ecs->entity);
	component_manager_close(&ecs->component);
	system_manager_close(&ecs->system);
	vector_close(&ecs->static_collisions);
	vector_close(&ecs->entities_to_destroy);
	camera_close(ecs->camera);
	free(ecs->camera);
}


entity_t ecs_entity_create(ecs_t* ecs, const zindex_t zindex, const int add_to_camera) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	transform_t t;
	transform_init(&t, zindex);	
	ecs_component_add(ecs, e, TRANSFORM_ID, &t);	
	if (add_to_camera) camera_insert(ecs->camera, e, zindex);
	return e;
}


void ecs_entity_destroy(ecs_t* ecs, const entity_t e) {
	vector_push_back(&ecs->entities_to_destroy, &e);
}


void ecs_destroy_entity_immediate(ecs_t* ecs, const entity_t e) {
	const zindex_t z = ecs_get_transform(ecs, e)->zindex;
	camera_erase(ecs->camera, e, z);
	entity_manager_destroy_entity(&ecs->entity, e);
	component_manager_entity_destroy(&ecs->component, e);
	system_manager_entity_destroy(&ecs->system, e);
}


void* ecs_component_get(ecs_t* ecs, const entity_t e, const component_t id) {
	return component_manager_get(&ecs->component, e, id);
}


transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return (transform_t*)component_manager_get(&ecs->component, e, TRANSFORM_ID);
}


void ecs_component_add(ecs_t* ecs, const entity_t e, const component_t id, const void* component) {
	component_manager_add(&ecs->component, e, id, component);
	system_manager_add(&ecs->system, e, id);
}

void* ecs_component_allocate(ecs_t* ecs, entity_t e, component_t id) {
	system_manager_add(&ecs->system, e, id);
	return component_manager_allocate(&ecs->component, e, id);
}


void ecs_update(ecs_t* ecs, const float dt) {
	system_manager_update(&ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		ecs_destroy_all_entities_immediate(ecs);
		vector_clear(&ecs->entities_to_destroy);
	}

	while (!vector_is_empty(&ecs->entities_to_destroy)) {
		entity_t e;
		vector_pop_back(&ecs->entities_to_destroy, &e);
		ecs_destroy_entity_immediate(ecs, e);
	}
}


void ecs_draw(ecs_t* ecs) {
	camera_draw(ecs->camera, &ecs->system);
}


void ecs_destroy_all_entities(ecs_t* ecs) {
	ecs->should_destroy_all_entities = 1;
}


void ecs_destroy_all_entities_immediate(ecs_t* ecs) {
	camera_clear(ecs->camera);
	entity_manager_clear(&ecs->entity);
	component_manager_clear(&ecs->component);
	system_manager_clear(&ecs->system);
}