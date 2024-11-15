#pragma once
#include "../util/TexturePool.h"


namespace pk {

	namespace ui {

		typedef struct image {
			Texture2D texture{};
			Rectangle rect{};
			Vector2 pos{};
			image() = default;
			explicit image(
				const char* p
			) : texture(pk::texture_pool_get(p)),
				rect({0.0f, 0.0f, (float) texture.width, (float) texture.height}) { }
		} image_t;

	}

}