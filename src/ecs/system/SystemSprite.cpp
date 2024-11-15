#include "SystemManager.h"
#include "../ECS.h"


void pk::sprite_draw(const pk::entity_t e) {
	const pk::transform_t* t = pk::ecs_get_transform(e);
	const pk::sprite_t* s = (const pk::sprite_t*)pk::ecs_get_component(e, pk::id::sprite);
	DrawTextureV(s->texture, t->pos, WHITE);
}