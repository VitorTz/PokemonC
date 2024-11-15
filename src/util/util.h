#pragma once
#include <raylib.h>
#include <raymath.h>
#include <cstddef>
#include "types.h"


namespace pk {

	std::size_t hash_str(const char* s);

	Vector2 get_direction(
		const int left,
		const int right,
		const int up,
		const int down,
		pk::move_state_t& move_state
	);

}