#pragma once
#include "../util/texture_pool.h"
#include "../util/types.h"


typedef struct transform {
	Vector2 pos;
	Vector2 size;
	zindex_t zindex;
} transform_t;


typedef struct sprite {
	Texture2D* texture;
} sprite_t;


typedef struct sprite_animation {
	Texture2D* texture;
	Rectangle rect;
	uint8_t current_frame;
	uint8_t max_frame;
	uint8_t current_sprite_index;
	uint8_t max_sprite_index;
} sprite_animation_t;


void transform_init(transform_t* t, zindex_t zindex);
void sprite_init(sprite_t* sprite, const char* file_name);
void sprite_animation_init(
	sprite_animation_t* sprite_animation,
	const char* file_name,
	float width,
	float height,
	uint8_t speed
);