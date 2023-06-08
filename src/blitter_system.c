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

/* 
 * - Function: blitter_framework_create().
 * - Returns: Returns a pointer to a newly created blitter framework.
 */
blitter_framework* blitter_framework_create() {
	blitter_framework* blitter;
	blitter = malloc(sizeof(blitter_framework));
	if(blitter) printf("[OK] Blitter framework created.\n");
	return blitter;
}

/* 
 * - Function: blitter_system_source_surface(i8* path).
 * - Returns: Returns a pointer to the surface where the tileset is stored in memory.
 */
SDL_Surface* blitter_system_surface_bmp(i8* path) {
	SDL_Surface* surface_bmp = SDL_LoadBMP(path);
	return surface_bmp;
}

/* 
 * - Function: blitter_system_create_tileset(SDL_Surface* surface_source).
 * - Returns: Returns the total number of tiles in the tileset
 */
SDL_Rect* blitter_system_create_tileset(SDL_Surface* surface_bmp) {
	i8 tiles_width = (surface_bmp -> w)/16;
	i8 tiles_height = (surface_bmp -> h)/16;
	i16 number_tiles = tiles_width * tiles_height;
	printf("We have a total of %i tiles.\n", number_tiles);
	SDL_Rect* tile = malloc(number_tiles * sizeof(SDL_Rect));
	i32 n = 0;
	for(i8 y = 0; y < tiles_height; y++) {
		for(i8 x = 0; x < tiles_width ; x++) {
			tile[n].x = x * 16;
			tile[n].y = y * 16;
			tile[n].w = 16;
			tile[n].h = 16;
			n++;
		}
	}
	return tile;
}

/* 
 * - Function: blitter_system_create_tilemap(SDL_Surface* surface_source).
 * - Returns: Returns the total number of tiles in the tileset
 */
SDL_Rect* blitter_system_create_tilemap(SDL_Surface* surface_destination) {

	i8 tiles_width = 10;
	i8 tiles_height = 8;
	i16 number_tiles = tiles_width * tiles_height;

	SDL_Rect* tilemap = malloc(number_tiles * sizeof(SDL_Rect));

	i32 n = 0;
	for(i8 y = 0; y < tiles_height; y++) {
		for(i8 x = 0; x < tiles_width ; x++) {
			tilemap[n].x = x * 100;
			tilemap[n].y = y * 100;
			tilemap[n].w = 100;
			tilemap[n].h = 100;
			n++;
		}
	}
	return tilemap;
}

/*
 * - Function: blitter_system_initialize(canvas_framework* canvas).
 * - Returns: Creates the blitting framework and initializes the blitting system.
 */
blitter_framework* blitter_system_initialize(canvas_framework* canvas) {
	blitter_framework* blitter = blitter_framework_create();
	blitter -> surface_bmp = blitter_system_surface_bmp("res/bmp/tileset1.bmp");
	if(blitter -> surface_bmp) printf("[OK] Blitter framework embeded with surface bmp.\n");
	blitter -> surface_source = canvas -> surface;
	if(blitter -> surface_source) printf("[OK] Blitter framework embeded with surface source.\n");
	blitter -> surface_destination = canvas -> surface;
	if(blitter -> surface_destination) printf("[OK] Blitter framework embeded with surface destination.\n");
	blitter -> tile = blitter_system_create_tileset(blitter -> surface_bmp);
	if(blitter -> tile) printf("[OK] Blitter framework embeded with tileset.\n");
	blitter -> tilemap = blitter_system_create_tilemap(blitter -> surface_destination);
	if(blitter -> tilemap) printf("[OK] Blitter framework embeded with tilemap.\n");

	SDL_UnlockSurface(blitter -> surface_source);
	SDL_UnlockSurface(blitter -> surface_bmp);

	SDL_BlitSurface(blitter -> surface_bmp,	NULL, blitter -> surface_source, NULL);

	SDL_LockSurface(blitter -> surface_bmp);
	SDL_LockSurface(blitter -> surface_source);

	SDL_UnlockSurface(blitter -> surface_source);
	SDL_UnlockSurface(blitter -> surface_destination);
	
	i8 n = 1;
	for(i8 i = 0; i < 12; i++) {
		SDL_BlitScaled(
			blitter -> surface_source,
			&blitter -> tile[50],
			blitter -> surface_destination,
			&blitter -> tilemap[n]);
		SDL_UpdateWindowSurface(canvas -> window);
		SDL_Delay(100);
		n++;
	}

	SDL_LockSurface(blitter -> surface_destination);
	SDL_LockSurface(blitter -> surface_source);

	SDL_FreeSurface(blitter -> surface_bmp);

	return blitter;
}

/* 
 * - Function: blitter_system_update().
 * - Returns: Refreshses the blitting of the destination surface on request.
 */
void blitter_system_update(blitter_framework* blitter) {
/*
	SDL_UnlockSurface(blitter -> surface_source);
	SDL_UnlockSurface(blitter -> surface_destination);
	
	i8 i  = 0;
	while(i < 70) {
	//for(i8 i = 0; i < 70; i++)
		SDL_BlitScaled(
			blitter -> surface_source,
			&blitter -> tile[3],
			blitter -> surface_destination,
			&blitter -> tilemap[i]);
		SDL_Delay(100);
	}

	SDL_LockSurface(blitter -> surface_destination);
	SDL_LockSurface(blitter -> surface_source);
*/
}

/* 
 * - Function: blitter_system_shutdown(blitter_framework* blitter).
 * - Returns: Shutd down the blitting system and all its elements.
 */
void blitter_system_shutdown(blitter_framework* blitter) {
	SDL_FreeSurface(blitter -> surface_source);
	SDL_FreeSurface(blitter -> surface_destination);
	free(blitter);
}
