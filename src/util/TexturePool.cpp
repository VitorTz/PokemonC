#include "TexturePool.h"


static std::unordered_map<std::size_t, Texture2D> pool{};



void pk::texture_pool_init() {
	pool.reserve(256);
}


Texture2D pk::texture_pool_get(const char* path) {
	const std::size_t h = pk::hash_str(path);
	if (pool.find(h) == pool.end()) {
		Texture2D t = LoadTexture(path);
		assert(t.id > 0);
		pool.emplace(h, t);
	}
	return pool[h];
}


void pk::texture_pool_close() {
	for (auto& pair : pool) {
		UnloadTexture(pair.second);
	}
}