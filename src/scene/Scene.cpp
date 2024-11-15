#include "Scene.h"


static std::unique_ptr<pk::Scene> scene{nullptr};
static pk::SceneID current_scene{ pk::MAIN_SCENE };
static pk::SceneID next_scene{ pk::MAIN_SCENE};
static bool should_change_scene = false;


static void load_next_scene() {
	switch (next_scene) {
		case pk::TitleScreenId:
			scene = std::make_unique<pk::TitleScreen>();
			break;
		case pk::WorldSceneId:
			scene = std::make_unique<pk::WorldScene>();
			break;
		case pk::FireArenaSceneId:
			scene = std::make_unique<pk::FireArenaScene>();
			break;
		case pk::WaterAreanaSceneId:
			scene = std::make_unique<pk::WaterArenaScene>();
			break;
		case pk::PlantArenaSceneId:
			scene = std::make_unique<pk::PlantArenaScene>();
			break;
		case pk::HospitalSceneId:
			scene = std::make_unique<pk::HospitalScene>();
			break;
		case pk::HouseSceneId:
			scene = std::make_unique<pk::HouseScene>();
			break;
		case pk::TestSceneId:
			scene = std::make_unique<pk::TestScene>();
			break;		
		default:
			break;
	}
	current_scene = next_scene;
}


void pk::scene_init() {
	load_next_scene();
}


void pk::scene_change_scene(const pk::SceneID scene_id) {
	next_scene = scene_id;
	should_change_scene = true;
}


void pk::scene_update(const float dt) {
	scene->update(dt);
	if (should_change_scene == true) {
		should_change_scene = false;
		load_next_scene();
	}
}


void pk::scene_draw() {
	scene->draw();
}