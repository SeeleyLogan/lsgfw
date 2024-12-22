#include <cube.h>

lsgfw_world_t* world;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	#pragma omp critical
	{
		glfwMakeContextCurrent(window);

		glViewport(0, 0, width, height);	
		
		glfwMakeContextCurrent(NULL);
	}
}

LSGFW_EXPORT void* Start(lsgfw_universe_t* universe, u32_t world_i)
{
	world = &universe->world_v[world_i];
	
	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glfwMakeContextCurrent(NULL);
	}

	glfwShowWindow(world->window);
	glfwSetFramebufferSizeCallback(world->window, framebuffer_size_callback);
	
	return NULL;
}

LSGFW_EXPORT void* Update(lsgfw_universe_t* universe, u32_t world_i)
{	
	if (glfwGetKey(world->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(world->window, GLFW_TRUE);

	return NULL;
}

LSGFW_EXPORT void* End(lsgfw_universe_t* universe, u32_t world_i)
{
	return NULL;
}

