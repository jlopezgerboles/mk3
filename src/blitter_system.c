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
SDL_Surface* blitter_system_surface_source(i8* path) {
	SDL_Surface* surface_source = SDL_LoadBMP(path);
	return surface_source;
}

/* 
 * - Function: blitter_system_create_tileset(SDL_Surface* surface_source).
 * - Returns: Returns the total number of tiles in the tileset
 */
SDL_Rect* blitter_system_create_tileset(SDL_Surface* surface_source) {
	i8 TILE_WIDTH = 16;
	i8 TILE_HEIGHT = 16;
	i8 tiles_width = (surface_source -> w)/TILE_WIDTH;
	i8 tiles_height = (surface_source -> h)/TILE_HEIGHT;
	i16 number_tiles = tiles_width * tiles_height;

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
	blitter -> surface_source = blitter_system_surface_source("res/bmp/tileset.bmp");
	if(blitter -> surface_source) printf("[OK] Blitter framework embeded with source surface.\n");
	blitter -> surface_destination = canvas -> surface;
	if(blitter -> surface_destination) printf("[OK] Blitter framework embeded with destination surface.\n");
	blitter -> tile = blitter_system_create_tileset(blitter -> surface_source);
	if(blitter -> tile) printf("[OK] Blitter framework embeded with tileset.\n");
	blitter -> tilemap = blitter_system_create_tilemap(blitter -> surface_destination);
	if(blitter -> tilemap) printf("[OK] Blitter framework embeded with tilemap.\n");

	printf("The values of tile 7 in tileset are %ix and %iy\n", blitter -> tile[7].x, blitter -> tile[7].y);
	printf("The values of tile 3 in tilemap are %ix and %iy\n", blitter -> tilemap[3].x, blitter -> tilemap[3].y);
	printf("Surface source is %i per pixels.\n", blitter -> surface_source -> format -> format);
	printf("Surface destination is %i per pixel.\n", blitter -> surface_destination -> format -> format);

	SDL_UnlockSurface(blitter -> surface_source);
	SDL_UnlockSurface(blitter -> surface_destination);

	i32 check = SDL_BlitSurface(
		blitter -> surface_source,
		&blitter -> tile[7],
		blitter -> surface_destination,
		&blitter -> tilemap[3]);
	printf("%i %s\n", check, SDL_GetError());

	SDL_LockSurface(blitter -> surface_destination);
	SDL_LockSurface(blitter -> surface_source);

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
 * - Returns: Shutd down the blitting system and all its elements.
 */
void blitter_system_shutdown(blitter_framework* blitter) {
	SDL_FreeSurface(blitter -> surface_destination);
	SDL_FreeSurface(blitter -> surface_source);
	free(blitter);
}
