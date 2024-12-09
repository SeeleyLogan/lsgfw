#define LSGFW_IMPLEMENTATION
#include <LSGFW/lsgfw.h>

u8_t init_lsgfw()
{
	universe = (lsgfw_universe_t)
	{
		NULL
	};

	return glfwInit();
}

lsgfw_universe_t* lsgfw_get_universe()
{
	return &universe;
}

