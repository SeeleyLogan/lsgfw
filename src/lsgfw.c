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
	// todo: free all allocated memory by worlds, and their members

	glfwTerminate();
}

