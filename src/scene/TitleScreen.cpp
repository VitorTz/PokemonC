#include "Scene.h"


static pk::ui::image_t background{};
static pk::ui::image_t logo{};
static pk::ui::image_t press_start{};


pk::TitleScreen::TitleScreen() {
	background = pk::ui::image(GRAPHICS_PATH "backgrounds/title-screen-bg.png");
}


void pk::TitleScreen::update(const float dt) {
	if (IsKeyPressed(KEY_SPACE)) {
		pk::scene_change_scene(pk::WorldSceneId);
	}
}


void pk::TitleScreen::draw() {
	DrawTextureRec(background.texture, background.rect, background.pos, WHITE);
}