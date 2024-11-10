#include "scene.h"



static entity_t player_e;
static entity_t enemy_e;


void scene_test_init() {	
	ecs_manager_create(TEST_SCENE_ID);
	ecs_manager_set_ecs(TEST_SCENE_ID);
	ecs_t* ecs = ecs_manager_get_ecs();

	ecs_sprite_create(ecs, CAMERA_ZINDEX_TERRAIN, BACKGROUNDS_PATH "world.png");
	player_e = ecs_sprite_create(ecs, CAMERA_ZINDEX_OBJECTS, ICONS_PATH "Atrox.png");
	enemy_e = ecs_sprite_create(ecs, CAMERA_ZINDEX_OBJECTS, ICONS_PATH "Cleaf.png");	
}

void scene_test_update(const float dt) {
	ecs_manager_set_ecs(TEST_SCENE_ID);
	ecs_t* ecs = ecs_manager_get_ecs();
	transform_t* player_transform = ecs_get_transform(ecs, player_e);
	transform_t* enemy_transform = ecs_get_transform(ecs, enemy_e);

	Vector2 direction;

	direction = get_direction(KEY_W, KEY_S, KEY_A, KEY_D);
	player_transform->pos.x += dt * direction.x * 150.0f;
	player_transform->pos.y += dt * direction.y * 150.0f;

	direction = get_direction(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
	enemy_transform->pos.x += dt * direction.x * 150.0f;
	enemy_transform->pos.y += dt * direction.y * 150.0f;
	
	camera_set_target(
		&ecs->camera,
		get_center(player_transform)		
	);
	ecs_update(ecs, dt);	
}

void scene_test_draw() {
	ecs_manager_set_ecs(TEST_SCENE_ID);
	ecs_t* ecs = ecs_manager_get_ecs();
	ecs_draw(ecs);
}