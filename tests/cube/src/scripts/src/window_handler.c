#include <cube.h>

LSGFW_EXPORT void Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	glfwMakeContextCurrent(world->window);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glfwMakeContextCurrent(NULL);

	glfwShowWindow(world->window);
}

LSGFW_EXPORT void Update(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	if (glfwGetKey(world->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(world->window, GLFW_TRUE);
}
