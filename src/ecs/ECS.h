#pragma once
#include "../pokemon.h"
#include "entity/EntityManager.h"
#include "component/ComponentManager.h"
#include "system/SystemManager.h"
#include "../util/Collision.h"
#include "../util/Camera.h"


namespace pk {

	class ecs_t {

	public:
		pk::SceneID scene_id;
		std::unique_ptr<pk::EntityManager> entity{};
		std::unique_ptr<pk::ComponentManager> component{};
		std::unique_ptr<pk::SystemManager> system{};
		std::unique_ptr<pk::Camera> camera{};
		pk::Collision collision{};
		std::queue<pk::entity_t> entities_to_destroy{};
		bool should_destroy_all_entities{ false };

	public:
		explicit ecs_t(
			const pk::SceneID scene_id
		) : scene_id(scene_id),
			entity(std::make_unique<pk::EntityManager>()),
			component(std::make_unique<pk::ComponentManager>()),
			system(std::make_unique<pk::SystemManager>()),
			camera(std::make_unique<pk::Camera>(scene_id)) { }

	};

	void ecs_create_instance(pk::SceneID scene_id);
	void ecs_destroy_instance(pk::SceneID scene_id);
	void ecs_destroy_all_instances();
	
	pk::ecs_t* ecs_get_instance(pk::SceneID scene_id);
	pk::ecs_t* ecs_get_current_instance();
	void ecs_set_instance(pk::SceneID scene_id);

	pk::entity_t ecs_create_entity(pk::zindex_t zindex, bool add_to_camera);
	pk::entity_t ecs_create_sprite(pk::zindex_t zindex, const char* path);		
	pk::entity_t ecs_create_player(Vector2 pos);

	void ecs_destroy_entity(pk::entity_t e);
	void ecs_destroy_all_entities();

	bool ecs_check_collision(const Rectangle& rect);
	
	void* ecs_add_component(pk::entity_t e, pk::component_t id);
	void* ecs_get_component(pk::entity_t e, pk::component_t id);
	transform_t* ecs_get_transform(pk::entity_t e);

	void ecs_update(float dt);
	void ecs_draw();

}