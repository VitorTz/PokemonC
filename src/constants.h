#pragma once
#include <raylib.h>
#include <array>
#include "util/types.h"


#define ASSETS_PATH "./resources/"
#define GRAPHICS_PATH "./resources/graphics/"
#define CHARACTERS_PATH "./resources/graphics/characters/"
#define MAPS_PATH "./resources/data/maps/"


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
	constexpr pk::SceneID MAIN_SCENE{ pk::WorldSceneId };
	constexpr pk::entity_t MAX_ENTITIES{ 4096 };
	constexpr bool DEBUG_MODE{ true };

	constexpr int UP_KEY{ KEY_W };
	constexpr int DOWN_KEY{ KEY_S };
	constexpr int LEFT_KEY{ KEY_A };
	constexpr int RIGHT_KEY{ KEY_D };

	// Player
	constexpr Vector2 PLAYER_SIZE{ 128.0f, 128.0f };
	constexpr float PLAYER_SPEED{ 150.0f };
	constexpr float PLAYER_COLLISION_WIDTH{ pk::PLAYER_SIZE.x * 0.35f };
	constexpr float PLAYER_COLLISION_HEIGHT{ pk::PLAYER_SIZE.y * 0.4f };

	// Sprite Animation

	constexpr std::uint8_t ANIMATION_SPEED_SLOW{ 12 };
	constexpr std::uint8_t ANIMATION_SPEED_NORMAL{ 8 };
	constexpr std::uint8_t ANIMATION_SPEED_FAST{ 4 };

	constexpr std::array<pk::sprite_animation_info_t, pk::NumCharacters> SPRITE_ANI_INFO = {
		pk::sprite_animation_info_t{CHARACTERS_PATH "player.png", 128.0, 128.0f, pk::ANIMATION_SPEED_NORMAL},
		pk::sprite_animation_info_t{CHARACTERS_PATH "purple_girl.png", 128.0, 128.0f, pk::ANIMATION_SPEED_NORMAL}	
	};

	// Camera
	constexpr pk::zindex_t CAMERA_ZINDEX_MIN{ 0 };
	constexpr pk::zindex_t CAMERA_ZINDEX_TERRAIN{ 0 };
	constexpr pk::zindex_t CAMERA_ZINDEX_WATER{ 1 };
	constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{ 2 };
	constexpr pk::zindex_t CAMERA_ZINDEX_OBJECTS{ 3 };
	constexpr pk::zindex_t CAMERA_ZINDEX_TOP{ 4 };
	constexpr pk::zindex_t CAMERA_ZINDEX_SKY{ 5 };
	constexpr pk::zindex_t CAMERA_ZINDEX_MAX{ 5 };
	constexpr float CAMERA_ZOOM_MIN{ 0.5f };
	constexpr float CAMERA_ZOOM_MAX{ 2.5f };

	// Maps
	constexpr std::array<pk::map_info_t, pk::NumScenes> MAP_INFO{
		pk::map_info_t{"TitleScreen", "none", "none", 0.0f, 0.0f }, // TitleScreen
		pk::map_info_t{ "World", MAPS_PATH "world.png", MAPS_PATH "world.tmx", 5504.0f, 5504.0f }, // World
		pk::map_info_t{ "FireArena", MAPS_PATH "fire.png", MAPS_PATH "fire.tmx", 5504.0f, 5504.0f },  // FireArena
		pk::map_info_t{ "WaterArena", MAPS_PATH "plant.png", MAPS_PATH "plant.tmx", 5504.0f, 5504.0f },  // WaterArena
		pk::map_info_t{ "PlantArena", MAPS_PATH "water.png", MAPS_PATH "water.tmx", 5504.0f, 5504.0f },  // PlantArena
		pk::map_info_t{ "Hospital", MAPS_PATH "hospital.png", MAPS_PATH "hospital.tmx", 5504.0f, 5504.0f },  // Hospital
		pk::map_info_t{ "House", MAPS_PATH "house.png", MAPS_PATH "house.tmx", 5504.0f, 5504.0f },  // House
		pk::map_info_t{ "TestScene", MAPS_PATH "test-scene.png", MAPS_PATH "test-scene.tmx", 5504.0f, 5504.0f }   // TestScene
	};
}
