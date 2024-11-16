#pragma once
#include <cstdint>
#include <unordered_set>


namespace pk {

	typedef uint32_t entity_t;
	typedef uint8_t component_t;
	typedef uint8_t zindex_t;

	typedef std::unordered_set<pk::entity_t> EntitySet;

	typedef struct sprite_animation_info {
		const char* path{};
		float width{};
		float height{};
		std::uint8_t speed;
	} sprite_animation_info_t;

	typedef struct move_state {
		char direction{ 'd' };
		char last_direction{ 'd' };
		bool last_is_idle{ true };
		bool is_idle{ true };
		move_state() = default;
		explicit move_state(const char direction) : direction(direction) { }
	} move_state_t;


	typedef struct map_info {
		const char* name{};
		const char* image_path{};
		const char* tmx_map_path{};
		float width{};
		float height{};
	} map_info_t;

	enum SceneID {
		TitleScreenId,
		WorldSceneId,
		FireArenaSceneId,
		WaterAreanaSceneId,
		PlantArenaSceneId,
		HospitalSceneId,
		HouseSceneId,
		TestSceneId,
		NumScenes
	};

	enum ObjectGroupId {
		EntitiesGroupId,
		CollisionGroupId,
		TransitionGroupId,
		CoastGroupId,
		MonstersGroupId,
		ObjectsGroupId
	};

	enum CharacterID {
		PlayerID,
		NurseID,
		NumCharacters
	};

}


