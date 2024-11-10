#include "scene.h"


void scene_world_init() {
	ecs_manager_create(WORLD_SCENE_ID);
	ecs_manager_set_ecs(WORLD_SCENE_ID);
	ecs_t* ecs = ecs_manager_get_ecs();

	const entity_t e = ecs_entity_create(ecs, 0);
	sprite_t* s = ecs_component_allocate(ecs, e, SPRITE_ID);
	sprite_init(s, CHARACTERS_PATH "player.png");
}

void scene_world_update(const float dt) {
	ecs_manager_set_ecs(WORLD_SCENE_ID);
	ecs_t* ecs = ecs_manager_get_ecs();
	ecs_update(ecs, dt);
}

void scene_world_draw() {
	ecs_manager_set_ecs(WORLD_SCENE_ID);
	ecs_t* ecs = ecs_manager_get_ecs();
	ecs_draw(ecs);
}