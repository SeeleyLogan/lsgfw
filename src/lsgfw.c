#define LSGFW_IMPLEMENTATION
#include <LSGFW/lsgfw.h>

LSGFW_API lsgfw_universe_t* init_lsgfw()
{
	universe = (lsgfw_universe_t)
	{
		NULL
	};

	omp_set_nested(1);

	if (!glfwInit())
		return LSGFW_FAIL;

	return &universe;
}

LSGFW_API lsgfw_universe_t* lsgfw_get_universe()
{
	return &universe;
}

LSGFW_API void lsgfw_end_universe()
{	
	for (u32_t i = 0; i < arrlen(universe.worlds); i++)
	{
		lsgfw_world_t* world = &universe.worlds[i];
		
		lsgfw_free_scripts(i);
		
		arrfree(world->scripts.handles);
		arrfree(world->scripts.Starts);
		arrfree(world->scripts.Updates);
		arrfree(world->scripts.Ends);
	}

	arrfree(universe.worlds);

	glfwTerminate();
}

