#include "debug.h"


void pk::debug_ecs(pk::ecs_t* ecs) {
	Vector2 player_pos{};
	ecs->camera->begin_drawing();
		for (const Rectangle& rect : ecs->collision.get_collisions()) {
			DrawRectangleLinesEx(rect, 2.0f, BLUE);
		}
		for (const pk::entity_t e : ecs->system->get_entities_from_component(pk::id::player)) {
			pk::player_t* p = (pk::player_t*) pk::ecs_get_component(e, pk::id::player);
			player_pos.x = p->collision_box.x + p->collision_box.width / 2.0f;
			player_pos.y = p->collision_box.y + p->collision_box.height;
			DrawRectangleLinesEx(p->collision_box, 2.0f, RED);
		}		
	ecs->camera->end_drawing();
	DrawText(TextFormat("Entities: %d", ecs->entity->size()), 20, 44, 20, LIME);
	DrawText(TextFormat("Collisions: %d", ecs->collision.size()), 20, 64, 20, LIME);
	DrawText(TextFormat("PlayerPos: %.2f, %.2f", player_pos.x, player_pos.y), 20, 84, 20, LIME);
	DrawText(TextFormat("Zoom: %.2f", ecs->camera->get_zoom()), 20, 104, 20, LIME);
}