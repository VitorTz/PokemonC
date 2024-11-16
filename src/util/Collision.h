#pragma once
#include "../pokemon.h"


namespace pk {

	class Collision {
	
	private:
		std::vector<Rectangle> collisions{};

	public:
		Collision();		
		void insert(float x, float y, float width, float height);
		bool check(const Rectangle& rect);
		const std::vector<Rectangle>& get_collisions() const;
		std::size_t size() const;
		void clear();
	};

}