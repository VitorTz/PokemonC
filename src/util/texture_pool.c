#include "texture_pool.h"
#include "util.h"


static hash_map_t texture_map;


void texture_pool_init() {
	hash_map_init(&texture_map, sizeof(Texture2D), 256, hash_str);
}


void texture_pool_close() {
	const iterator_t miter = hash_map_iter(&texture_map);
	for (vector_t* v = miter.begin; v < miter.end; v += miter.step) {
		const iterator_t viter = vector_iter(v);
		for (char* p = viter.begin; p < viter.end; p += viter.step) {
			Texture2D* t = (Texture2D*)(p + sizeof(size_t));
			UnloadTexture(*t);
		}
	}
	hash_map_close(&texture_map);
}

Texture2D* texture_pool_get(const char* file_name) {
	query_t q = hash_map_allocate(&texture_map, file_name);
	Texture2D* t = (Texture2D*)q.data;
	if (q.success) {
		*t = LoadTexture(file_name);
	}
	return t;
}