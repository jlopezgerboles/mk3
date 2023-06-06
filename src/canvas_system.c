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
//  - The canvas system is a set of functions that control the windoing of our application.
//
//-----------------------------------------------------------------------------------------------------------------------

#include "standard.h"
#include "canvas_system.h"

/* 
 * - Function: canvas_framework_create().
 * - Returns: Returns a pointer to an empry canvas framework and allocates its memory.
 */
canvas_framework* canvas_framework_create() {
	canvas_framework* canvas;
	canvas = malloc(sizeof(canvas_framework));
	if(canvas) printf("[OK] Canvas framework created.\n");
	return canvas;
}

/* 
 * - Function: canvas_system_desired_width()
 * - Returns: Returns the desired width of the canvas given the display.
 */
f64 canvas_system_desired_width() {
	f64 canvas_width;
	SDL_DisplayMode* display_mode;
	printf("Works until here.\n");
	SDL_GetCurrentDisplayMode(1, display_mode);
	printf("Works until here.\n");
	canvas_width = 0.8 * (f64)display_mode -> w;
	printf("The desired width is: %f, canvas_width\n");
	return canvas_width;
}

/* 
 * - Function: canvas_system_desired_height()
 * - Returns: Returns the desired height of the canvas given the display.
 */
f64 canvas_system_desired_height() {
	f64 canvas_height;
	SDL_DisplayMode* display_mode;
	SDL_GetCurrentDisplayMode(0, display_mode);
	canvas_height = 0.8 * (f64)display_mode -> h;
	printf("The desired width is: %f, canvas_height\n");
	return canvas_height;
}

/* 
 * - Function: canvas_system_window_flags_create().
 * - Returns: Returns an unsigned integer that will collect the window flags.
 */
u32 canvas_system_window_flags() {
	u32 window_flags =
//		SDL_WINDOW_FULLSCREEN		// fullscreen window
//		SDL_WINDOW_FULLSCREEN_DESKTOP	// fullscreen window at the current desktop resolution
//		SDL_WINDOW_OPENGL		// window usable with OpenGL context
//		SDL_WINDOW_VULKAN		// window usable with a Vulkan instance
//		SDL_WINDOW_SHOWN		// window is visible
//		SDL_WINDOW_HIDDEN		// window is not visible
		SDL_WINDOW_BORDERLESS		// no window decoration
//		SDL_WINDOW_RESIZABLE		// window can be resized
//		SDL_WINDOW_MINIMIZED		// window is minimized
//		SDL_WINDOW_MAXIMIZED		// window is maximized
//		SDL_WINDOW_INPUT_GRABBED	// window has grabbed input focus
//		SDL_WINDOW_INPUT_FOCUS		// window has input focus
//		SDL_WINDOW_MOUSE_FOCUS		// window has mouse focus
//		SDL_WINDOW_FOREIGN		// window not created by SDL
//		SDL_WINDOW_ALLOW_HIGHDPI	// window should be created in high-DPI mode if supported (>= SDL 2.0.1)
//		SDL_WINDOW_MOUSE_CAPTURE	// window has mouse captured (unrelated to INPUT_GRABBED, >= SDL 2.0.4)
//		SDL_WINDOW_ALWAYS_ON_TOP	// window should always be above others (X11 only, >= SDL 2.0.5)
//		SDL_WINDOW_SKIP_TASKBAR		// window should not be added to the taskbar (X11 only, >= SDL 2.0.5)
//		SDL_WINDOW_UTILITY		// window should be treated as a utility window (X11 only, >= SDL 2.0.5)
//		SDL_WINDOW_TOOLTIP		// window should be treated as a tooltip (X11 only, >= SDL 2.0.5)
//		SDL_WINDOW_POPUP_MENU		// window should be treated as a popup menu (X11 only, >= SDL 2.0.5)	
		;
		return window_flags;
}

/* 
 * - Function: canvas_system_window(canvas_framework* canvas)
 * - Returns: Returns a pointer to the SDL Window later assigned to the canvas framework.
 */
SDL_Window* canvas_system_window(canvas_framework* canvas, const char* NAME) {
	SDL_Window* window = SDL_CreateWindow(
		NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		canvas -> canvas_width,
		canvas -> canvas_height,
		canvas -> canvas_flags);
	return window;
}

/* 
 * - Function: canvas_system_surface(SDL_Window* window)
 * - Returns: Returns a pointer to the SDL Surface automatically assigned to a window.
 */
SDL_Surface* canvas_system_surface(SDL_Window* window) {
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	return surface;
}

/* 
 * - Function: canvas_system_initialize().
 * - Returns: Returns the whole canvas framework used in our application.
 */
canvas_framework* canvas_system_initialize(const char* NAME) {
	canvas_framework* canvas = canvas_framework_create();
	canvas -> canvas_width = 1000.00; //canvas_system_desired_width();
	canvas -> canvas_height = 800.00; //canvas_system_desired_height();
	canvas -> canvas_flags = canvas_system_window_flags();
	if(canvas -> canvas_flags) printf("[OK] Canvas framework embeded with canvas flags.\n");
	canvas -> window = canvas_system_window(canvas, NAME);
	if(canvas -> window) printf("[OK] Canvas framework embeded with window.\n");
	canvas -> surface = canvas_system_surface(canvas -> window);
	if(canvas -> surface) printf("[OK] Canvas framework embeded with surface.\n");
	return canvas;
}

/* 
 * - Function: canvas_system_shutdown().
 * - Returns: Shuts down all the canvas related variables and frees all memory related to this system.
 */
void canvas_system_shutdown(canvas_framework* canvas) {
	SDL_FreeSurface(canvas -> surface);
	SDL_DestroyWindow(canvas -> window);
	free(canvas);
}
