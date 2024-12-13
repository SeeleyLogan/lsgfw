#ifndef LSGFW_H
#define LSGFW_H

#include <glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_ds.h>  // love you Sean

#include <omp.h>

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

#define LSGFW_REALLLOC(...)	realloc(__VA_ARGS__)
#define LSGFW_FREE(...) 	free   (__VA_ARGS__)

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

typedef struct lsgfw_scripts_s
{
	void** handles;
	void*  (**Starts) (void*, u32_t);
	void*  (**Updates)(void*, u32_t);
	void*  (**Ends)	  (void*, u32_t);
	u32_t  script_c;
}
lsgfw_scripts_t;

typedef struct lsgfw_world_s
{
	GLFWwindow* window;
	void* global_ptr;
	lsgfw_scripts_t scripts;
}
lsgfw_world_t;

typedef struct lsgfw_univserse_s
{
	lsgfw_world_t* worlds;
	void* global_ptr;
}
lsgfw_universe_t;

// =========
//  lsgfw.c
// =========

LSGFW_API lsgfw_universe_t* init_lsgfw();

LSGFW_API lsgfw_universe_t* lsgfw_get_universe();
LSGFW_API void lsgfw_end_universe();

// =========
//  world.c
// =========

// returns index of world in universe.worlds
LSGFW_API u32_t lsgfw_new_world();

LSGFW_API void lsgfw_start_world(u32_t world_i, void (*script_cb)());
LSGFW_API void lsgfw_loop_world	(u32_t world_i, void (*script_cb)());
LSGFW_API void lsgfw_end_world	(u32_t world_i, void (*script_cb)());

// ==========
//  window.c
// ==========

LSGFW_API GLFWwindow* lsgfw_quick_window(const char* title);

// ===========
//  scripts.c
// ===========

#define LSGFW_ATTACH_GLOB_FAILED 	-1
#define LSGFW_NO_SCRIPTS 		-2

#if defined(__WIN32) || defined(__CYGWIN__)
	#define SHARED_LIB_EXT	   "dll"
	#define SHARED_LIB_EXT_LEN 3
#else
	#define SHARED_LIB_EXT	   "so"
	#define SHARED_LIB_EXT_LEN 2
#endif

#define LSGFW_SCRIPT_START 	1
#define LSGFW_SCRIPT_UPDATE 	2
#define LSGFW_SCRIPT_END	3

// Errors:
// 	negative: error code
// 	positive: amount of scripts that failed to attach
LSGFW_API i32_t lsgfw_attach_scripts(u32_t world_i, const char* path);

LSGFW_API void lsgfw_invoke_scripts(u32_t world_i, u8_t func_offset, void (*script_cb)(void*));
LSGFW_API void lsgfw_free_scripts  (u32_t world_i);

// ==============
//  shared_lib.c
// ==============

#define LSGFW_SHARED_LIB_LOAD_FAILED 0

LSGFW_API void* lsgfw_get_shared_lib_handle(const char* file_path);
LSGFW_API void* lsgfw_get_shared_lib_func  (void* handle, const char* func_name);
LSGFW_API void  lsgfw_close_shared_lib	   (void* handle);

#ifdef LSGFW_IMPLEMENTATION

#define STB_DS_IMPLEMENTATION
#include <stb/stb_ds.h>

#include <glob.h>
#include <dirent.h>

#if defined (_WIN32) || defined(__CYGWIN__)
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

lsgfw_universe_t universe;

#include <world.c>
#include <window.c>
#include <shared_lib.c>
#include <scripts.c>

#endif  // #ifdef LSGFW_IMPLEMENTATION

#endif  // #ifndef LSGFW_H

