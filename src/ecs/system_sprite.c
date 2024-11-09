#include "system_manager.h"
#include "ecs_manager.h"


void sprite_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_ecs();
	transform_t* t = ecs_get_transform(ecs, e);
	sprite_t* s = ecs_component_get(ecs, e, SPRITE_ID);
	DrawTextureV(*s->texture, t->pos, WHITE);
}