#pragma once
#include <cassert>
#include <unordered_map>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "Camera.h"
#include "../scene/SceneId.h"


namespace pk {

	typedef struct ecs {
		pk::EntityManager entity{};
		pk::ComponentManager component{};
		std::queue<pk::entity_t> entities_to_destroy{};
		bool should_destroy_all_entities{ false };	
		pk::Camera camera{};
		pk::SystemManager system{};
	} ecs_t;	

	class EcsManager {

	private:
		std::unordered_map<pk::SceneID, std::unique_ptr<pk::ecs_t>> ecs_map{};
		pk::ecs_t* current_ecs{};

	public:
		void ecs_create(pk::SceneID scene_id);

		void ecs_destroy(pk::SceneID scene_id);

		void ecs_set(pk::SceneID scene_od);

		pk::entity_t entity_create(pk::zindex_t zindex, bool add_to_camera);

		void entity_destroy(pk::entity_t e);

		void entity_destroy_all();

		void* component_get(pk::entity_t e, pk::component_t id);

		transform_t* get_transform(pk::entity_t e);

		void update(float dt);

		void draw();

	};

}