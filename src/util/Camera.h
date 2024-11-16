#pragma once
#include "../pokemon.h"
#include "../ecs/component/ComponentManager.h"
#include "../ecs/system/SystemManager.h"


namespace pk {

	class Camera {

	private:
		Camera2D camera{};
		std::array<std::vector<std::pair<float, pk::entity_t>>, pk::CAMERA_ZINDEX_MAX + 1> entities{};
		std::array<bool, pk::MAX_ENTITIES> is_on_camera{};
		std::size_t m_size{};
		float max_x;
		float max_y;

	public:
		explicit Camera(pk::SceneID scene_id);
		
		void begin_drawing() const;
		
		void end_drawing();

		void insert(pk::entity_t e, pk::zindex_t zindex);

		void erase(pk::entity_t e, pk::zindex_t zindex);		

		void set_target(float x, float y);

		void handle_input(float dt);

		void draw(pk::SystemManager* system_manager, pk::ComponentManager* component_manager);

		void clear();

		float get_zoom() const;

		std::size_t size() const;

	};

}