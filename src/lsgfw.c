#define LSGFW_IMPLEMENTATION
#include <LSGFW/lsgfw.h>

LSGFW_API bool_t init_lsgfw()
{
	universe = (lsgfw_universe_t) { 0 };

	omp_set_nested(1);	

	if (!glfwInit())
		return LSGFW_FAIL;

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	universe.window = glfwCreateWindow(1, 1, "botnet.exe", NULL, NULL);

	glfwMakeContextCurrent(universe.window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		return LSGFW_FAIL;

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glfwMakeContextCurrent(NULL);

	return LSGFW_SUCCESS;
}

LSGFW_API void run_lsgfw(void (*run_cb)(lsgfw_universe_t*))
{
	#pragma omp parallel sections shared(universe)
	{
		#pragma omp parallel master
		{
			while(!universe.ending)
				glfwPollEvents();

			glfwTerminate();
		}

		#pragma omp section
		{
			run_cb(&universe);
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

	universe.ending = LSGFW_TRUE;
}

