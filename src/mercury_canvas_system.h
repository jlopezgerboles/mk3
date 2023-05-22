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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct mercury_canvas_framework {
	Display* display;
	Drawable window;
	Drawable root_window;
	i8 screen;
	XSetWindowAttributes* window_attributes;
	i64 window_attributes_mask;
	XVisualInfo* visual_info;
	i16 x, y;
	i16 width, height;
} mercury_canvas_framework;

mercury_canvas_framework* mercury_canvas_system_initialize();
void mercury_canvas_system_shutdown(mercury_canvas_framework* canvas);
