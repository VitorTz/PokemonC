#include "components.h"


static std::bitset<pk::NUM_COMPONENTS> DRAWABLE_COMP_BITSET{};


void pk::components_init() {
	DRAWABLE_COMP_BITSET.set(pk::id::sprite, true);
	DRAWABLE_COMP_BITSET.set(pk::id::sprite_animation, true);
}


bool pk::is_drawable_component(const pk::component_t id) {
	return DRAWABLE_COMP_BITSET[id];
}