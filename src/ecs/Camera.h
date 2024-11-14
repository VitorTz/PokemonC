#pragma once
#include <cassert>
#include <raylib.h>
#include <array>
#include <vector>
#include <algorithm>
#include "ComponentManager.h"
#include "SystemManager.h"
#include "../util/types.h"
#include "../constants.h"

namespace pk {

	class Camera {

	private:
		Camera2D camera{};
		std::array<std::vector<std::pair<float, pk::entity_t>>, pk::CAMERA_ZINDEX_MAX> entities{};
		std::array<bool, pk::MAX_ENTITIES> is_on_camera{};
		std::size_t m_size{};

	public:
		Camera();
		
		void begin_drawing();
		
		void end_drawing();

		void insert(pk::entity_t e, pk::zindex_t zindex);

		void erase(pk::entity_t e, pk::zindex_t zindex);		

		void draw(pk::SystemManager* system_manager, pk::ComponentManager* component_manager);

		void clear();

		std::size_t size() const;

	};

}