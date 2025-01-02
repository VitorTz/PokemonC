#include <raylib.h>
#include <raymath.h>
#include "system.h"
#include "ecs_manager.h"


void sprite_draw(const entity_t e) {	
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	const Sprite* sprite = (Sprite*)ecs_get_component(ecs, e, SPRITE_ID);
	const EntityTransform* transform = ecs_get_transform(ecs, e);
	DrawTextureV(*sprite->texture, transform->pos, WHITE);
}


void sprite_animation_update(SetIterator* iter, const float dt) {
	EntityPair* pair = NULL;
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	while ((pair = (EntityPair*)set_iter_next(iter)) != NULL) {
		SpriteAnimation* sprite_animation = (SpriteAnimation*)ecs_get_component(ecs, pair->entity, SPRITE_ANIMATION_ID);
		sprite_animation->current_frame++;
		if (sprite_animation->current_frame > sprite_animation->max_frame) {
			sprite_animation->current_frame = 0;
			sprite_animation->current_sprite = (sprite_animation->current_sprite + 1) % sprite_animation->max_sprite;
			sprite_animation->texture_rect.x = (sprite_animation->current_sprite / sprite_animation->cols) * sprite_animation->texture_rect.width;
			sprite_animation->texture_rect.y = (sprite_animation->current_sprite % sprite_animation->cols) * sprite_animation->texture_rect.height;
		}
	}
}

void sprite_animation_draw(const entity_t e) {
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	const EntityTransform* transform = ecs_get_transform(ecs, e);
	const SpriteAnimation* sprite_animation = (SpriteAnimation*)ecs_get_component(ecs, e, SPRITE_ANIMATION_ID);
	DrawTextureRec(
		*sprite_animation->texture, 
		sprite_animation->texture_rect, 
		transform->pos, 
		WHITE
	);
}

void shadow_draw(const entity_t e) {
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	const EntityTransform* transform = ecs_get_transform(ecs, e);
	const Shadow* shadow = (Shadow*)ecs_get_component(ecs, e, SHADOW_ID);	
	DrawTextureV(*shadow->sprite.texture, Vector2Add(transform->pos, shadow->offset), WHITE);
}
