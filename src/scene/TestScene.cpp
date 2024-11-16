#include "Scene.h"


static std::unordered_map<pk::entity_t, float> speed{};


pk::TestScene::TestScene() {
	pk::ecs_create_instance(pk::TestSceneId);
	pk::ecs_set_instance(pk::TestSceneId);

	for (int i = 0; i < pk::MAX_ENTITIES; i++) {
		const pk::entity_t e = pk::ecs_create_sprite(0, GRAPHICS_PATH "icons/Atrox.png");
		pk::transform_t* t = pk::ecs_get_transform(e);
		t->pos.x = GetRandomValue(0, pk::SCREEN_W);
		t->pos.y = GetRandomValue(0, pk::SCREEN_H) - pk::SCREEN_H;
		speed[e] = GetRandomValue(20, 150);
	}
}


void pk::TestScene::update(const float dt) {
	pk::ecs_set_instance(pk::TestSceneId);
	pk::ecs_update(dt);
	pk::ecs_t* ecs = pk::ecs_get_instance(pk::TestSceneId);
	const std::unordered_set<pk::entity_t>& entities = ecs->system->get_entities_from_component(pk::id::sprite);
	for (const pk::entity_t e : entities) {
		pk::transform_t* t = pk::ecs_get_transform(e);
		t->pos.y += dt * speed[e];
		if (t->pos.y > pk::SCREEN_H) {
			pk::ecs_destroy_entity(e);
		}
	}
}


void pk::TestScene::draw() {
	pk::ecs_set_instance(pk::TestSceneId);
	pk::ecs_draw();
}