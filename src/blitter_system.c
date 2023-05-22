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

#include "blitter_system.h"
#include "canvas_system.h"

#include <stdio.h>

#define SPRITE_WIDTH_HEIGHT 8

static i8* atlas =
	"00000000010000000000000000111111111000000001000000000000000000000000000000000000"; // This is a 8x10 background.

/* 
 * - Function: blitter_framework_create().
 * - Returns: Returns a pointer to a newly created blitter framework.
 */
static blitter_framework* blitter_framework_create() {
	blitter_framework* blitter;
	blitter = malloc(sizeof(blitter_framework));
	if(blitter) printf("[OK] Blitter created.");
	return blitter;
}

/* 
 * - Function: blitter_system_load_atlas(i8* path).
 * - Returns: Returns a pointer to the surface where the atlas is stored (the source surface).
 */
static SDL_Surface* blitter_system_load_atlas(i8* path) {
	SDL_Surface* source = SDL_LoadBMP("path");
	if(source) printf("[OK] Source created.");
	return source;
}

/* 
 * - Function: blitter_system_translate_code(i8* code).
 * - Returns: Returns a vector 2 with the coordinates in the atlas for the selected tile.
 */
static vec2 blitter_system_translate_code(i8* code) {
	//vec2 coordinates;
	//i8* code;
	//return coordinates;
}

/* 
 * - Function: blitter_system_map().
 * - Returns: Returns a pointer to an the name of the window.
 */
static void blitter_system_map(blitter_framework* blitter) {

	SDL_LockSurface(blitter -> surface_source);
	SDL_LockSurface(blitter -> surface_destination);

	for(i8 n = 0; n < 80; n++) {
		//vec2 atlas_coordinates = blitter_system_translate_code(atlas[n]);
		blitter -> rect_source -> x = atlas[n]*8;
		blitter -> rect_source -> y = 0;
		blitter -> rect_destination -> x = n*8;
		blitter -> rect_destination -> y = 0;
		SDL_BlitSurface(
			blitter -> surface_source,
			blitter -> rect_source,
			blitter -> surface_destination,
			blitter -> rect_destination
		);
	}

	SDL_UnlockSurface(blitter -> surface_destination);
	SDL_UnlockSurface(blitter -> surface_source);
}

/* 
 * - Function: blitter_system_initialize(canvas_framework* canvas).
 * - Returns: Initializes the blitter system and creates the blitting framework.
 */
blitter_framework* blitter_system_initialize(canvas_framework* canvas) {
	blitter_framework* blitter = blitter_framework_create();
	blitter -> rect_source -> w = SPRITE_WIDTH_HEIGHT;
	blitter -> rect_source -> h = SPRITE_WIDTH_HEIGHT;
	blitter -> rect_destination -> w = SPRITE_WIDTH_HEIGHT;
	blitter -> rect_destination -> h = SPRITE_WIDTH_HEIGHT;
	blitter -> surface_source = blitter_system_load_atlas("res/bmp/tileset.bmp");
	if(blitter -> surface_source) printf("[OK] Blitter source assigned to blitter framework.");
	blitter -> surface_destination = canvas -> surface;
	if(blitter -> surface_destination) printf("[OK] Blitter destination assigned to blitter framework.");
	blitter_system_map(blitter);
	return blitter;
}

/* 
 * - Function: blitter_system_update().
 * - Returns: Refreshses the blitting of the destination surface on request.
 */
void blitter_system_update() {
}

/* 
 * - Function: blitter_system_shutdown(blitter_framework* blitter).
 * - Returns: Shutd down all the elements of the blitter system.
 */
void blitter_system_shutdown(blitter_framework* blitter) {
	SDL_FreeSurface(blitter -> surface_source);
	free(blitter);
}
