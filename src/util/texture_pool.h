#pragma once
#include <raylib.h>
#include "hash_map.h"


void texture_pool_init();

void texture_pool_close();

Texture2D* texture_pool_get(const char* file_name);
