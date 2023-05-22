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
	SDL_Renderer*	renderer;
	SDL_Surface*	surface;
	SDL_Surface*	surface_logo;
	SDL_Texture*	texture;
	u8*		canvas_name;
	u32		canvas_flags;
	f64		canvas_width;
	f64		canvas_height;
} canvas_framework;

canvas_framework* canvas_system_initialize(char* name);
void canvas_system_shutdown(canvas_framework* canvas);
