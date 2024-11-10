#include "pokemon.h"
#include "scene/scene.h"
#include "ecs/ecs_manager.h"


int main(void) {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(FPS);
	const Image icon = LoadImage(ICONS_PATH "pokeball.png");
	SetWindowIcon(icon);	
	
	texture_pool_init();
	ecs_manager_init();
	scene_manager_init();	

	while (!WindowShouldClose()) {
		scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);		
		scene_manager_draw();
		DrawFPS(20, 20);
		EndDrawing();
	}

	UnloadImage(icon);
	ecs_manager_close();	
	texture_pool_close();
	CloseWindow();
	return 0;
}