#pragma once
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "../util/camera.h"


typedef struct ecs {
	entity_manager_t entity;
	component_manager_t component;
	system_manager_t system;
	camera_t camera;
	vector_t static_collisions;
	vector_t entities_to_destroy;
	int should_destroy_all_entities;	
} ecs_t;


void ecs_init(ecs_t* ecs);

void ecs_close(ecs_t* ecs);

entity_t ecs_entity_create(ecs_t* ecs, zindex_t zindex);

entity_t ecs_sprite_create(ecs_t* ecs, zindex_t zindex, const char* file_name);

void ecs_entity_destroy(ecs_t* ecs, entity_t e);

void ecs_destroy_entity_immediate(ecs_t* ecs, entity_t e);

void* ecs_component_get(ecs_t* ecs, entity_t e, component_t id);

void* ecs_component_allocate(ecs_t* ecs, entity_t e, component_t id);

void ecs_component_add(ecs_t* ecs, entity_t e, component_t id, const void* component);

transform_t* ecs_get_transform(ecs_t* ecs, entity_t e);

void ecs_update(ecs_t* ecs, const float dt);

void ecs_draw(ecs_t* ecs);

void ecs_destroy_all_entities(ecs_t* ecs);

void ecs_destroy_all_entities_immediate(ecs_t* ecs);
