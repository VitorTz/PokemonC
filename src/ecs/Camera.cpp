#include "Camera.h"


pk::Camera::Camera() {
	this->camera = {
		pk::SCREEN_CENTER,
		pk::SCREEN_CENTER,
		0.0f,
		1.0f
	};
}


void pk::Camera::begin_drawing() {
	BeginMode2D(this->camera);
}


void pk::Camera::end_drawing() {
	EndMode2D();
}


void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
	assert(zindex >= pk::CAMERA_ZINDEX_MIN && zindex <= pk::CAMERA_ZINDEX_MAX);
	if (this->is_on_camera[e] == false) {
		this->is_on_camera[e] = true;
		auto& v = this->entities[zindex];
		v.push_back({ 0.0f, e });
		this->m_size++;
	}
}


void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
	assert(zindex >= pk::CAMERA_ZINDEX_MIN && zindex <= pk::CAMERA_ZINDEX_MAX);
	if (this->is_on_camera[e] == true) {
		this->is_on_camera[e] = false;
		auto& v = this->entities[zindex];
		for (std::size_t i = 0; i < v.size(); i++) {
			if (v[i].second == e) {
				std::swap(v[i], v.back());
				v.pop_back();
				this->m_size--;
				return;
			}
		}		
	}
}


void pk::Camera::draw(
	pk::SystemManager* system_manager,
	pk::ComponentManager* component_manager
) {
	for (std::vector<std::pair<float, pk::entity_t>>& vec : this->entities) {
		for (std::pair<float, pk::entity_t>& pair : vec) {
			pk::transform_t* t = (pk::transform_t*) component_manager->at(pair.second, pk::id::transform);
			pair.first = t->pos.y + t->size.y / 2.0f;
		}
		std::sort(vec.begin(), vec.end());
		system_manager->draw(vec);
	}
}


void pk::Camera::clear() {
	for (auto& vec : this->entities) {
		vec.clear();
	}
	for (bool& b : this->is_on_camera) {
		b = false;
	}
}


std::size_t pk::Camera::size() const {
	return this->m_size;
}