#pragma once
#include "../constants.h"
#include "components.h"
#include <unordered_set>
#include <memory>
#include <vector>
#include <array>
#include <bitset>


namespace pk {

	typedef struct drawable_comp_arr {
		pk::component_t size;
		pk::component_t comps[pk::NUM_DRAWABLE_COMPONENTS];
	} drawable_comp_arr_t;

	typedef struct system {
		void (*update)(const float, const std::unordered_set<pk::entity_t>&);
		void (*draw)(const pk::entity_t e);
	} system_t;

	void sprite_draw(const pk::entity_t e);
	void sprite_animation_update(const float dt, const std::unordered_set<pk::entity_t>& entities);
	void sprite_animation_draw(const pk::entity_t e);

	class SystemManager {

	private:
		std::array<pk::system_t, pk::NUM_COMPONENTS> system;
		std::array<std::unordered_set<pk::entity_t>, pk::NUM_COMPONENTS> entities{};		
		std::array<pk::drawable_comp_arr_t, pk::MAX_ENTITIES> drawable_components{};

	public:
		SystemManager();
		void insert(pk::entity_t e, pk::component_t id);
		void entity_destroy(pk::entity_t e);
		void update(float dt);
		void draw(const std::vector<std::pair<float, pk::entity_t>>& entities);
		void clear();

	};

}