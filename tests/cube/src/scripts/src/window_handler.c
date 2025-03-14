#include <cube.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

LSGFW_API void Install(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	glfwMakeContextCurrent(world->window);

	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &world->VAO);

	glfwSetFramebufferSizeCallback(world->window, framebuffer_size_callback);  
	
	glfwMakeContextCurrent(NULL);
}

LSGFW_API void Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	glfwMakeContextCurrent(world->window);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glfwMakeContextCurrent(NULL);

	glfwShowWindow(world->window);
}

LSGFW_API void Update(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	if (glfwGetKey(world->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(world->window, GLFW_TRUE);
}
