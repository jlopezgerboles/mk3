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
 * - Function: SDL_Surface* blitter_system_surface_bmp(i8* path)
 * - Returns: Returns a pointer to the SDL_Surface where the tiles are stored in memory with original format.
 */
SDL_Surface* blitter_system_surface_bmp(i8* path) {
	SDL_Surface* surface_bmp = SDL_LoadBMP(path);
	return surface_bmp;
}

/* 
 * - Function: SDL_Surface* blitter_system_surface_source(SDL_Surface* surface_bmp)
 * - Returns: Returns a pointer to the SDL_Surface where the tiles will be stored in memory with specified format.
 */
SDL_Surface* blitter_system_surface_source(SDL_Surface* surface_bmp) {
	SDL_Surface* surface_source;
	surface_source = SDL_CreateRGBSurface(0, surface_bmp -> w, surface_bmp -> h, 32, 0, 0, 0, 0);
	return surface_source;
}

/* 
 * Function: SDL_Rect* blitter_system_rect_source()
 * Returns: Returns a pointer to the SDL_Rect array with the coordinates in the surface destination of the
 * alphanumeric values, the sprites and the background tiles.
 */
SDL_Rect* blitter_system_rect_source() {
	i8 num_alphanum = 36;
	//i8 num_tiles = 7;
	i8 num_sprites = 12;
	i16 total_tiles = num_alphanum + num_sprites; //+ num_background;
	SDL_Rect* tile = malloc(total_tiles * sizeof(SDL_Rect));

	i8 alphanum_width = 8;
	i8 alphanum_height = 10;
	i8 tile_width = 8;
	i8 tile_height = 8;
	i8 sprite_width = 16;
	i8 sprite_height = 32;

	i8 alphanum_values[] = " 1234567890abcdefghijklmnopqrstuvwxyz";
	for(i8 i = 0; i <= num_alphanum; i++) {
		tile[alphanum_values[i]].x = i * alphanum_width;
		tile[alphanum_values[i]].y = 0;
		tile[alphanum_values[i]].w = alphanum_width;
		tile[alphanum_values[i]].h = alphanum_height;
	}
	for(i8 i = 0; i <= 47; i++) {
		tile[i+37].x = i * sprite_width;
		tile[i+37].y = 10;
		tile[i+37].w = sprite_width;
		tile[i+37].h = sprite_height;
	}
	return tile;
}

/*
 * - Function: blitter_system_initialize(canvas_framework* canvas).
 * - Returns: Returns a pointer to the blitting framework already filled and ready foir the game.
 */
blitter_framework* blitter_system_initialize(canvas_framework* canvas) {
	blitter_framework* blitter = blitter_framework_create();
	if(blitter) printf("Blitter framework created.\n");
	blitter -> surface_bmp = blitter_system_surface_bmp("res/bmp/spriteset.bmp");
	if(blitter -> surface_source) printf("Blitter framework embeded with surface bmp.\n");
	blitter -> surface_source = blitter_system_surface_source(blitter -> surface_bmp);
	if(blitter -> surface_source) printf("Blitter framework embeded with surface source.\n");
	blitter -> rect_source = blitter_system_rect_source();
	
	SDL_UnlockSurface(blitter -> surface_bmp);
	SDL_UnlockSurface(blitter -> surface_source);
	SDL_BlitSurface(blitter -> surface_bmp, NULL, blitter -> surface_source, NULL);
	SDL_LockSurface(blitter -> surface_bmp);
	SDL_FreeSurface(blitter -> surface_bmp);
	
	SDL_UnlockSurface(canvas -> surface);
	
	// Implement a matrix system instead of the long unidimensional array.
	i8 background[768] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               e";

	for(i16 i = 0; i < 768; i++) {
		SDL_BlitScaled(
			blitter -> surface_source,
			&blitter -> rect_source[background[i]],
			canvas -> surface,
			&canvas -> rect_destination[i]
		);
	}
	SDL_LockSurface(canvas -> surface);
	SDL_LockSurface(blitter -> surface_source);
	SDL_UpdateWindowSurface(canvas -> window);
	SDL_SaveBMP(canvas -> surface, "res/bmp/image.bmp");
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
	SDL_FreeSurface(blitter -> surface_source);
	free(blitter);
}
