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
//	The following script handles the blitting from source bmp document to canvas surface. Please notice the blitting
//	requires an intermediate surface that fits the specifications of the window surface and brifges any difference
//	that we may have between the source surface bmp and the destination source.
//	The blitting system applies to tileset and sprites. Please notice the blitting is happening in 2 separate
//	surface as the background is only updated when the room is changed while the sprites are updated once per frame. 
//
//-----------------------------------------------------------------------------------------------------------------------

#include "blitter_system.h"

i8 TILE_WIDTH = 8;
i8 TILE_HEIGHT = 8;
i8 SPRITE_WIDTH = 16;
i8 SPRITE_HEIGHT = 32;

/* 
 * - Function: blitter_framework_create().
 * - Returns: Returns a pointer to a newly created blitter framework.
 */
blitter_framework* blitter_framework_create() {
	blitter_framework* blitter;
	blitter = malloc(sizeof(blitter_framework));
	return blitter;
}

/* 
 * - Function: blitter_system_surface_source(i8* path).
 * - Returns: Returns a pointer to the surface where the tiles are stored in memory with original format.
 */
SDL_Surface* blitter_system_surface_source(i8* path) {
	SDL_Surface* surface_source = SDL_LoadBMP(path);
	return surface_source;
}

/* 
 * - Function: blitter_system_surface_destination(SDL_Surface* surface_source).
 * - Returns: Returns a pointer to the surface where the tiles will be stored in memory with specified format.
 */
SDL_Surface* blitter_system_surface_destination(SDL_Surface* surface_source) {
	SDL_Surface* surface_destination;
	surface_destination = SDL_CreateRGBSurface(0, surface_source -> w, surface_source -> h, 32, 0, 0, 0, 0);
	return surface_destination;
}

/* 
 * - Function: blitter_system_create_tileser(SDL_Surface* surface_destination, i8 tile_width, i8 tile_height).
 * - Returns: Returns a pointer to the SDL_Rect array with the coordinates in the surface destination.
 */
SDL_Rect* blitter_system_create_tiles(SDL_Surface* surface_destination, i8 tile_width, i8 tile_height) {
	i8 width = surface_destination -> w/tile_width;
	i8 height = surface_destination -> h/tile_height;
	i32 number_tiles = width * height;
	SDL_Rect* tile = malloc(number_tiles * sizeof(SDL_Rect));
	i64 n = 0;
	for(i8 y = 0; y < height; y++) {
		for(i8 x = 0; x < width; x++) {
			tile[n].x = x * tile_width;
			tile[n].y = y * tile_height;
			tile[n].w = tile_width;
			tile[n].h = tile_height;
			n++;
		}
	}
	return tile;
}

/*
 * - Function: blitter_system_initialize(canvas_framework* canvas).
 * - Returns: Creates the blitting framework and initializes the blitting system.
 */
blitter_framework* blitter_system_initialize(canvas_framework* canvas) {
	blitter_framework* blitter = blitter_framework_create();
	if(blitter) printf("Blitter framework created.\n");
	blitter -> surface_source_tileset = blitter_system_surface_source("res/bmp/tileset.bmp");
	if(blitter -> surface_source_tileset) printf("Blitter framework embeded with surface source tileset.\n");
	blitter -> surface_source_spriteset = blitter_system_surface_source("res/bmp/spriteset.bmp");
	if(blitter -> surface_source_spriteset) printf("Blitter framework embeded with surface source spriteset.\n");
	blitter -> surface_destination_tileset = blitter_system_surface_destination(blitter -> surface_source_tileset);
	if(blitter -> surface_destination_tileset) printf("Blitter framework embeded with surface dest. tileset.\n");
	blitter ->surface_destination_spriteset = blitter_system_surface_destination(blitter -> surface_source_spriteset);
	if(blitter -> surface_destination_spriteset) printf("Blitter framework embeded with surface dest. spriteset.\n");
	blitter -> rect_tileset = blitter_system_create_tiles(
		blitter -> surface_destination_tileset,
		TILE_WIDTH,
		TILE_HEIGHT
	);
	blitter -> rect_spriteset = blitter_system_create_tiles(
		blitter -> surface_destination_spriteset,
		SPRITE_WIDTH,
		SPRITE_HEIGHT
	);

	SDL_UnlockSurface(blitter -> surface_source_tileset);
	SDL_UnlockSurface(blitter -> surface_source_spriteset);
	SDL_UnlockSurface(blitter -> surface_destination_tileset);
	SDL_UnlockSurface(blitter -> surface_destination_spriteset);
	SDL_UnlockSurface(canvas -> surface);
	SDL_BlitSurface(blitter -> surface_source_tileset, NULL, blitter -> surface_destination_tileset, NULL);
	SDL_BlitSurface(blitter -> surface_source_spriteset, NULL, blitter -> surface_destination_spriteset, NULL);

	i64 lvl_0[768] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 25, 17, 14, 11, 11, 0, 0, 11, 25, 18, 26, 14, 0, 24, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 13, 11, 11, 0, 0, 14, 15, 16, 14, 17, 16, 20, 13, 16, 19, 14, 15, 16, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 20, 21, 16, 12, 18, 17, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	for(i16 i = 0; i < 768; i++) {
		SDL_BlitScaled(
			blitter -> surface_destination_tileset,
			&blitter -> rect_tileset[lvl_0[i]],
			canvas -> surface,
			&canvas -> tilemap[i]
		);
	}

	SDL_LockSurface(canvas -> surface);
	SDL_LockSurface(blitter -> surface_destination_spriteset);
	SDL_LockSurface(blitter -> surface_destination_tileset);
	SDL_LockSurface(blitter -> surface_source_spriteset);
	SDL_LockSurface(blitter -> surface_source_tileset);
	SDL_FreeSurface(blitter -> surface_source_spriteset);
	SDL_FreeSurface(blitter -> surface_source_tileset);
	
	SDL_UpdateWindowSurface(canvas -> window);
	return blitter;
}

/* 
 * - Function: blitter_system_update().
 * - Returns: Refreshses the blitting of the tilemap destination surface on request.
 */
void blitter_system_update_tileset(blitter_framework* blitter) {
}

/* 
 * - Function: blitter_system_update().
 * - Returns: Refreshses the blitting of the sprite destination surface on request.
 */
void blitter_system_update_spriteset(blitter_framework* blitter) {
}

/* 
 * - Function: blitter_system_shutdown(blitter_framework* blitter).
 * - Returns: Shutd down the blitting system and all its elements.
 */
void blitter_system_shutdown(blitter_framework* blitter) {
	SDL_FreeSurface(blitter -> surface_destination_tileset);
	SDL_FreeSurface(blitter -> surface_destination_spriteset);
	free(blitter);
}
