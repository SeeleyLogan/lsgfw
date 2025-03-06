#ifndef LSGFW_H
#define LSGFW_H

#define GLAD_GLAPI_EXPORT
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stb/stb_ds.h>

#include <omp.h>

#ifdef LSGFW_SCRIPT
	#if defined(_WIN32)
		#ifdef __GNUC__
			#define LSGFW_API __attribute__ ((dllexport)) extern
		#else
			#define LSGFW_API __declspec(dllexport) extern
		#endif
	#elif defined(__GNUC__)
		#define LSGFW_API __attribute__ ((visibility ("default"))) extern
	#endif
#else
	#if defined(_WIN32)
		#if defined(LSGFW_IMPLEMENTATION)
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
	#elif defined(__GNUC__) && defined(LSGFW_IMPLEMENTATION)
		#define LSGFW_API __attribute__ ((visibility ("default"))) extern
	#else
		#define LSGFW_API extern
	#endif
#endif

#define LSGFW_SUCCESS 	1
#define LSGFW_FAIL		0

#define LSGFW_FALSE 	0
#define LSGFW_TRUE 		1

typedef unsigned 	char		bool_t;
typedef unsigned 	char		u8_t;
typedef signed		char		i8_t;
typedef unsigned 	short		u16_t;
typedef signed		short		i16_t;
typedef unsigned 	int			u32_t;
typedef signed		int			i32_t;
typedef unsigned	long long	u64_t;
typedef signed		long long	i64_t;

typedef struct lsgfw_world_s lsgfw_world_t;

typedef struct lsgfw_kv_s
{
	char* key;
	void* value;
}
lsgfw_kv_t;

typedef struct lsgfw_univserse_s
{
	GLFWwindow*	   	window;
	GLuint			VAO;
	lsgfw_world_t* 	world_v;
	lsgfw_kv_t*		global;
	bool_t 		   	ending;
}
lsgfw_universe_t;

typedef struct lsgfw_scripts_s
{
	void** 	handle_v;
	void  	(**Install_v)(lsgfw_universe_t*, u32_t);
	void  	(**Start_v)  (lsgfw_universe_t*, u32_t);
	void  	(**Update_v) (lsgfw_universe_t*, u32_t);
	void  	(**End_v)    (lsgfw_universe_t*, u32_t);
}
lsgfw_scripts_t;

struct lsgfw_world_s
{
	GLFWwindow* 	window;
	GLuint			VAO;
	lsgfw_kv_t*		global;
	lsgfw_scripts_t scripts;
};

typedef char** lsgfw_glob_t;

#ifndef LSGFW_SCRIPT

// =========
//  lsgfw.c
// =========

LSGFW_API bool_t 			init_lsgfw();
LSGFW_API void 				run_lsgfw(void (*run_cb)());

LSGFW_API lsgfw_universe_t* lsgfw_get_universe();
LSGFW_API void 				lsgfw_end_universe();

// ========
//  util.c
// ========

LSGFW_API u8_t lsgfw_glob	  (lsgfw_glob_t* glob, const char* glob_path, const char* pattern);
LSGFW_API void lsgfw_free_glob(lsgfw_glob_t glob);

// =========
//  world.c
// =========

// returns index of world in universe.worlds
LSGFW_API u32_t lsgfw_new_world();

LSGFW_API void lsgfw_start_world(u32_t world_i);
LSGFW_API void lsgfw_loop_world	(u32_t world_i);
LSGFW_API void lsgfw_end_world	(u32_t world_i);

// ==========
//  window.c
// ==========

LSGFW_API GLFWwindow* lsgfw_quick_window(const char* title);

// ===========
//  scripts.c
// ===========

#define LSGFW_ATTACH_GLOB_FAILED -1
#define LSGFW_NO_SCRIPTS 		 -2
#define LSGFW_SCRIPT_INSTALL 	  0
#define LSGFW_SCRIPT_START 		  1
#define LSGFW_SCRIPT_UPDATE 	  2
#define LSGFW_SCRIPT_END		  3

// Errors:
// 	negative: error code
// 	positive: amount of scripts that failed to attach
LSGFW_API i32_t lsgfw_attach_scripts(u32_t world_i, const char* path);
LSGFW_API void 	lsgfw_invoke_scripts(u32_t world_i, u8_t func_offset);
LSGFW_API void 	lsgfw_free_scripts	(u32_t world_i);

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

#if defined (_WIN32)
	#include <windows.h>
#else
	#include <dlfcn.h>
	#include <dirent.h>
	#include <fnmatch.h>
#endif

lsgfw_universe_t universe;

#include <util.c>
#include <world.c>
#include <window.c>
#include <shared_lib.c>
#include <scripts.c>

#include <glad/glad.c>

#endif  // #ifdef LSGFW_IMPLEMENTATION
#endif  // #ifndef LSGFW_SCRIPT
#endif  // #ifndef LSGFW_H
