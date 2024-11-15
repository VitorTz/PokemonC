#include "ECS.h"
#include "../util/debug.h"


static std::unordered_map<pk::SceneID, std::unique_ptr<pk::ecs_t>> ecs_map{};
static pk::ecs_t* mecs;


void pk::ecs_create_instance(const pk::SceneID scene_id) {
	if (ecs_map.find(scene_id) != ecs_map.end()) {
		return;
	}
	ecs_map.emplace(scene_id, std::make_unique<pk::ecs_t>());
	pk::ecs_t* ecs = ecs_map[scene_id].get();
	const pk::map_info_t& map_info = pk::MAP_INFO[scene_id];

	std::printf("Loading map %s\n", map_info.name);	
}


void pk::ecs_destroy_instance(const pk::SceneID scene_id) {
	ecs_map.erase(scene_id);
}


void pk::ecs_destroy_all_instances() {
	for (int i = 0; i < pk::NumScenes; i++) {
		if (ecs_map.find((pk::SceneID) i) != ecs_map.end()) {
			const pk::map_info_t& map = pk::MAP_INFO[i];
			printf("Deleting ecs instance %s map\n", map.name);
			ecs_map.erase((pk::SceneID)i);
		}
	}
}


pk::ecs_t* pk::ecs_get_instance(pk::SceneID scene_id) {
	assert(ecs_map.find(scene_id) != ecs_map.end());
	return ecs_map[scene_id].get();
}


pk::ecs_t* pk::ecs_get_current_instance() {
	return mecs;
}


void pk::ecs_set_instance(const pk::SceneID scene_id) {
	assert(ecs_map.find(scene_id) != ecs_map.end());
	mecs = ecs_map[scene_id].get();
}


pk::entity_t pk::ecs_create_entity(const pk::zindex_t zindex, const bool add_to_camera) {
	const pk::entity_t e = mecs->entity.create();
	pk::transform_t* t = ecs_get_transform(e);
	*t = pk::transform_t{ zindex };
	if (add_to_camera) {
		mecs->camera.insert(e, zindex);
	}
	return e;
}


pk::entity_t pk::ecs_create_sprite(pk::zindex_t zindex, const char* path) {
	const pk::entity_t e = pk::ecs_create_entity(zindex, true);
	pk::transform_t* t = (pk::transform_t*)pk::ecs_get_transform(e);
	pk::sprite_t* s = (pk::sprite_t*)pk::ecs_add_component(e, pk::id::sprite);
	*s = pk::sprite_t{ path };
	t->size.x = (float)s->texture.width;
	t->size.y = (float)s->texture.height;
	return e;
}


pk::entity_t pk::ecs_create_player(const Vector2 player_pos) {
	const pk::entity_t e = pk::ecs_create_entity(pk::CAMERA_ZINDEX_OBJECTS, true);
	const pk::entity_t shadow_entity = pk::ecs_create_sprite(pk::CAMERA_ZINDEX_SHADOW, GRAPHICS_PATH "other/shadow.png");

	// Sprite Animation
	pk::sprite_animation_t* s = (pk::sprite_animation_t*)pk::ecs_add_component(e, pk::id::sprite_animation);
	*s = pk::sprite_animation_t{ pk::SPRITE_ANI_INFO[pk::CharacterID::PlayerID] };

	// Character
	pk::character_t* c = (pk::character_t*)pk::ecs_add_component(e, pk::id::character);
	*c = pk::character_t{ pk::CharacterID::PlayerID };
	
	// Player
	pk::player_t* p = (pk::player_t*)pk::ecs_add_component(e, pk::id::player);
	*p = pk::player_t{ shadow_entity };

	// Player Transform
	pk::transform_t* t = pk::ecs_get_transform(e);
	t->pos = player_pos;
	t->size = pk::PLAYER_SIZE;

	return e;
}


void pk::ecs_destroy_entity(const pk::entity_t e) {
	mecs->entities_to_destroy.push(e);
}


void pk::ecs_destroy_all_entities() {
	mecs->should_destroy_all_entities = true;
}


void* pk::ecs_get_component(const pk::entity_t e, const pk::component_t id) {
	return mecs->component.at(e, id);
}


void* pk::ecs_add_component(pk::entity_t e, pk::component_t id) {
	mecs->system.insert(e, id);
	return mecs->component.at(e, id);
}


pk::transform_t* pk::ecs_get_transform(const pk::entity_t e) {
	return (pk::transform_t*)mecs->component.at(e, pk::id::transform);
}


bool pk::ecs_check_collision(const Rectangle& rect) {
	return mecs->collision.check(rect);
}


void pk::ecs_update(const float dt) {
	mecs->camera.handle_input(dt);
	mecs->system.update(dt);

	if (mecs->should_destroy_all_entities == true) {
		mecs->should_destroy_all_entities = false;
		mecs->camera.clear();
		mecs->entity.clear();
		mecs->system.clear();
		mecs->entities_to_destroy = std::queue<pk::entity_t>();
	}

	while (mecs->entities_to_destroy.empty() == false) {
		const pk::entity_t e = mecs->entities_to_destroy.front();
		mecs->entities_to_destroy.pop();
		mecs->camera.erase(e, ecs_get_transform(e)->zindex);
		mecs->entity.destroy(e);
		mecs->system.entity_destroy(e);
	}
}


void pk::ecs_draw() {
	mecs->camera.begin_drawing();
		mecs->camera.draw(&mecs->system, &mecs->component);
	mecs->camera.end_drawing();
	if (pk::DEBUG_MODE) {
		DrawFPS(20, 20);
		pk::debug_ecs(mecs);		
	}
}