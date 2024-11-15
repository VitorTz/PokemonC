#pragma once
#include <cassert>
#include <raylib.h>
#include <unordered_map>
#include "util.h"


namespace pk {


	void texture_pool_init();

	Texture2D texture_pool_get(const char* path);

	void texture_pool_close();

}