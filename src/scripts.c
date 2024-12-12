#include <stdio.h>

LSGFW_API i32_t lsgfw_attach_scripts(u32_t world_i, const char* path)
{
	glob_t script_glob;

	// concat *.so (*.dll on win) to path
	u32_t path_len = strlen(path);
	char path_regex[path_len + SHARED_LIB_EXT_LEN + 3];
	memcpy(path_regex, path, path_len);
	memcpy(path_regex + path_len, "*."SHARED_LIB_EXT, SHARED_LIB_EXT_LEN + 2);
	path_regex[path_len + SHARED_LIB_EXT_LEN + 2] = 0;  // null term

	if (glob(path_regex, 0, NULL, &script_glob))
		return LSGFW_ATTACH_GLOB_FAILED;

	if (!script_glob.gl_pathc)
		return LSGFW_NO_SCRIPTS;	

	lsgfw_world_t* world = &universe.worlds[world_i];
	world->scripts.script_c += script_glob.gl_pathc;
	
	u32_t fail_c = 0;
	for (int i = 0; i < script_glob.gl_pathc; i++)
	{
		void* script_handle = lsgfw_get_shared_lib_handle(script_glob.gl_pathv[i]);

		if (!script_handle)
		{
			fail_c++;
			continue;
		}

		arrput(world->scripts.handles, script_handle);
		arrput(world->scripts.Starts,  lsgfw_get_shared_lib_func(script_handle, "Start"));
		arrput(world->scripts.Updates, lsgfw_get_shared_lib_func(script_handle, "Update"));
		arrput(world->scripts.Ends,    lsgfw_get_shared_lib_func(script_handle, "End"));
	}
	
	world->scripts.script_c -= fail_c;

	globfree(&script_glob);
	
	return fail_c;
}

LSGFW_API void lsgfw_invoke_scripts(u32_t world_i, u8_t func_offset, void (*script_cb)(void*))
{
	void* (**script_funcs)(lsgfw_universe_t*, u32_t) = ((void* (***)(lsgfw_universe_t*, u32_t)) (&universe.worlds[world_i].scripts))[func_offset];

	if (script_cb)
		#pragma omp parallel shared(universe)
		{
			#pragma omp for
			for (u32_t i = 0; i < universe.worlds[world_i].scripts.script_c; i++)
				script_cb(script_funcs[i](&universe, world_i));
		}
	else
		#pragma omp parallel shared(universe)
		{
			#pragma omp for
			for (u32_t i = 0; i < universe.worlds[world_i].scripts.script_c; i++)
				script_funcs[i](&universe, world_i);
		}
}

LSGFW_API void lsgfw_free_scripts(u32_t world_i)
{
	lsgfw_scripts_t* scripts = &universe.worlds[world_i].scripts;

	for (u32_t i = 0; i < scripts->script_c; i++)
		lsgfw_close_shared_lib(scripts->handles[i]);
}

