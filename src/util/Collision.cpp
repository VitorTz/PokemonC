#include "Collision.h"


pk::Collision::Collision() {
	this->collisions.reserve(1024);
}


void pk::Collision::insert(Rectangle rect) {
	this->collisions.emplace_back(rect);
}


bool pk::Collision::check(const Rectangle& rect) {
	return std::any_of(
		this->collisions.begin(),
		this->collisions.end(),
		[rect](const Rectangle& other) {
			return CheckCollisionRecs(rect, other);
		}
	);
}


const std::vector<Rectangle>& pk::Collision::get_collisions() const {
	return this->collisions;
}


void pk::Collision::clear() {
	this->collisions.clear();
}


std::size_t pk::Collision::size() const {
	return this->collisions.size();
}