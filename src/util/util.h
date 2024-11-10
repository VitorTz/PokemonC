#pragma once
#include <time.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include "types.h"
#include "../ecs/components.h"


size_t hash_entity_t(const void* k);
size_t hash_component_t(const void* k);
size_t hash_zindex_t(const void* k);
size_t hash_int(const void* k);
size_t hash_str(const void* s);

int equal_entity_t(const void* l, const void* r);
int equal_component_t(const void* l, const void* r);

void init_random_utility();

float fclamp(float value, float min, float max);

double dclamp(double value, double min, double max);

Vector2 get_direction(
	int up,
	int down,
	int left,
	int right
);

int randint(int start, int end);

Vector2 get_center(transform_t* t);