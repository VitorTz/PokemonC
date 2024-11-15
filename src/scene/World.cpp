#include "Scene.h"


pk::WorldScene::WorldScene() {
	ecs_create_instance(pk::WorldSceneId);
	ecs_set_instance(pk::WorldSceneId);
	pk::ecs_create_sprite(0, MAPS_PATH "world.png");
	pk::ecs_create_player(Vector2{ 100.0f, 100.0f });	
}


void pk::WorldScene::update(const float dt) {
	ecs_set_instance(pk::WorldSceneId);
	ecs_update(dt);	
}


void pk::WorldScene::draw() {
	ecs_set_instance(pk::WorldSceneId);
	ecs_draw();
}