#include "ecs_manager.h"


static ecs_manager_t ecsm;


void ecs_manager_init() {
	camera_init_aux();	
}


void ecs_manager_close() {
	for (int i = 0; i < NUM_SCENES; i++) {
		ecs_t* e = ecsm.ecs_vec[i];
		if (e != NULL) {
			ecs_close(e);
		}
		free(e);
	}	
}


void ecs_manager_set_ecs(const int ecs_id) {
	ecsm.ecs = ecsm.ecs_vec[ecs_id];
}

ecs_t* ecs_manager_get_ecs() {
	return ecsm.ecs;
}


void ecs_manager_create(const int ecs_id) {
 	ecs_t* e = ecsm.ecs_vec[ecs_id];
	if (e != NULL) {
		return;
	}
	ecsm.ecs_vec[ecs_id] = (ecs_t*)malloc(sizeof(ecs_t));
	e = ecsm.ecs_vec[ecs_id];
	ecs_init(e);
}
