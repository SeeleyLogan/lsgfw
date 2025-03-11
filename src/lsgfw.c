#define LSGFW_IMPLEMENTATION
#include <lsgfw.h>

bool_t init_lsgfw()
{
	universe = (lsgfw_universe_t) { 0 };

	omp_set_nested(1);

	if (!glfwInit())
		return LSGFW_FAIL;

	return LSGFW_SUCCESS;
}

void run_lsgfw(void (*run_cb)())
{
	bool_t ending = 0;

	#pragma omp parallel shared(ending)
	{
		if (omp_get_thread_num() == 0)
		{
			while(!ending)
			{
				glfwPollEvents();
				LSGFW_SLEEP(1);
			}
		}
		
		if (omp_get_thread_num() == 1)
		{
			run_cb();
			
			ending = 1;
		}
	}
}

lsgfw_universe_t* lsgfw_get_universe()
{
	return &universe;
}

void lsgfw_end_universe()
{	
	for (u32_t i = 0; i < arrlen(universe.world_v); i++)
	{
		lsgfw_world_t* world = &universe.world_v[i];
		
		lsgfw_free_scripts(i);
		
		arrfree(world->scripts.handle_v);
		arrfree(world->scripts.Start_v);
		arrfree(world->scripts.Update_v);
		arrfree(world->scripts.End_v);
	}

	arrfree(universe.world_v);

	vkDestroyInstance(universe.vk_instance, NULL);
	glfwTerminate();
}
