#ifndef LSGFW_BUFFERS_H
#define LSGFW_BUFFERS_H

#ifndef LSGFW_BUFFERS_TAG
    // all tags should be unique, change this to handle collisions
    #define LSGFW_BUFFERS_TAG "lsgfw_buffers"
#else
    #error "Tag collision detected"
#endif  // #ifndef LSGFW_BUFFERS_TAG

#include <lsgfw.h>
#include <stb/stb_ds.h>

typedef struct lsgfw_mapped_buffer_s
{
    GLuint named_buffer;
    void*  mapped_buffer;
}
lsgfw_mapped_buffer_t;

#ifdef LSGFW_BUFFERS_IMPLEMENTATION

void quick_mapped_buffer(u32_t buff_size, void* data, lsgfw_mapped_buffer_t* lsgfw_mapped_buffer);

#endif // #ifdef LSGFW_BUFFERS_IMPLEMENTATION

typedef struct lsgfw_buffers_s
{
    void (*quick_mapped_buffer)(u32_t, void*, lsgfw_mapped_buffer_t*);
}
lsgfw_buffers_t;

// DO NOT CALL THIS IN ANY INSTALL FUNCTIONS
void lsgfw_buffers_load(lsgfw_kv_t* lsgfw_kv, lsgfw_buffers_t* lsgfw_buffers)
{
    *lsgfw_buffers = *(lsgfw_buffers_t*) shget(lsgfw_kv, LSGFW_BUFFERS_TAG);
}

#endif  // #ifndef LSGFW_BUFFERS_H
