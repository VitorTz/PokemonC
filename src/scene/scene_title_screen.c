#include "scene.h"

static image_t background_image;
static image_t logo;
static image_t press_start;


void scene_title_screen_init() {
	image_init(&background_image, BACKGROUNDS_PATH "title-screen-bg.png");	
}

void scene_title_screen_update(const float dt) {
	if (IsKeyPressed(KEY_SPACE)) {
		scene_manager_change_scene(WORLD_SCENE_ID);
	}
	
}

void scene_title_screen_draw() {
	image_draw(&background_image);	
}