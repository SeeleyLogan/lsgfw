#include <cube.h>
#include <stdio.h>

float vertices[] =
{
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f
};

GLuint ssbo;

LSGFW_EXPORT void* Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);
		
		glGenBuffers(1, &ssbo);

		glfwMakeContextCurrent(NULL);
	}
	
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
	
	return NULL;
}

LSGFW_EXPORT void* Update(lsgfw_universe_t* universe, u32_t world_i)
{
	//lsgfw_world_t* world = &universe->world_v[world_i];
	
	return NULL;
}

LSGFW_EXPORT void* End(lsgfw_universe_t* universe, u32_t world_i)
{
	//lsgfw_world_t* world = &universe->world_v[world_i];
	
	return NULL;
}
