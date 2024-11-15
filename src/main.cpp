#include "scene/Scene.h"


int main() {
	InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
	SetTargetFPS(pk::FPS);

	pk::components_init();
	pk::texture_pool_init();
	pk::scene_init();

	while (WindowShouldClose() == false) {
		pk::scene_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		pk::scene_draw();
		EndDrawing();
	}

	pk::texture_pool_close();
	pk::ecs_destroy_all_instances();
	CloseWindow();
	return 0;
}