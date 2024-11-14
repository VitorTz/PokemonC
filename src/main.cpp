#include "constants.h"
#include "util/TexturePool.h"



int main(void) {
	InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
	SetTargetFPS(pk::FPS);

	pk::texture_pool_init();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	pk::texture_pool_clear();
	CloseWindow();
	return 0;
}