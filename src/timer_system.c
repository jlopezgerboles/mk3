//-----------------------------------------------------------------------------------------------------------------------
//
// Copyright (C) 2023 by Swiss Entertainment Software AG.
//
// This source is available for distribution and/or modification only under the terms of the Source Code License as
// published by Swiss Entertainment Software AG. All rights reserved.
//
// The source is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of FITNESS FOR A PARTICULAR PURPOSE.
//
// DESCRIPTION:
//  -
//
//-----------------------------------------------------------------------------------------------------------------------

#include "timer_system.h"

#define LOOPS_PER_SECOND 30

/* 
 * - Function: timer_framework_create()
 * - Returns: Returns the time left to refresh the game loop. This will be either 0 when it is time to refresh the game
 *	loop or it will return the time left to refresh, all given a constant refresh rate.
 */
timer_framework* timer_framework_create() {
	timer_framework* timer;
	timer = malloc(sizeof(timer_framework));
	return timer; 
}

timer_framework* timer_system_initialize() {
	timer_framework* timer;
	timer = timer_framework_create();
	timer -> t0 = SDL_GetTicks();
	timer -> t1 = 0;
	timer -> delta = 1000 / LOOPS_PER_SECOND; 
	timer -> t2 = timer -> t1 + timer -> delta;
	return timer;
}

void timer_system_control_fps(timer_framework* timer) {

	timer -> t1 = SDL_GetTicks();
	SDL_Delay(timer -> t2 - timer -> t1);
}
