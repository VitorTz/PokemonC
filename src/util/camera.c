#include "camera.h"


static vector_t stack;


void camera_init_aux() {
	vector_init(&stack, sizeof(int), MAX_ENTITIES);
}


void camera_init(camera_t* camera) {
	camera->entities = (vector_t*)malloc(sizeof(vector_t) * (CAMERA_ZINDEX_MAX + 1));
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_t* v = camera->entities + i;
		vector_init(v, sizeof(entity_pair_t), MAX_ENTITIES / 2);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		camera->on_camera[i] = 0;
	}
	camera->camera2D = (Camera2D) {
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY},
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY},
		0.0f,
		1.0f
	};
}


void camera_close(camera_t* camera) {
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_t* v = camera->entities + i;
		vector_close(v);
	}
	free(camera->entities);
}


void camera_insert(camera_t* camera, const entity_t e, const zindex_t z) {
	if (camera->on_camera[e] == 0) {
		camera->on_camera[e] = 1;
		vector_t* vec = camera->entities + z;
		entity_pair_t pair = { e, 0.0f };
		vector_push_back(vec, &pair);
		camera->size++;
	}
}


void camera_erase(camera_t* camera, const entity_t e, const zindex_t z) {
	if (camera->on_camera[e] == 1) {
		camera->on_camera[e] = 0;
		vector_t* vec = camera->entities + z;
		size_t i = 0;
		const iterator_t iter = vector_iter(vec);
		for (entity_pair_t* p = iter.begin; p < iter.end; p++) {
			if (p->e == e) {
				vector_erase(vec, i);
				camera->size--;
				return;
			}
		}
	}
}


void camera_begin_drawing(camera_t* camera) {
	BeginMode2D(camera->camera2D);
}


void camera_end_drawing() {
	EndMode2D();
}


// Quicksort
void camera_sort_by_y_pos(vector_t* v) {
	vector_clear(&stack);	
	int l = 0;
	int h = v->size - 1;
	vector_push_back(&stack, &l);
	vector_push_back(&stack, &h);

	while (stack.size != 0) {
		vector_pop_back(&stack, &h);
		vector_pop_back(&stack, &l);
		
		entity_pair_t aux;
		const float pivot = ((entity_pair_t*)vector_at(v, h))->y;

		int i = l - 1;

		for (int j = l; j < h; j++) {
			vector_cpy_to(v, j, &aux);			
			if (aux.y <= pivot) {
				i++;
				// swap
				vector_set(v, j, vector_at(v, i));
				vector_set(v, i, &aux);							
			}
		}
		// swap
		vector_cpy_to(v, i + 1, &aux);		
		vector_set(v, i + 1, vector_at(v, h));
		vector_set(v, h, &aux);		

		int p = i + 1;
		int aux_int = i;

		if (p - 1 > l) {
			vector_push_back(&stack, &l);
			vector_push_back(&stack, &aux_int);
		}
		aux_int = i + 1;
		if (p + 1 < h) {
			vector_push_back(&stack, &aux_int);
			vector_push_back(&stack, &h);			
		}
	}
}


void camera_draw(camera_t* camera, system_manager_t* system) {
	camera_begin_drawing(camera);
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_t* v = camera->entities + i;
		camera_sort_by_y_pos(v);
		system_manager_draw(system, v);
	}
	camera_end_drawing();
}


void camera_clear(camera_t* camera) {
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_t* v = camera->entities + i;
		vector_clear(v);		
	}
}


size_t camera_num_entities(camera_t* camera) {
	return camera->size;
}