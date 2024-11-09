#include "components.h"


void transform_init(transform_t* t, const zindex_t z) {
	t->pos = (Vector2){ 0.0f, 0.0f };
	t->size = (Vector2){ 0.0f, 0.0f };
	t->zindex = z;
}


void sprite_init(sprite_t* s, const char* file_name) {
	s->texture = texture_pool_get(file_name);
}


void sprite_animation_init(
	sprite_animation_t* sprite_animation,
	const char* file_name,
	float width,
	float height,
	uint8_t speed
) {
	sprite_animation->texture = texture_pool_get(file_name);
	sprite_animation->rect = (Rectangle){ 0.0f, 0.0f, width, height };
	sprite_animation->current_frame = 0;
	sprite_animation->max_frame = speed;
	sprite_animation->current_sprite_index = 0;
	sprite_animation->max_sprite_index = (float) sprite_animation->texture->width / width;
}