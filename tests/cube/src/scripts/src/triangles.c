#include <cube.h>
#include <stdio.h>

float vertices[] =
{
    -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 1.0f
};

GLuint ssbo;

GLuint shader_program = 0;

char* load_file_source(char* file_name);
#define free_file_source(file_source) arrfree(file_source)

LSGFW_EXPORT void* Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	#pragma omp critical
	{
		glfwMakeContextCurrent(universe->window);
		
		glGenBuffers(1, &ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glfwMakeContextCurrent(NULL);
	}
	
	char* vertex_source   = load_file_source("./assets/shaders/test/vertex.glsl");
	char* fragment_source = load_file_source("./assets/shaders/test/fragment.glsl");

	if (!vertex_source || !fragment_source)
		return (void*) 0x1;

	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);

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

unsigned long long i = 0;

LSGFW_EXPORT void* Update(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);
			
		glUseProgram(shader_program);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(world->window);
		
		glfwMakeContextCurrent(NULL);
	}

	if (i % 100 == 0)
		printf("%d\n", i);
	
	i++;

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

