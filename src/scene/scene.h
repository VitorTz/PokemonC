#pragma once
#include "../pokemon.h"
#include "../ecs/ecs_manager.h"


typedef struct scene {
	void (*init)();
	void (*update)(const float);
	void (*draw)();
} scene_t;


void scene_title_screen_init();
void scene_title_screen_update(const float dt);
void scene_title_screen_draw();
	 
void scene_world_init();
void scene_world_update(const float dt);
void scene_world_draw();

void scene_fire_arena_init();
void scene_fire_arena_update(const float dt);
void scene_fire_arena_draw();

void scene_water_arena_init();
void scene_water_arena_update(const float dt);
void scene_water_arena_draw();

void scene_plant_arena_init();
void scene_plant_arena_update(const float dt);
void scene_plant_arena_draw();

void scene_hospital_init();
void scene_hospital_update(const float dt);
void scene_hospital_draw();

void scene_house_init();
void scene_house_update(const float dt);
void scene_house_draw();

void scene_test_init();
void scene_test_update(const float dt);
void scene_test_draw();


void scene_manager_init();
void scene_manager_update(const float dt);
void scene_manager_change_scene(int scene_id);
void scene_manager_draw();