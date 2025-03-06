#define LSGFW_SHADERS_IMPLEMENTATION
#include <lsgfw_shaders.h>

lsgfw_shaders_t lsgfw_shaders =
{
    quick_shader_program
};

LSGFW_API void Install(lsgfw_universe_t* universe, u32_t world_i)
{
    shput(universe->world_v[world_i].global, LSGFW_SHADERS_TAG, (void*) &lsgfw_shaders);
}

GLuint quick_shader_program(u32_t source_c, char** source_v, GLenum* shader_type_v, bool_t debug)
{
    GLuint shader_program = glCreateProgram();

    GLint info_log_len;

    for (u32_t i = 0; i < source_c; i++)
    {
        GLuint shader = glCreateShader(shader_type_v[i]);
        glShaderSource(shader, 1, (void*) &source_v[i], NULL);

        glCompileShader(shader);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_len);
        if (debug && info_log_len)
        {
            char* info_log = NULL;
            arrsetlen(info_log, info_log_len);
            glGetShaderInfoLog(shader, info_log_len, NULL, info_log);
            printf("shader source at index %i: %s", i, info_log);
        }

        glAttachShader(shader_program, shader);
        glDeleteShader(shader);
    }

    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_log_len);
    if (debug && info_log_len)
    {
        char* info_log = NULL;
        arrsetlen(info_log, info_log_len);
        glGetProgramInfoLog(shader_program, info_log_len, NULL, info_log);
        printf("%s", info_log);
    }

    return shader_program;
}
