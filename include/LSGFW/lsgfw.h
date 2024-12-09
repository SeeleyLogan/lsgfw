#ifndef LSGFW_H
#define LSGFW_H

#include <glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_ds.h>  // love you Sean

#include <omp.h>

#include <stdio.h>
#include <stdbool.h>

#ifdef LSGFW_API_EXPORT
	#if defined(_WIN32) || defined(__CYGWIN__)
		#ifdef LSGFW_IMPLEMENTATION
			#ifdef __GNUC__
				#define LSGFW_API __attribute__ ((dllexport)) extern
			#else
				#define LSGFW_API __declspec(dllexport) extern
			#endif
		#else
			#ifdef __GNUC__
				#define LSGFW_API __attribute__ ((dllimport)) extern
			#else
				#define LSGFW_API __declspec(dllimport) extern
			#endif
		#endif
	#elif defined(__GNUC__) && defined(LSGFW_API_EXPORT_BUILD)
		#define LSGFW_API __attribute__ ((visibility ("default"))) extern
	#else
		#define LSGFW_API extern
	#endif
#else
	#define LSGFW_API extern
#endif

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

LSGFW_API u8_t init_lsgfw();

LSGFW_API lsgfw_universe_t* lsgfw_get_universe();

// =========
//  world.c
// =========

struct lsgfw_world_s
{
	GLFWwindow* window;
};

LSGFW_API lsgfw_world_t* lsgfw_new_world(GLFWwindow* window);

// ==========
//  window.c
// ==========

LSGFW_API GLFWwindow* lsgfw_quick_window(const char* title, bool share);

#ifdef LSGFW_IMPLEMENTATION

#define STB_DS_IMPLEMENTATION
#include <stb/stb_ds.h>

lsgfw_universe_t universe;

#include <world.c>
#include <window.c>

#endif  // #ifdef LSGFW_IMPLEMENTATION

#endif  // #ifndef LSGFW_H

