#include "util.h"


size_t hash_entity_t(const void* k) {
	const size_t i = *((entity_t*)k);
	return i;
}


size_t hash_zindex_t(const void* k) {
	const size_t i = *((zindex_t*)k);
	return i;
}

size_t hash_int(const void* k) {
	const size_t i = *((int*)k);
	return i;
}


size_t hash_component_t(const void* k) {
	const size_t i = *((component_t*)k);
	return i;
}


size_t hash_str(const void* s) {
	const char* str = (const char*)s;
	size_t h = 5381;
	int c;
	while ((c = *str++))
		h = ((h << 5) + h) + c;
	return h;	
}

int equal_entity_t(const void* l, const void* r) {
	return *((entity_t*)l) == *((entity_t*)r);
}


int equal_component_t(const void* l, const void* r) {
	return *((component_t*)l) == *((component_t*)r);
}


void init_random_utility() {
	srand(time(NULL));
}

int randint(const int start, const int end) {
	return start + rand() % (end - start);
}


float fclamp(const float value, const float min, const float max) {
	const float t = value < min ? min : value;
	return t > max ? max : t;
}


double dclamp(const double value, const double min, const double max) {
	const double t = value < min ? min : value;
	return t > max ? max : t;
}


Vector2 get_direction(
	int up,
	int down,
	int left,
	int right
) {
	Vector2 direction = { 0.0f, 0.0f };
	if (IsKeyDown(up)) {
		direction.y = -1.0f;
	}
	else if (IsKeyDown(down)) {
		direction.y = 1.0f;
	}
	if (IsKeyDown(left)) {
		direction.x = -1.0f;
	}
	else if (IsKeyDown(right)) {
		direction.x = 1.0f;
	}
	return Vector2Normalize(direction);
}


Vector2 get_center(transform_t* t) {
	Vector2 center = {
		t->pos.x + t->size.x / 2.0f,
		t->pos.y + t->size.y / 2.0f
	};
	return center;
}