#define LSGFW_BUFFERS_IMPLEMENTATION
#include <lsgfw_buffers.h>

lsgfw_buffers_t lsgfw_buffers =
{
    quick_mapped_buffer
};

LSGFW_API void Install(lsgfw_universe_t* universe, u32_t world_i)
{
    shput(universe->world_v[world_i].global, LSGFW_BUFFERS_TAG, (void*) &lsgfw_buffers);
}

void quick_mapped_buffer(u32_t buff_size, void* data, lsgfw_mapped_buffer_t* lsgfw_mapped_buffer)
{
    glCreateBuffers(1, &lsgfw_mapped_buffer->named_buffer);

	glNamedBufferStorage(lsgfw_mapped_buffer->named_buffer, buff_size, data,
        GL_MAP_WRITE_BIT        | 
        GL_MAP_READ_BIT         | 
        GL_MAP_PERSISTENT_BIT
    );

    lsgfw_mapped_buffer->mapped_buffer = glMapNamedBufferRange(lsgfw_mapped_buffer->named_buffer, 0, buff_size,
        GL_MAP_WRITE_BIT            | 
        GL_MAP_READ_BIT             | 
        GL_MAP_PERSISTENT_BIT       |
        GL_MAP_FLUSH_EXPLICIT_BIT
    );
}
