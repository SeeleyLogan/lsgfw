#ifndef LSGFW_STORAGE_BUFFERS_H
#define LSGFW_STORAGE_BUFFERS_H

#ifndef LSGFW_STORAGE_BUFFERS_TAG
    // all tags should be unique, change this to handle collisions
    #define LSGFW_STORAGE_BUFFERS_TAG "lsgfw_storage_buffers"
#else
    #error "Tag collision detected"
#endif  // #ifndef LSGFW_STORAGE_BUFFERS_TAG

#include <lsgfw.h>
#include <stdio.h>
#include <stb/stb_ds.h>

typedef struct lsgfw_storage_buffer_s
{
    GLuint ssbo;
    void*  mapped_buffer;
}
lsgfw_storage_buffer_t;

#ifdef LSGFW_STORAGE_BUFFERS_IMPLEMENTATION

void quick_storage_buffer(u32_t buff_size, void* data, lsgfw_storage_buffer_t* lsgfw_storage_buffer);

#endif // #ifdef LSGFW_STORAGE_BUFFERS_IMPLEMENTATION

typedef struct lsgfw_storage_buffers_s
{
    void (*quick_storage_buffer)(u32_t, void*, lsgfw_storage_buffer_t*);
}
lsgfw_storage_buffers_t;

// DO NOT CALL THIS IN ANY INSTALL FUNCTIONS
void lsgfw_storage_buffers_load(lsgfw_kv_t* lsgfw_kv, lsgfw_storage_buffers_t* lsgfw_storage_buffers)
{
    *lsgfw_storage_buffers = *(lsgfw_storage_buffers_t*) shget(lsgfw_kv, LSGFW_STORAGE_BUFFERS_TAG);
}

#endif  // #ifndef LSGFW_STORAGE_BUFFERS_H
