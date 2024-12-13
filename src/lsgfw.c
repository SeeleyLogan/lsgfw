#define LSGFW_IMPLEMENTATION
#include <LSGFW/lsgfw.h>

LSGFW_API u8_t init_lsgfw(void (*run_cb)(lsgfw_universe_t*), void (*init_cb)(lsgfw_universe_t*))
{
	universe = (lsgfw_universe_t) { 0 };

	omp_set_nested(1);	

	if (!glfwInit())
		return LSGFW_FAIL;

	init_cb(&universe);

	#pragma omp parallel sections shared(universe)
	{
		#pragma omp parallel master
		{
			while(!universe.ending)
			{
				glfwPollEvents();
			}

			glfwTerminate();
		}

		#pragma omp section
		{
			run_cb(&universe);
		}
	}

	return LSGFW_SUCCESS;
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

	universe.ending = LSGFW_TRUE;
}

