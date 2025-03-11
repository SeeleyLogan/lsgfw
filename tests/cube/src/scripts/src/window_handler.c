#include <window_handler.h>

LSGFW_API void Start(lsgfw_universe_t* universe, u32_t world_i)
{
    lsgfw_world_t* world = &universe->world_v[world_i];

    glfwShowWindow(world->window);
}

LSGFW_API void Update(lsgfw_universe_t* universe, u32_t world_i)
{
    lsgfw_world_t* world = &universe->world_v[world_i];

	if (glfwGetKey(world->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(world->window, GLFW_TRUE);
}
