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

#include "src/standard.h"
#include "src/canvas_system.h"
#include "src/blitter_system.h"
#include "src/mercury_canvas_system.h"

#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>

const char* NAME = "mk3";

//-----------------------------------------------------------------------------------------------------------------------
// SDL ACTIVATION.
#define SDL // COMMENT OUT TO ENABLE THE SDL INITIALIZATION FUNCTIONS.
// SDL ACTIVATION.
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
// MERCURY ENGINE ACTIVATION.
//#define MERCURY // COMMENT OUT TO ENABLE THE USE OF THE MERCURY INITIALIZATION FUNCTIONS.
// MERCURY ENGINE ACTIVATION.
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
// Testing variables.
//#define TESTING_MODE // COMMENT OUT TO DISABLE TESTING MODE.
// End Testing variables.
//-----------------------------------------------------------------------------------------------------------------------

void main(int argc, char **argv) {

//-----------------------------------------------------------------------------------------------------------------------
// THIS IS THE MODULE OF INITIALIZATION FUNCTIONS USING THE SLD LIBRARY.
#ifdef SDL
	canvas_framework* canvas = canvas_system_initialize(NAME);
	blitter_framework* blitter = blitter_system_initialize(canvas);
	SDL_Event event;
#endif
// THIS IS THE MODULE OF INITIALIZATION FUNCTIONS USING THE SLD LIBRARY.
//-----------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------
// THIS IS THE MERCURY MODULE OF INITIALIZATION FUNCTIONS.
#ifdef MERCURY
	mercury_canvas_framework* mercury_canvas = mercury_canvas_system_initialize();
	XEvent x11_event;
#endif
// THIS IS THE MERCURY MODULE OF INITIALIZATION FUNCTIONS.
//-----------------------------------------------------------------------------------------------------------------------

	b8 quit = FALSE;
	while(quit == FALSE) {
	
	// --------------------------------------------------------------------------------------------------------------
	// SDL GAME LOOP
	#ifdef SDL	
		//SDL_UpdateWindowSurface(canvas -> window);
		while(SDL_PollEvent(&event) != 0) {
			if((event.type == SDL_QUIT) || (event.key.keysym.sym == SDLK_ESCAPE)) {
				quit = TRUE;
				blitter_system_shutdown(blitter);
				canvas_system_shutdown(canvas);
				SDL_Quit();
			}
		}
	#endif
	// SDL GAME LOOP
	// --------------------------------------------------------------------------------------------------------------
	
	// --------------------------------------------------------------------------------------------------------------
	// MERCURY GAME LOOP
	#ifdef MERCURY
		XNextEvent(mercury_canvas -> display, &x11_event);
		//if (x11_event.type == Expose)
		if (x11_event.type == KeyPress) {
			mercury_canvas_system_shutdown(mercury_canvas);
			//break;
		}
	#endif
	// MERCURY GAME LOOP
	// --------------------------------------------------------------------------------------------------------------
	
	}
}
