#include <cube.h>

#define FOV   (70 * M_PI/180.0)
#define ZNEAR 0.5f
#define ZFAR  100.0f

char* load_file_source(char* file_name);
#define free_file_source(file_source) arrfree(file_source)

float vertices[] =
{
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
};

u32_t indices[] =
{
    0, 1, 2,
    1, 3, 2,

    7, 4, 6,
    7, 5, 4,

    5, 1, 0,
    0, 4, 5,

    3, 7, 6,
    3, 6, 2,

    0, 2, 6,
    0, 6, 4,

    5, 7, 3,
    3, 1, 5
};

GLuint ssbos[2] = { 0 };
GLuint shader_program;

vec3 camera_pos = { 3.0, 1.0, 3.0 };

mat4 view = GLM_MAT4_IDENTITY_INIT;
mat4 proj = GLM_MAT4_IDENTITY_INIT;
mat4 vp   = GLM_MAT4_IDENTITY_INIT;

LSGFW_API void Start(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	// create buffers
	glfwMakeContextCurrent(universe->window);
	glBindVertexArray(world->VAO);
	
	glGenBuffers(2, ssbos);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[0]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[1]);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(indices),  indices,  GL_STATIC_DRAW);

	// compile shaders
	char* vertex_source   = load_file_source("./assets/shaders/test/vertex.glsl");
	char* fragment_source = load_file_source("./assets/shaders/test/fragment.glsl");

	if (!vertex_source || !fragment_source)
	{
		printf("big bad stinky error (shader source didnt load)");
		return;
	}

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

	free_file_source(vertex_source);
	free_file_source(fragment_source);

	glBindVertexArray(0);
	glfwMakeContextCurrent(NULL);
}

float r = 0;

LSGFW_API void Update(lsgfw_universe_t* universe, u32_t world_i)
{
	lsgfw_world_t* world = &universe->world_v[world_i];

	glfwMakeContextCurrent(world->window);
	glBindVertexArray(world->VAO);
	
	// spin camera around origin	
	r += 0.01f;
	camera_pos[0] = cosf(r) * 3.0f;
	camera_pos[2] = sinf(r) * 3.0f;

	int width, height;
	glfwGetWindowSize(world->window, &width, &height);

	// update matrices
	glm_perspective(FOV, width / (float) height, ZNEAR, ZFAR, proj);
	glm_lookat(camera_pos, (vec3) { 0.0, 0.0, 0.0 }, (vec3) { 0.0, 1.0, 0.0 }, view);
	glm_mat4_mul(proj, view, vp);
	
	// draw cube
	glUseProgram(shader_program);
		
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbos[0]);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbos[1]);
		
	int vp_loc = glGetUniformLocation(shader_program, "vp");
	glUniformMatrix4fv(vp_loc, 1, GL_FALSE, vp[0]);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // debug
	glDrawArrays(GL_TRIANGLES, 0, sizeof(indices)/sizeof(u32_t));

	glBindVertexArray(0);
	glfwMakeContextCurrent(NULL);
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

	arrsetlen(source, f_len + 1);
	fread(source, sizeof(char), f_len, f);
	source[f_len] = 0;

	fclose(f);

	return source;
}
