#include <cube.h>

int width, height;
bool_t resize_pending = LSGFW_FALSE;

void framebuffer_size_cb(GLFWwindow* window, int _width, int _height)
{
	#pragma omp critical
	{
		width = _width;
		height = _height;
		resize_pending = LSGFW_TRUE;
	}	
}

LSGFW_EXPORT void* Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];
	
	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glfwMakeContextCurrent(NULL);
	}

	glfwShowWindow(world->window);
	glfwSetFramebufferSizeCallback(world->window, framebuffer_size_cb);
	
	return NULL;
}

LSGFW_EXPORT void* Update(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];
	
	if (resize_pending)
	{
		resize_pending = LSGFW_FALSE;
		
		glfwGetWindowSize(world->window, &width, &height);
		#pragma omp critical
		{
			glfwMakeContextCurrent(world->window);
		
			glViewport(0, 0, width, height);

			glfwMakeContextCurrent(NULL);
		}
	}

	if (glfwGetKey(world->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(world->window, GLFW_TRUE);
	
	return NULL;
}

LSGFW_EXPORT void* End(lsgfw_universe_t* universe, u32_t world_i)
{
	return NULL;
}

