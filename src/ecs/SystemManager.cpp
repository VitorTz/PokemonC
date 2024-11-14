#include "SystemManager.h"


static const std::array<pk::component_t, pk::NUM_UPDATABLE_COMPONENTS> UPDATE_ORDER = {
	pk::id::sprite_animation
};

static const std::bitset<pk::NUM_COMPONENTS> DRAWABLE_COMP_BITSET{ "011" };


pk::SystemManager::SystemManager() {
	this->system[pk::id::transform] = { NULL, NULL };
	this->system[pk::id::sprite] = { NULL, pk::sprite_draw };
	this->system[pk::id::sprite_animation] = { pk::sprite_animation_update, pk::sprite_animation_draw};	
}


void pk::SystemManager::insert(const pk::entity_t e, const pk::component_t id) {
	this->entities[id].insert(e);
	if (DRAWABLE_COMP_BITSET[id]) {
		pk::drawable_comp_arr_t& arr = this->drawable_components[e];
		arr.comps[arr.size++] = id;
	}
}


void pk::SystemManager::entity_destroy(const pk::entity_t e) {
	this->drawable_components[e].size = 0;	
	for (std::unordered_set<pk::entity_t>& set : this->entities) {
		set.erase(e);
	}
}


void pk::SystemManager::update(const float dt) {
	for (const pk::component_t id : UPDATE_ORDER) {
		this->system[id].update(dt, this->entities[id]);
	}	
}


void pk::SystemManager::draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
	for (const auto& pair : entities) {
		pk::drawable_comp_arr_t& arr = this->drawable_components[pair.second];
		for (pk::component_t i = 0; i < arr.size; i++) {
			this->system[arr.comps[i]].draw(pair.second);
		}		
	}
}


void pk::SystemManager::clear() {
	for (std::unordered_set<pk::entity_t>& set : this->entities) {
		set.clear();
	}
	for (pk::drawable_comp_arr_t& arr : this->drawable_components) {
		arr.size = 0;
	}	
}