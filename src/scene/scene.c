#include "scene.h"

static scene_t scenes[NUM_SCENES];
static int current_scene = MAIN_SCENE;
static int next_scene = MAIN_SCENE;
static int should_change_scene = 0;


void scene_manager_init() {
	scenes[TITLE_SCREEN_ID].init = scene_title_screen_init;
	scenes[TITLE_SCREEN_ID].update = scene_title_screen_update;
	scenes[TITLE_SCREEN_ID].draw = scene_title_screen_draw;
	
	scenes[WORLD_SCENE_ID].init = scene_world_init;
	scenes[WORLD_SCENE_ID].update = scene_world_update;
	scenes[WORLD_SCENE_ID].draw = scene_world_draw;

	scenes[FIRE_ARENA_SCENE_ID].init = scene_fire_arena_init;
	scenes[FIRE_ARENA_SCENE_ID].update = scene_fire_arena_update;
	scenes[FIRE_ARENA_SCENE_ID].draw = scene_fire_arena_draw;

	scenes[PLANT_ARENA_SCENE_ID].init = scene_plant_arena_init;
	scenes[PLANT_ARENA_SCENE_ID].update = scene_plant_arena_update;
	scenes[PLANT_ARENA_SCENE_ID].draw = scene_plant_arena_draw;

	scenes[WATER_ARENA_SCENE_ID].init = scene_water_arena_init;
	scenes[WATER_ARENA_SCENE_ID].update = scene_water_arena_update;
	scenes[WATER_ARENA_SCENE_ID].draw = scene_water_arena_draw;

	scenes[HOSPITAL_SCENE_ID].init = scene_hospital_init;
	scenes[HOSPITAL_SCENE_ID].update = scene_hospital_update;
	scenes[HOSPITAL_SCENE_ID].draw = scene_hospital_draw;
	
	scenes[HOUSE_SCENE_ID].init = scene_house_init;
	scenes[HOUSE_SCENE_ID].update = scene_house_update;
	scenes[HOUSE_SCENE_ID].draw = scene_house_draw;
	
	scenes[TEST_SCENE_ID].init = scene_test_init;
	scenes[TEST_SCENE_ID].update = scene_test_update;
	scenes[TEST_SCENE_ID].draw = scene_test_draw;
	
	scenes[MAIN_SCENE].init();
}


void scene_manager_change_scene(const int scene_id) {
	next_scene = scene_id;
	should_change_scene = 1;
}


void scene_manager_update(const float dt) {
	scenes[current_scene].update(dt);
	if (should_change_scene) {
		should_change_scene = 0;
		current_scene = next_scene;
		scenes[current_scene].init();		
	}
}


void scene_manager_draw() {
	scenes[current_scene].draw();
}