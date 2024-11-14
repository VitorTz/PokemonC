#include "ComponentManager.h"


pk::ComponentManager::ComponentManager() {
	this->component[pk::id::transform] = std::make_pair(
		(char*)malloc(sizeof(transform_t) * pk::MAX_ENTITIES),
		sizeof(transform_t)
	);
	this->component[pk::id::sprite] = std::make_pair(
		(char*)malloc(sizeof(sprite_t) * pk::MAX_ENTITIES),
		sizeof(sprite_t)
	);
	this->component[pk::id::sprite_animation] = std::make_pair(
		(char*)malloc(sizeof(sprite_animation_t) * pk::MAX_ENTITIES),
		sizeof(sprite_animation_t)
	);
}

pk::ComponentManager::~ComponentManager() {
	for (auto& pair : this->component)
		free(pair.first);
}

void* pk::ComponentManager::at(const pk::entity_t e, const pk::component_t id) {
	return this->component[id].first + this->component[id].second * e;
}