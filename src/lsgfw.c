#define LSGFW_IMPLEMENTATION
#include <LSGFW/lsgfw.h>

LSGFW_API u8_t init_lsgfw()
{
	universe = (lsgfw_universe_t)
	{
		NULL
	};

	omp_set_nested(1);

	return glfwInit();
}

LSGFW_API lsgfw_universe_t* lsgfw_get_universe()
{
	return &universe;
}

