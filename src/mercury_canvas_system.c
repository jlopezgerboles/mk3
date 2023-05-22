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

#include "standard.h"
#include "mercury_canvas_system.h"

#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* 
 * - Function: mercury_canvas_framework_create().
 * - Returns: Provides an empty canvas framework.
 */
mercury_canvas_framework* mercury_canvas_framework_create() {
	mercury_canvas_framework* canvas;
	canvas = malloc(sizeof(mercury_canvas_framework));
	if(canvas) printf("[OK] Empty mercury canvas framework created.\n");
	canvas -> display = NULL;
	canvas -> window = NULL;
	canvas -> root_window = NULL;
	canvas -> screen = NULL;
	canvas -> window_attributes = NULL;
	canvas -> window_attributes_mask = NULL;
	canvas -> visual_info = NULL;
	return canvas;
}

/* 
 * - Function: mercury_canvas_system_display().
 * - Returns: Provides a pointer to the x11 display later assigned to the canvas framework.
 */
Display* mercury_canvas_system_display() {
	Display* display = XOpenDisplay(NULL); // Further analysis required
	return display;
}

/* 
 * - Function: mercury_canvas_system_screen().
 * - Returns: Provides the x11 screen later assigned to the canvas framework.
 */
i8 mercury_canvas_system_screen(mercury_canvas_framework* canvas) {
	i8 screen = XDefaultScreen(canvas -> display);
	return screen;
}

/* 
 * - Function: mercury_canvas_system_root_window().
 * - Returns: Provides the x11 root window later assigned to the canvas framework.
 * - Prerequisite: Requires the display and screen of the canvas framework already defined.
 */
Drawable mercury_canvas_system_root_window(mercury_canvas_framework* canvas) {
	Drawable root_window = XRootWindow(canvas -> display, canvas -> screen);
	return root_window;
}

/* 
 * - Function: mercury_canvas_system_window_attributes_create().
 * - Returns: Provides a pointer to an empty x11 window attributes structure.
 */
XSetWindowAttributes* mercury_canvas_system_window_attributes_create() {
	XSetWindowAttributes* window_attributes;
	window_attributes = malloc(sizeof(XSetWindowAttributes));
	window_attributes -> background_pixmap = NULL;		/* background, None, or ParentRelative */
	window_attributes -> background_pixel = NULL;		/* background pixel */
	window_attributes -> border_pixmap = NULL;		/* border of the window or CopyFromParent */
	window_attributes -> border_pixel = NULL;		/* border pixel value */
	window_attributes -> bit_gravity = NULL;		/* one of bit gravity values */
	window_attributes -> win_gravity = NULL;		/* one of the window gravity values */
	window_attributes -> backing_store = NULL;		/* NotUseful, WhenMapped, Always */
	window_attributes -> backing_planes = NULL;		/* planes to be preserved if possible */
	window_attributes -> backing_pixel = NULL;		/* value to use in restoring planes */
	window_attributes -> save_under = NULL;			/* should bits under be saved? (popups) */
	window_attributes -> event_mask = NULL;			/* set of events that should be saved */
	window_attributes -> do_not_propagate_mask = NULL;	/* set of events that should not propagate */
	window_attributes -> override_redirect = NULL;		/* boolean value for override_redirect */
	window_attributes -> colormap = NULL;			/* color map to be associated with window */
	window_attributes -> cursor = NULL;			/* cursor to be displayed (or None) */
	return window_attributes;
}

/* 
 * - Function: mercury_canvas_system_window_attributes_define().
 * - Returns: Defines the parameters of the x11 window attributes structure.
 * - Prerequisite: Requires the previous creastion of the x11 window attributes.
 */
void  mercury_canvas_system_window_attributes_define(XSetWindowAttributes* window_attributes) {
//	window_attributes -> background_pixmap = NULL;		/* background, None, or ParentRelative */
//	window_attributes -> background_pixel = NULL;		/* background pixel */
//	window_attributes -> border_pixmap = NULL;		/* border of the window or CopyFromParent */
	window_attributes -> border_pixel = 0;			/* border pixel value */
//	window_attributes -> bit_gravity = NULL;		/* one of bit gravity values */
//	window_attributes -> win_gravity = NULL;		/* one of the window gravity values */
//	window_attributes -> backing_store = NULL;		/* NotUseful, WhenMapped, Always */
//	window_attributes -> backing_planes = NULL;		/* planes to be preserved if possible */
//	window_attributes -> backing_pixel = NULL;		/* value to use in restoring planes */
//	window_attributes -> save_under = NULL;			/* should bits under be saved? (popups) */
//	window_attributes -> event_mask = NULL;			/* set of events that should be saved */
//	window_attributes -> do_not_propagate_mask = NULL;	/* set of events that should not propagate */
//	window_attributes -> override_redirect = NULL;		/* boolean value for override_redirect */
//	window_attributes -> colormap = NULL;			/* color map to be associated with window */
//	window_attributes -> cursor = NULL;			/* cursor to be displayed (or None) */
}

/* 
 * - Function: mercury_canvas_system_window_attributes().
 * - Returns: Provides a pointer to the x11 window attributes later assigned to the canvas framework.
 */
XSetWindowAttributes* mercury_canvas_system_window_attributes() {
	XSetWindowAttributes* window_attributes;
	window_attributes = mercury_canvas_system_window_attributes_create();
	mercury_canvas_system_window_attributes_define(window_attributes);
	return window_attributes;
}

/* 
 * - Function: mercury_canvas_system_window_attributes_mask().
 * - Returns: Provides the x11 window attributes mask later assigned to the canvas framework.
 */
i64 mercury_canvas_system_window_attribute_mask() {
	i64 window_attribute_mask;
	window_attribute_mask = // Comment out the values below that need to be defined.
//	CWBackPixmap
//	|CWBackPixel
//	|CWBorderPixmap
	CWBorderPixel
//	|CWBitGravity
//	|CWWinGravity
//	|CWBackingStore
//	|CWBackingPlanes
//	|CWBackingPixel
//	|CWOverrideRedirect
//	|CWSaveUnder
//	|CWEventMask
//	|CWDontPropagate
//	|CWColormap
//	|CWCursor
	;
	return window_attribute_mask;
}

/* 
 * - Function: mercury_canvas_system_visual_info().
 * - Returns: Provides an empty x11 visual info structure later assigned to the canvas framework.
 */
XVisualInfo* mercury_canvas_system_visual_info() {
	XVisualInfo* visual_info;
	visual_info = malloc(sizeof(XVisualInfo));
	visual_info -> visual = NULL;
	visual_info -> visualid = NULL;
	visual_info -> screen = NULL;
	visual_info -> depth = NULL;
	visual_info -> class = NULL;
	visual_info -> red_mask = NULL;
	visual_info -> green_mask = NULL;
	visual_info -> blue_mask = NULL;
	visual_info -> colormap_size = NULL;
	visual_info -> bits_per_rgb = NULL;
	return visual_info;
}

/* 
 * - Function: mercury_canvas_system_window().
 * - Returns: Provides the x11 window later assigned to the canvas framework.
 */
Drawable mercury_canvas_system_window(mercury_canvas_framework* canvas) {
	Drawable window = XCreateWindow(
		canvas -> display,
		canvas -> root_window,
		300,		// Currently hardcoded.
		300,		// Currently hardcoded.
		800,		// Currently hardcoded.
		500,		// Currently hardcoded.
		canvas -> window_attributes -> border_pixel,
		canvas -> visual_info -> depth,
		InputOutput,
		canvas -> visual_info -> visual,
		canvas -> window_attributes_mask,
		canvas -> window_attributes
	);
	return window;
}

/* 
 * - Function: mercury_canvas_system_initialize().
 * - Returns: Provides a fully defined canvas framework for the game.
 */
mercury_canvas_framework* mercury_canvas_system_initialize() {
	mercury_canvas_framework* canvas = mercury_canvas_framework_create();
	canvas -> display = mercury_canvas_system_display();
	if (canvas -> display) printf("[OK] Mercury canvas display assigned.\n");
	canvas -> screen = mercury_canvas_system_screen(canvas);
	if (canvas -> screen) printf("[OK] Mercury canvas screen assigned.\n");
	canvas -> root_window = mercury_canvas_system_root_window(canvas);
	if (canvas -> root_window) printf("[OK] Mercury canvas root window assigned.\n");
	canvas -> window_attributes = mercury_canvas_system_window_attributes();
	if (canvas -> window_attributes) printf("[OK] Mercury canvas window attributes assigned.\n");
	canvas -> window_attributes_mask = mercury_canvas_system_window_attribute_mask();
	if (canvas -> window_attributes_mask) printf("[OK] Mercury canvas window attributes mask assigned.\n");
	canvas -> visual_info = mercury_canvas_system_visual_info();
	if (canvas -> visual_info) printf("[OK] Mercury canvas visual info assigned.\n");
	canvas -> window = mercury_canvas_system_window(canvas);
	if (canvas -> window) printf("[OK] Mercury canvas window assigned.\n");
	XMapWindow(canvas -> display, canvas -> window);
	return canvas;
}

/* 
 * - Function: mercury_canvas_system_shutdown(mercury_canvas_framework* canvas).
 * - Returns: Shuts down all the canvas related variables and frees all memory related to this system.
 */
void mercury_canvas_system_shutdown(mercury_canvas_framework* canvas) {
	XDestroyWindow(canvas -> display, canvas -> window);
	XCloseDisplay(canvas -> display);
	free(canvas);
}
