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
	this->component[pk::id::character] = std::make_pair(
		(char*)malloc(sizeof(character_t) * pk::MAX_ENTITIES),
		sizeof(character_t)
	);
	this->component[pk::id::player] = std::make_pair(
		(char*)malloc(sizeof(player_t) * pk::MAX_ENTITIES),
		sizeof(player_t)
	);	
}


pk::ComponentManager::~ComponentManager() {
	int id = 0;
	for (auto& pair : this->component) {
		free(pair.first);
		printf("Deleting component array of id %d\n", id++);
	}
}


void* pk::ComponentManager::at(const pk::entity_t e, const pk::component_t id) {
	return this->component[id].first + this->component[id].second * e;
}