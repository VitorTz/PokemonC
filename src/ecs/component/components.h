#pragma once
#include "../../pokemon.h"


namespace pk {

	namespace id {
		constexpr pk::component_t transform{ 0 };
		constexpr pk::component_t sprite{ 1 };
		constexpr pk::component_t sprite_animation{ 2 };
		constexpr pk::component_t character{ 3 };
		constexpr pk::component_t player{ 4 };
	}

	constexpr std::size_t NUM_COMPONENTS{ 5 };
	constexpr std::size_t NUM_UPDATABLE_COMPONENTS{ 2 };
	constexpr std::size_t NUM_DRAWABLE_COMPONENTS{ 2 };		
	constexpr std::array<pk::component_t, pk::NUM_UPDATABLE_COMPONENTS> SYSTEM_UPDATE_ORDER{
		pk::id::sprite_animation,
		pk::id::player
	};

	void components_init();
	bool is_drawable_component(pk::component_t id);

	typedef struct transform {
		Vector2 pos{};
		Vector2 size{};
		pk::zindex_t zindex{};
		transform() = default;
		explicit transform(const pk::zindex_t z) : zindex(z) { }
	} transform_t;

	typedef struct sprite {
		Texture2D texture{};
		sprite() = default;
		explicit sprite(const char* path) : texture(pk::texture_pool_get(path)) { }
	} sprite_t;

	typedef struct sprite_animation {
		Texture2D texture{};
		Rectangle rect{};
		std::uint8_t frame{};
		std::uint8_t max_frame{};
		std::uint8_t sprite{};
		std::uint8_t max_sprite{};
		sprite_animation() = default;
		sprite_animation(
			const char* path,
			const float width,
			const float height,
			const std::uint8_t speed
		) : texture(pk::texture_pool_get(path)),
		    rect({0.0f, 0.0f, width, height}),
		    max_frame(speed),
		    max_sprite((float) texture.width / width) { }
		explicit sprite_animation(
			const pk::sprite_animation_info_t& info
		) : sprite_animation(info.path, info.width, info.height, info.speed) { }
	} sprite_animation_t;

	typedef struct character {
		pk::CharacterID id{};
		pk::move_state_t mov_state{};
		character() = default;
		explicit character(const pk::CharacterID id) : id(id) { }
		character(
			const pk::CharacterID id, 
			const char direction
		) : id(id), mov_state(direction) { }
	} character_t;

	typedef struct player {
		pk::entity_t shadow_entity{};
		Rectangle collision_box{0.0f, 0.0f, pk::PLAYER_COLLISION_WIDTH, pk::PLAYER_COLLISION_HEIGHT};
		explicit pk::player(const pk::entity_t shadow_entity) : shadow_entity(shadow_entity) { }
	} player_t;

}
