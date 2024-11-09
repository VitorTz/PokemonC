#include "system_manager.h"
#include "ecs_manager.h"


void sprite_animation_update(const float dt, const entity_t e) {
	ecs_t* ecs = ecs_manager_get_ecs();
	sprite_animation_t* s = (sprite_animation_t*)ecs_component_get(ecs, e, SPRITE_ANIMATION_ID);
	s->current_frame++;
	if (s->current_frame >= s->max_frame) {
		s->current_sprite_index = (s->current_sprite_index + 1) % s->max_sprite_index;
		s->rect.x = s->rect.width * s->current_sprite_index;
	}
}


void sprite_animation_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_ecs();
	sprite_animation_t* s = (sprite_animation_t*) ecs_component_get(ecs, e, SPRITE_ANIMATION_ID);
	transform_t* t = ecs_get_transform(ecs, e);
	DrawTextureRec(*s->texture, s->rect, t->pos, WHITE);
}