#include "SystemManager.h"
#include "../ECS.h"


void pk::sprite_animation_update(
	const float dt, 
	const pk::EntitySet& entities
) {
	for (const pk::entity_t e : entities) {
		pk::sprite_animation_t* s = (pk::sprite_animation_t*)pk::ecs_get_component(e, pk::id::sprite_animation);
		s->frame++;
		if (s->frame >= s->max_frame) {
			s->frame = 0;
			s->sprite = (s->sprite + 1) % s->max_sprite;
			s->rect.x = s->rect.width * s->sprite;
		}
	}
}


void pk::sprite_animation_draw(const pk::entity_t e) {
	const pk::transform_t* t = pk::ecs_get_transform(e);
	const pk::sprite_animation_t* s = (const pk::sprite_animation_t*)pk::ecs_get_component(e, pk::id::sprite_animation);
	DrawTextureRec(s->texture, s->rect, t->pos, WHITE);
}