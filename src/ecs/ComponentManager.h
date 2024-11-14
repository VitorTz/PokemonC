#pragma once
#include "components.h"
#include "../constants.h"
#include <array>


namespace pk {


	class ComponentManager {

	private:
		std::array<std::pair<char*, std::size_t>, pk::NUM_COMPONENTS> component{};

	public:
		ComponentManager();
		~ComponentManager();
		void* at(const pk::entity_t e, const pk::component_t id);

	};

}