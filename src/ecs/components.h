#pragma once
#include <raylib.h>
#include <cstddef>
#include <array>
#include "../util/types.h"


namespace pk {

	constexpr std::size_t NUM_COMPONENTS{ 3 };
	constexpr std::size_t NUM_UPDATABLE_COMPONENTS{ 1 };
	constexpr std::size_t NUM_DRAWABLE_COMPONENTS{ 2 };	

	namespace id {
		constexpr pk::component_t transform{ 0 };
		constexpr pk::component_t sprite{ 1 };
		constexpr pk::component_t sprite_animation{ 2 };
	}

	typedef struct transform {
		Vector2 pos{};
		Vector2 size{};
		pk::zindex_t zindex{};
	} transform_t;

	typedef struct sprite {
		Texture2D texture{};
	} sprite_t;

	typedef struct sprite_animation {
		Texture2D texture{};
		Rectangle rect{};
		std::uint8_t frame{};
		std::uint8_t max_frame{};
		std::uint8_t sprite{};
		std::uint8_t max_sprite{};
	} sprite_animation_t;

}
