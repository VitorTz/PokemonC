#pragma once
#include <raylib.h>
#include "util.h"
#include "constants.h"


typedef struct camera {	
	Camera2D camera2D;	
} camera_t;

void camera_init(camera_t* camera);

void camera_begin_drawing(camera_t* camera);

void camera_end_drawing();

void camera_set_target(camera_t* camera, Vector2 target);

void camera_handle_input(camera_t* camera, float dt);

void camera_add_zoom(camera_t* camera, float zoom);

void camera_set_zoom(camera_t* camera, float zoom);
