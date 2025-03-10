#ifndef LSGFW_SHADERS_H
#define LSGFW_SHADERS_H

#ifndef LSGFW_SHADERS_TAG
    // all tags should be unique, change this to handle collisions
    #define LSGFW_SHADERS_TAG "lsgfw_shaders"
#else
    #error "Tag collision detected"
#endif  // #ifndef LSGFW_SHADERS_TAG

#include <lsgfw.h>

#include <stb/stb_ds.h>

#include <stdio.h>

#ifdef LSGFW_SHADERS_IMPLEMENTATION

GLuint quick_shader_program(u32_t source_c, char** source_v, GLenum* shader_type_v, bool_t debug);

#endif // #ifdef LSGFW_SHADERS_IMPLEMENTATION

typedef struct lsgfw_shaders_s
{
    GLuint (*quick_shader_program)(u32_t, char**, GLenum*, bool_t);
}
lsgfw_shaders_t;

// DO NOT CALL THIS IN ANY INSTALL FUNCTIONS
void lsgfw_shaders_load(lsgfw_kv_t* lsgfw_kv, lsgfw_shaders_t* lsgfw_shaders)
{
    *lsgfw_shaders = *(lsgfw_shaders_t*) shget(lsgfw_kv, LSGFW_SHADERS_TAG);
}

#endif  // #ifndef LSGFW_SHADERS_H
