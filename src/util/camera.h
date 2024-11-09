#pragma once
#include <raylib.h>
#include "../ecs/system_manager.h"
#include "util.h"
#include "entity_pair.h"
#include "constants.h"
#include "types.h"
#include "hash_map.h"
#include "vector.h"


typedef struct camera {
	vector_t* entities;	
	Camera2D camera2D;
	size_t size;
	char on_camera[MAX_ENTITIES];
} camera_t;

void camera_init_aux();

void camera_init(camera_t* camera);

void camera_close(camera_t* camera);

void camera_insert(camera_t* camera, entity_t e, zindex_t zindex);

void camera_begin_drawing(camera_t* camera);

void camera_end_drawing();

void camera_erase(camera_t* camera, entity_t e, zindex_t zindex);

void camera_draw(camera_t* camera, system_manager_t* system);

void camera_sort_by_y_pos(vector_t* vec);

void camera_clear(camera_t* camera);

size_t camera_num_entities(camera_t* camera);