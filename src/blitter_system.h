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
#include "canvas_system.h"

#include <SDL2/SDL.h>

typedef struct blitter_framework {
	SDL_Surface*	surface_source_tileset;
	SDL_Surface*	surface_source_spriteset;
	SDL_Surface*	surface_destination_tileset;
	SDL_Surface*	surface_destination_spriteset;
	SDL_Rect*	rect_tileset;
	SDL_Rect*	rect_spriteset;
} blitter_framework;

blitter_framework* blitter_system_initialize(canvas_framework* canvas);
void blitter_system_update_tileset(blitter_framework* blitter);
void blitter_system_update_spriteset(blitter_framework* blitter);
void blitter_system_shutdown(blitter_framework* blitter);
