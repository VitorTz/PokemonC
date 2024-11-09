#pragma once
#include "types.h"


size_t hash_entity_t(const void* k);
size_t hash_component_t(const void* k);
size_t hash_zindex_t(const void* k);
size_t hash_str(const void* s);

int equal_entity_t(const void* l, const void* r);
int equal_component_t(const void* l, const void* r);
