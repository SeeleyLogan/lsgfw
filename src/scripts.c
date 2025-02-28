LSGFW_API i32_t lsgfw_attach_scripts(u32_t world_i, const char* path)
{
	lsgfw_glob_t script_glob = NULL;

	#if defined(__WIN32) || defined(__CYGWIN__)

	if (!lsgfw_glob(&script_glob, path, "*.dll"))
		return LSGFW_ATTACH_GLOB_FAILED;

	#else

	if (!lsgfw_glob(&script_glob, path, "*.so"))
		return LSGFW_ATTACH_GLOB_FAILED;

	#endif

	if (!arrlenu(script_glob))
		return LSGFW_NO_SCRIPTS;	

	lsgfw_world_t* world = &universe.world_v[world_i];
	
	u32_t fail_c = 0;	
	for (int i = 0; i < arrlenu(script_glob); i++)
	{
		void* script_handle = lsgfw_get_shared_lib_handle(script_glob[i]);

		if (!script_handle)
		{
			fail_c++;
			continue;
		}
		
		void* (*start)()  = lsgfw_get_shared_lib_func(script_handle, "Start");
		void* (*update)() = lsgfw_get_shared_lib_func(script_handle, "Update");
		void* (*end)()	  = lsgfw_get_shared_lib_func(script_handle, "End");
		
		if (!start || !update || !end)
		{
			fail_c++;
			continue;
		}

		arrput(world->scripts.handle_v, script_handle);
		arrput(world->scripts.Start_v,  start);
		arrput(world->scripts.Update_v, update);
		arrput(world->scripts.End_v,    end);
	}
	
	lsgfw_free_glob(script_glob);
	
	return fail_c;
}

LSGFW_API void lsgfw_invoke_scripts(u32_t world_i, u8_t func_offset, void (*script_cb)(void*))
{
	void* (**script_funcs)(lsgfw_universe_t*, u32_t);

	switch (func_offset)
	{
		case LSGFW_SCRIPT_START:
			script_funcs = universe.world_v[world_i].scripts.Start_v;
			break;
		case LSGFW_SCRIPT_UPDATE:
			script_funcs = universe.world_v[world_i].scripts.Update_v;
			break;
		case LSGFW_SCRIPT_END:
			script_funcs = universe.world_v[world_i].scripts.End_v;
	}

	if (script_cb)
		for (u32_t i = 0; i < arrlenu(universe.world_v[world_i].scripts.handle_v); i++)
			script_cb(script_funcs[i](&universe, world_i));
	else
		for (u32_t i = 0; i < arrlenu(universe.world_v[world_i].scripts.handle_v); i++)	
			script_funcs[i](&universe, world_i);
}

LSGFW_API void lsgfw_free_scripts(u32_t world_i)
{
	lsgfw_scripts_t* scripts = &universe.world_v[world_i].scripts;

	for (u32_t i = 0; i < arrlen(scripts->handle_v); i++)
		lsgfw_close_shared_lib(scripts->handle_v[i]);
}

