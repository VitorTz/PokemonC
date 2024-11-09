#pragma once


// WINDOW
#define SCREEN_W 1280
#define SCREEN_H 720
#define SCREEN_CENTERX 640
#define SCREEN_CENTERY 360
#define FPS 60
#define WINDOW_TITLE "PokemonC"

// RESOURCES
#define ASSETS_PATH "./resources/"
#define GRAPHICS_PATH "./resources/graphics/"
#define CHARACTERS_PATH "./resources/graphics/characters/"
#define AUDIO_PATH "./resources/audio/"
#define MAPS_PATH "./resources/data/maps/"
#define FONTS_PATH "./resources/graphics/fonts/"
#define UI_PATH "./resources/graphics/ui/"
#define ICONS_PATH "./resources/graphics/icons/"
#define BACKGROUNDS_PATH "./resources/graphics/backgrounds/"

// SCENES
#define TITLE_SCREEN_ID 0
#define WORLD_SCENE_ID 1
#define FIRE_ARENA_SCENE_ID 2
#define PLANT_ARENA_SCENE_ID 3
#define WATER_ARENA_SCENE_ID 4
#define HOSPITAL_SCENE_ID 5
#define HOUSE_SCENE_ID 6
#define TEST_SCENE_ID 7
#define NUM_SCENES 8
#define MAIN_SCENE TITLE_SCREEN_ID

// ECS
#define MAX_ENTITIES 4096
#define TRANSFORM_ID 0
#define SPRITE_ID 1
#define SPRITE_ANIMATION_ID 2
#define NUM_COMPONENTS 3

// CAMERA
#define CAMERA_ZINDEX_MIN 0
#define CAMERA_ZINDEX_TERRAIN 0
#define CAMERA_ZINDEX_WATER 1
#define CAMERA_ZINDEX_SHADOW 2
#define CAMERA_ZINDEX_OBJECTS 3
#define CAMERA_ZINDEX_TOP 4
#define CAMERA_ZINDEX_SKY 5
#define CAMERA_ZINDEX_MAX 5
#define CAMERA_ZOOM_MIN 0.25f
#define CAMERA_ZOOM_MAX 2.5f

// SPRITE ANIMATION
#define ANIMATION_SPEED_SLOW 12
#define ANIMATION_SPEED_NORMAL 8
#define ANIMATION_SPEED_FAST 6

// CHARACTERS
#define CHARACTER_WIDTH 128.0f
#define CHARACTER_HEIGHT 128.0f

// PLAYER
#define PLAYER_SPEED 150.0f
