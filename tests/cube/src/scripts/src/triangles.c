#include <cube.h>
#include <stdio.h>

float vertices[] =
{
	 0.5f,  0.5f, 0.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 1.0f
};

u32_t indices[] =
{
	0, 1, 2,
	3, 2, 1
};

GLuint ssbos[2] = { 0 };

GLuint shader_program = 0;

char* load_file_source(char* file_name);
#define free_file_source(file_source) arrfree(file_source)

LSGFW_EXPORT void* Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	#pragma omp critical
	{
		glfwMakeContextCurrent(universe->window);
		
		glGenBuffers(2, ssbos);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[0]);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[1]);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(indices),  indices,  GL_STATIC_DRAW);

		glfwMakeContextCurrent(NULL);
	}

	char* vertex_source   = load_file_source("./assets/shaders/test/vertex.glsl");
	char* fragment_source = load_file_source("./assets/shaders/test/fragment.glsl");

	if (!vertex_source || !fragment_source)
		return (void*) 0x1;

	#pragma omp critical
	{
		glfwMakeContextCurrent(universe->window);

		GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertex_shader,   1, (void*) &vertex_source,   NULL);
		glShaderSource(fragment_shader, 1, (void*) &fragment_source, NULL);

		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);

		shader_program = glCreateProgram();

		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		glfwMakeContextCurrent(NULL);
	}

	free_file_source(vertex_source);
	free_file_source(fragment_source);
	
	return NULL;
}

LSGFW_EXPORT void* Update(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];
	
	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);
			
		glUseProgram(shader_program);
		
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbos[0]);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbos[1]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(indices)/sizeof(u32_t));

		glfwMakeContextCurrent(NULL);
	}

	return NULL;
}

LSGFW_EXPORT void* End(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];
	
	return NULL;
}

char* load_file_source(char* file_name)
{
	FILE* f = fopen(file_name, "rb");
	if (!f)
		return LSGFW_FAIL;
	
	fseek(f, 0L, SEEK_END);
	long f_len = ftell(f);
	rewind(f);

	char* source = NULL;
	arrsetlen(source, f_len);
	fread(source, sizeof(char), f_len, f);

	fclose(f);

	return source;
}

