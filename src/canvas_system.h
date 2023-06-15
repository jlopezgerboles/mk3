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

#pragma once

#include "standard.h"

#include <SDL2/SDL.h>

typedef struct canvas_framework {
	SDL_Window*	window;
	SDL_Surface*	surface;
	u32		canvas_flags;
	f64		canvas_width;
	f64		canvas_height;
	SDL_Rect*	rect_destination;
} canvas_framework;

canvas_framework* canvas_system_initialize(const char* NAME);
void canvas_system_shutdown(canvas_framework* canvas);
