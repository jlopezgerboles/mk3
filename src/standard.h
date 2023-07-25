#pragma once

typedef unsigned char u8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;

typedef float f32;
typedef double f64;

typedef char b8;

#define FPS 10
#define FRAMERATE_TARGET (1000 / FPS)

#define TRUE 1
#define FALSE 0

#define min(a, b)		(((a) < (b)) ? (a) : (b))
#define max(a, b)		(((a) > (b)) ? (a) : (b))
#define clamp(a, mi, ma)	min(max(a,mi)ma)
#define mercury_abs(a)		(((a) < 0) ? -(a) : (a))
#define sign(a)			((a > 0) - (a < 0))	// Here each component will return 1 or 0 if true or false.
#define vec2x(x0, y0, x1, y1)	(x0 * y1) - (y0 * x1)	// Cross product of 2 2D vectors.

typedef struct vec2f {
	f32 x;
	f32 y;
} vec2f;

typedef struct vec2 {
	i8 x;
	i8 y;
} vec2;

typedef struct vec3 {
	f32 x;
	f32 y;
	f32 z;
} vec3;

