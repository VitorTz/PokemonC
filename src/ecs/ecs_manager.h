#pragma once
#include "ecs.h"


typedef struct ecs_manager {
	ecs_t* ecs_vec[NUM_SCENES];
	ecs_t* ecs;
} ecs_manager_t;


void ecs_manager_init();


void ecs_manager_close();


void ecs_manager_set_ecs(int ecs_id);


ecs_t* ecs_manager_get_ecs();


void ecs_manager_create(int ecs_id);