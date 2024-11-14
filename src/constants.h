#pragma once
#include <raylib.h>
#include <cstddef>


namespace pk {

	constexpr float SCREEN_W{ 1280.0f };
	constexpr float SCREEN_H{ 720.0f };
	constexpr float SCREEN_CENTERX{ SCREEN_W / 2.0f };
	constexpr float SCREEN_CENTERY{ SCREEN_H / 2.0f };
	constexpr Vector2 SCREEN_SIZE{ SCREEN_W, SCREEN_H };
	constexpr Vector2 SCREEN_CENTER{ SCREEN_CENTERX, SCREEN_CENTERY };
	constexpr char WINDOW_TITLE[]{ "PokemonCPP" };
	constexpr int FPS{ 60 };


	constexpr std::size_t MAX_ENTITIES{ 4096 };

}

