#include "SystemManager.h"
#include "../ECS.h"


void pk::player_update(const float dt, const pk::EntitySet& entities) {
	pk::ecs_t* ecs = pk::ecs_get_current_instance();

	for (const pk::entity_t e : entities) {
		pk::player_t* player = (pk::player_t*)pk::ecs_get_component(e, pk::id::player);
		pk::transform_t* player_transform = pk::ecs_get_transform(e);
		pk::character_t* character = (pk::character_t*)pk::ecs_get_component(e, pk::id::character);
		pk::sprite_animation_t* sprite_animation = (pk::sprite_animation_t*)pk::ecs_get_component(e, pk::id::sprite_animation);
		pk::transform_t* shadow_transform = pk::ecs_get_transform(player->shadow_entity);

		// Movement
			Vector2 direction = pk::get_direction(pk::LEFT_KEY, pk::RIGHT_KEY, pk::UP_KEY, pk::DOWN_KEY, character->mov_state);
		
			// Horizontal Movement
			player_transform->pos.x += dt * direction.x * pk::PLAYER_SPEED;
			player->collision_box.x = player_transform->pos.x + player_transform->size.x / 2.0f - player->collision_box.width / 2.0f;
			player->collision_box.y = player_transform->pos.y + player_transform->size.y - player->collision_box.height;
			if (pk::ecs_check_collision(player->collision_box)) {
				player_transform->pos.x -= dt * direction.x * pk::PLAYER_SPEED;
			}
		
			// Vertical Movement
			player_transform->pos.y += dt * direction.y * pk::PLAYER_SPEED;
			player->collision_box.x = player_transform->pos.x + player_transform->size.x / 2.0f - player->collision_box.width / 2.0f;
			player->collision_box.y = player_transform->pos.y + player_transform->size.y - player->collision_box.height;
			if (pk::ecs_check_collision(player->collision_box)) {
				player_transform->pos.y -= dt * direction.y * pk::PLAYER_SPEED;
			}
			
			// Shadow Pos
			shadow_transform->pos.x = player_transform->pos.x + player_transform->size.x / 2.0f - shadow_transform->size.x / 2.0f;
			shadow_transform->pos.y = player_transform->pos.y + player_transform->size.y - shadow_transform->size.y;

			// Camera Center
			ecs->camera->set_target(
				player_transform->pos.x + player_transform->size.x / 2.0f,
				player_transform->pos.y + player_transform->size.y / 2.0f
			);
		
		// Sprite Animation
			if (character->mov_state.is_idle) {
				sprite_animation->rect.x = 0.0f;
			}
	
			if (character->mov_state.last_is_idle != character->mov_state.is_idle) {
				sprite_animation->rect.x = pk::PLAYER_SIZE.x;
			}

			switch (character->mov_state.direction) {
				case 'u':
					sprite_animation->rect.y = pk::PLAYER_SIZE.y * 3;
					break;
				case 'd':
					sprite_animation->rect.y = 0.0f;
					break;
				case 'l':
					sprite_animation->rect.y = pk::PLAYER_SIZE.y;
					break;
				case 'r':
					sprite_animation->rect.y = pk::PLAYER_SIZE.y * 2;
					break;
				default:
					break;
			}
	}
}