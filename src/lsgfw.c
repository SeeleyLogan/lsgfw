#define LSGFW_IMPLEMENTATION
#include <lsgfw.h>

LSGFW_API bool_t init_lsgfw()
{
	universe = (lsgfw_universe_t) { 0 };

	omp_set_nested(1);

	if (!glfwInit())
		return LSGFW_FAIL;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#ifdef __APPLE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	universe.window = glfwCreateWindow(800, 600, "lsgfw_universe_window", NULL, NULL);

	glfwMakeContextCurrent(universe.window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		return LSGFW_FAIL;

	glGenVertexArrays(1, &universe.VAO);

	glfwMakeContextCurrent(NULL);

	return LSGFW_SUCCESS;
}

LSGFW_API void run_lsgfw(void (*run_cb)())
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

LSGFW_API lsgfw_universe_t* lsgfw_get_universe()
{
	return &universe;
}

LSGFW_API void lsgfw_end_universe()
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

	glfwDestroyWindow(universe.window);
	glfwTerminate();
}
