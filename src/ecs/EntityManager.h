#pragma once
#include <cassert>
#include <queue>
#include "../constants.h"
#include "../util/types.h"


namespace pk {

	class EntityManager {

	private:
		std::queue<pk::entity_t> q{};
		std::size_t m_size{};

	public:
		EntityManager();
		pk::entity_t create();
		void destroy(pk::entity_t e);
		void clear();
		std::size_t size() const;

	};

}