#include "camera.h"


void camera_init(camera_t* camera) {		
	camera->camera2D = (Camera2D) {
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY},
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY},
		0.0f,
		1.0f
	};
}


void camera_set_target(camera_t* camera, const Vector2 target) {
	camera->camera2D.target = target;
}

void camera_add_zoom(camera_t* camera, const float zoom) {
	camera->camera2D.zoom = fclamp(
		zoom + camera->camera2D.zoom,
		CAMERA_ZOOM_MIN,
		CAMERA_ZOOM_MAX
	);
}


void camera_set_zoom(camera_t* camera, const float zoom) {
	camera->camera2D.zoom = fclamp(
		zoom,
		CAMERA_ZOOM_MIN,
		CAMERA_ZOOM_MAX
	);
}


void camera_handle_input(camera_t* camera, const float dt) {
	camera_add_zoom(camera, GetMouseWheelMove() * 2.0f * dt);
}


void camera_begin_drawing(camera_t* camera) {
	BeginMode2D(camera->camera2D);
}


void camera_end_drawing() {
	EndMode2D();
}
