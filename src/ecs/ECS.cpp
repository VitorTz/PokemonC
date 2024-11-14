#include "ECS.h"


void pk::EcsManager::ecs_create(const pk::SceneID scene_id) {
	if (this->ecs_map.find(scene_id) == this->ecs_map.end()) {
		return;
	}
	this->ecs_map.emplace(scene_id, std::make_unique<pk::ecs_t>());
}


void pk::EcsManager::ecs_destroy(const pk::SceneID scene_id) {
	this->ecs_map.erase(scene_id);
}


void pk::EcsManager::ecs_set(const pk::SceneID scene_id) {
	assert(this->ecs_map.find(scene_id) != this->ecs_map.end());
	this->current_ecs = this->ecs_map[scene_id].get();
}


pk::transform_t* pk::EcsManager::get_transform(const pk::entity_t e) {
	return (pk::transform_t*)this->current_ecs->component.at(e, pk::id::transform);
}


pk::entity_t pk::EcsManager::entity_create(const pk::zindex_t zindex, const bool add_to_camera) {
	const pk::entity_t e = this->current_ecs->entity.create();
	transform_t* t = this->get_transform(e);
	t->zindex = zindex;
	if (add_to_camera) {
		this->current_ecs->camera.insert(e, zindex);
	}
	return e;
}


void pk::EcsManager::entity_destroy(const pk::entity_t e) {
	this->current_ecs->entities_to_destroy.push(e);
}


void pk::EcsManager::entity_destroy_all() {
	this->current_ecs->should_destroy_all_entities = true;
}


void* pk::EcsManager::component_get(const pk::entity_t e, const pk::component_t id) {
	return this->current_ecs->component.at(e, id);
}


void pk::EcsManager::update(const float dt) {
	this->current_ecs->system.update(dt);

	if (this->current_ecs->should_destroy_all_entities) {
		this->current_ecs->should_destroy_all_entities = false;
		this->current_ecs->entity.clear();
		this->current_ecs->system.clear();
		this->current_ecs->camera.clear();
		this->current_ecs->entities_to_destroy = std::queue<pk::entity_t>();
	}

	while (this->current_ecs->entities_to_destroy.empty() == false) {
		const pk::entity_t e = this->current_ecs->entities_to_destroy.front();
		this->current_ecs->entities_to_destroy.pop();
		this->current_ecs->camera.erase(e, this->get_transform(e)->zindex);
		this->current_ecs->entity.destroy(e);
		this->current_ecs->system.entity_destroy(e);
	}
}


void pk::EcsManager::draw() {
	this->current_ecs->camera.draw(
		&this->current_ecs->system,
		&this->current_ecs->component
	);
}