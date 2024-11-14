#pragma once
#include <raylib.h>
#include "util/types.h"


namespace pk {

	// Window
	constexpr float SCREEN_W{ 1280.0f };
	constexpr float SCREEN_H{ 720.0f };
	constexpr float SCREEN_CENTERX{ SCREEN_W / 2.0f };
	constexpr float SCREEN_CENTERY{ SCREEN_H / 2.0f };
	constexpr Vector2 SCREEN_SIZE{ SCREEN_W, SCREEN_H };
	constexpr Vector2 SCREEN_CENTER{ SCREEN_CENTERX, SCREEN_CENTERY };
	constexpr int FPS{ 60 };
	constexpr char WINDOW_TITLE[]{ "PokemonCPP" };

	// Game
	constexpr pk::entity_t MAX_ENTITIES{ 4096 };

	// Camera
	constexpr pk::zindex_t CAMERA_ZINDEX_MIN{ 0 };
	constexpr pk::zindex_t CAMERA_ZINDEX_TERRAIN{ 0 };
	constexpr pk::zindex_t CAMERA_ZINDEX_WATER{ 1 };
	constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{ 2 };
	constexpr pk::zindex_t CAMERA_ZINDEX_OBJECTS{ 3 };
	constexpr pk::zindex_t CAMERA_ZINDEX_TOP{ 4 };
	constexpr pk::zindex_t CAMERA_ZINDEX_SKY{ 5 };
	constexpr pk::zindex_t CAMERA_ZINDEX_MAX{ 5 };

}
