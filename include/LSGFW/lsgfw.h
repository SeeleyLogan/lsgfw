#ifndef LSGFW_H
#define LSGFW_H

#define GLAD_GLAPI_EXPORT
#include <glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_ds.h>  // love you Sean

#include <omp.h>

#include <stdio.h>
#include <stdbool.h>

// you may thank me or hate me
typedef unsigned 	char		u8_t;
typedef signed		char		i8_t;
typedef unsigned 	short		u16_t;
typedef signed		short		i16_t;
typedef unsigned 	long		u32_t;
typedef signed		long		i32_t;
typedef unsigned	long long	u64_t;
typedef signed		long long	i64_t;

#define LSGFW_SUCCESS 	1
#define LSGFW_FAIL	0

typedef struct lsgfw_world_s lsgfw_world_t;

// =========
//  lsgfw.c
// =========

typedef struct lsgfw_univserse_s
{
	lsgfw_world_t* worlds;
}
lsgfw_universe_t;

u8_t init_lsgfw();

lsgfw_universe_t* lsgfw_get_universe();

// =========
//  world.c
// =========

struct lsgfw_world_s
{
	GLFWwindow* window;
};

lsgfw_world_t* lsgfw_new_world(GLFWwindow* window);

// ==========
//  window.c
// ==========

GLFWwindow* lsgfw_quick_window(const char* title, bool share);

#ifdef LSGFW_IMPLEMENTATION

#define STB_DS_IMPLEMENTATION
#include <stb/stb_ds.h>

lsgfw_universe_t universe;

#include <world.c>
#include <window.c>

#endif  // #ifdef LSGFW_IMPLEMENTATION

#endif  // #ifndef LSGFW_H

