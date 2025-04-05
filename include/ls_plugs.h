#ifndef _LS_TYPES_INCLUDED
	#define _LS_TYPES_INCLUDED

	typedef unsigned 	char		ls_bool_t;
	typedef unsigned 	char		ls_u8_t;
	typedef signed		char		ls_i8_t;
	typedef unsigned 	short		ls_u16_t;
	typedef signed		short		ls_i16_t;
	typedef unsigned 	long		ls_u32_t;
	typedef signed		long		ls_i32_t;
	typedef unsigned	long long	ls_u64_t;
	typedef signed		long long	ls_i64_t;
#endif

#if !defined(LS_NO_SHORT_TYPES) && !defined(_LS_SHORT_TYPES_INCLUDED)
	#define _LS_SHORT_TYPES_INCLUDED

	#define bool_t ls_bool_t
	#define	u8_t   ls_u8_t
	#define i8_t   ls_i8_t
	#define u16_t  ls_u16_t
	#define i16_t  ls_i16_t
	#define u32_t  ls_u32_t
	#define i32_t  ls_i32_t
	#define u64_t  ls_u64_t
	#define i64_t  ls_i64_t
#endif

#ifndef LS_API
	#if defined(_WIN32)
		#ifdef __GNUC__
			#define LS_API __attribute__ ((dllexport)) extern
		#else
			#define LS_API __declspec(dllexport) extern
		#endif
	#elif defined(__GNUC__)
		#define LS_API __attribute__ ((visibility ("default"))) extern
	#endif
#endif

#ifndef LS_PLUGS_H
#define LS_PLUGS_H

typedef struct ls_plugs_outlet_s ls_plugs_outlet_t;
struct ls_plugs_outlet_s
{
	void*	 	user_ptr;
	ls_u32_t 	plug_c;
	void** 	 	plug_handle_v;
	void  	 (**plug_main_func_v)(ls_plugs_outlet_t*);
};

#ifndef LS_PLUGS_NO_SHORT_NAMES
	#define outlet_t   		ls_plugs_outlet_t
#endif

#ifdef LS_PLUGS_IMPLEMENTATION

#ifndef LS_PLUGS_NO_SHORT_NAMES
	#define NEW_OUTLET 		LS_PLUGS_NEW_OUTLET
	#define load_plugs 		ls_plugs_load_plugs
	#define free_outlet		ls_plugs_free_outlet
	#define invoke_plugs	ls_plugs_invoke_plugs
#endif

#define LS_PLUGS_NEW_OUTLET { NULL }

void ls_plugs_load_plugs (ls_plugs_outlet_t* outlet, const char* plugs_path, const char* regex);
void ls_plugs_free_outlet(ls_plugs_outlet_t* outlet);

void ls_plugs_invoke_plugs(ls_plugs_outlet_t* outlet);

typedef char** ls_plugs_glob_t;

ls_plugs_glob_t 	ls_plugs_glob	  (const char* glob_path, const char* pattern);
void 				ls_plugs_free_glob(ls_plugs_glob_t glob);

#define STB_DS_IMPLEMENTATION
#include <stb/stb_ds.h>

#if defined (_WIN32)
	#include <windows.h>
	
	#define GET_SHARED_LIBRARY_HANDLE 	LoadLibrary
	#define GET_SHARED_LIBRARY_FUNCTION (void*) GetProcAddress
	#define CLOSE_SHARED_LIBRARY		FreeLibrary
#else
	#include <dlfcn.h>
	#include <dirent.h>
	#include <fnmatch.h>

	#define GET_SHARED_LIBRARY_HANDLE(...) 	dlopen(__VA_ARGS__, RTLD_NOW)
	#define GET_SHARED_LIBRARY_FUNCTION 	dlsym
	#define CLOSE_SHARED_LIBRARY			dlclose
#endif

inline void ls_plugs_load_plugs(ls_plugs_outlet_t* outlet, const char* plugs_path, const char* regex)
{
	if (outlet->plug_handle_v)
		ls_plugs_free_outlet(outlet);

	ls_plugs_glob_t plug_glob = ls_plugs_glob(plugs_path, regex);

	if (!plug_glob)
		return;

	for (ls_u32_t i = 0; i < arrlenu(plug_glob); i++)
	{
		void* plug_handle    = GET_SHARED_LIBRARY_HANDLE(plug_glob[i]);
		void* plug_main_func = GET_SHARED_LIBRARY_FUNCTION(plug_handle, "PlugMain");

		if (!plug_handle || !plug_main_func)
			continue;

		outlet->plug_c++;
		arrput(outlet->plug_handle_v, 	 plug_handle);
		arrput(outlet->plug_main_func_v, plug_main_func);
	}
	
	ls_plugs_free_glob(plug_glob);
}

inline void ls_plugs_free_outlet(ls_plugs_outlet_t* outlet)
{
	for (ls_u32_t i = 0; i < outlet->plug_c; i++)
		CLOSE_SHARED_LIBRARY(outlet->plug_handle_v[i]);

	arrfree(outlet->plug_main_func_v);
	arrfree(outlet->plug_handle_v);
}

inline void ls_plugs_invoke_plugs(ls_plugs_outlet_t* outlet)
{
	for (ls_u32_t i = 0; i < outlet->plug_c; i++)
		outlet->plug_main_func_v[i](outlet);
}

inline ls_plugs_glob_t ls_plugs_glob(const char* glob_path, const char* pattern)
{
	ls_plugs_glob_t glob = NULL;
	ls_u32_t 		glob_path_len = strlen(glob_path);
	char* 		  	path_pattern  = NULL;
	ls_u32_t 		pattern_len   = strlen(pattern);

	arrsetlen(path_pattern, glob_path_len + pattern_len + 1);

	memcpy(path_pattern, glob_path, glob_path_len);
	memcpy(path_pattern + glob_path_len, pattern, pattern_len + 1);	

#if defined(_WIN32)
	WIN32_FIND_DATAA file_data;
	HANDLE file_handle = FindFirstFileA(path_pattern, &file_data);
	do
	{
		char* 	 full_path 	   = NULL;
		ls_u32_t file_name_len = strlen(file_data.cFileName);

		arrsetlen(full_path, glob_path_len + file_name_len + 1);

		memcpy(full_path, glob_path, glob_path_len);
		memcpy(full_path + glob_path_len, file_data.cFileName, file_name_len + 1);

		arrput(glob, full_path);
	}
	while (FindNextFileA(file_handle, &file_data));
#else

	DIR* dir = opendir(glob_path);

	if (!dir)
		return NULL;
	
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		char* 	 full_path 	= NULL;
		ls_u32_t d_name_len = strlen(entry->d_name);

		arrsetlen(full_path, glob_path_len + d_name_len + 2);

		memcpy(full_path, glob_path, glob_path_len);
		full_path[glob_path_len] = '/';
		memcpy(full_path + glob_path_len + 1, entry->d_name, d_name_len + 1);

		if (fnmatch(path_pattern, full_path, 0) != FNM_NOMATCH)	
			arrput(glob, full_path);
	}

	closedir(dir);
#endif

	return glob;
}

inline void ls_plugs_free_glob(ls_plugs_glob_t glob)
{
	for (ls_u32_t i = 0; i < arrlen(glob); i++)
		arrfree(glob[i]);

	arrfree(glob);
}

#endif  // #ifdef LS_PLUGS_IMPLEMENTATION
#endif  // #ifndef LS_PLUGS_H
