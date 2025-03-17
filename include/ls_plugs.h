#ifndef LS_PLUGS_H
#define LS_PLUGS_H

#ifdef LS_PLUG
	#if defined(_WIN32)
		#ifdef __GNUC__
			#define LS_PLUGS_API __attribute__ ((dllexport)) extern
		#else
			#define LS_PLUGS_API __declspec(dllexport) extern
		#endif
	#elif defined(__GNUC__)
		#define LS_PLUGS_API __attribute__ ((visibility ("default"))) extern
	#endif
#endif

typedef unsigned long long ls_plug_id_t;
typedef char** 			   ls_plugs_glob_t;

typedef struct ls_plugs_outlet_s ls_plugs_outlet_t;
struct ls_plugs_outlet_s
{
	void*		user_ptr;
	void** 		plug_handle_v;
	void	(***plug_func_v)(ls_plugs_outlet_t*, ls_plug_id_t);
};

#ifdef LS_PLUGS_IMPLEMENTATION

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

#define LS_PLUGS_NEW_OUTLET { NULL, NULL }

void ls_plugs_load_plugs(ls_plugs_outlet_t* outlet, const char* plugs_path, const char* regex);
void ls_plugs_free_outlet(ls_plugs_outlet_t* outlet);

ls_plugs_glob_t ls_plugs_glob		(const char* glob_path, const char* pattern);
void 			ls_plugs_free_glob	(ls_plugs_glob_t glob);

void ls_plugs_load_plugs(ls_plugs_outlet_t* outlet, const char* plugs_path, const char* regex)
{
	if (outlet->plug_handle_v)
		ls_plugs_free_outlet(outlet);

	ls_plugs_glob_t plug_glob = ls_plugs_glob(plugs_path, regex);

	if (!plug_glob)
		return;

	unsigned long fail_c = 0;
	for (int i = 0; i < arrlenu(plug_glob); i++)
	{
		void* plug_handle = GET_SHARED_LIBRARY_HANDLE(plug_glob[i]);

		if (!plug_handle)
			continue;

		arrput(outlet->plug_handle_v, plug_handle);
	}
	
	ls_plugs_free_glob(plug_glob);
}

void ls_plugs_free_outlet(ls_plugs_outlet_t* outlet)
{
	for (unsigned int i = 0; i < arrlenu(outlet->plug_handle_v); i++)
		for (unsigned int j = 0; j < arrlenu(outlet->plug_func_v[i]); j++)
			arrfree(outlet->plug_func_v[i]);

	arrfree(outlet->plug_func_v);
	arrfree(outlet->plug_handle_v);
}

ls_plugs_glob_t ls_plugs_glob(const char* glob_path, const char* pattern)
{
	ls_plugs_glob_t glob = NULL;
	unsigned long 	glob_path_len = strlen(glob_path);
	char* 		  	path_pattern = NULL;
	unsigned long 	pattern_len = strlen(pattern);

	arrsetlen(path_pattern, glob_path_len + pattern_len + 1);

	memcpy(path_pattern, glob_path, glob_path_len);
	memcpy(path_pattern + glob_path_len, pattern, pattern_len + 1);	

#if defined(_WIN32)
	WIN32_FIND_DATAA file_data;
	HANDLE file_handle = FindFirstFileA(path_pattern, &file_data);
	do
	{
		char* full_path = NULL;
		unsigned long file_name_len = strlen(file_data.cFileName);

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
		char* full_path = NULL;
		unsigned long d_name_len = strlen(entry->d_name);

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

void ls_plugs_free_glob(ls_plugs_glob_t glob)
{
	for (unsigned long i = 0; i < arrlen(glob); i++)
		arrfree(glob[i]);

	arrfree(glob);
}

#endif  // #ifdef  LS_PLUGS_IMPLEMENTATION
#endif  // #ifndef LS_PLUGS_H
