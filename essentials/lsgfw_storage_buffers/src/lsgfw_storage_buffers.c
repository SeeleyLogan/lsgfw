#define LSGFW_STORAGE_BUFFERS_IMPLEMENTATION
#include <lsgfw_storage_buffers.h>

lsgfw_storage_buffers_t lsgfw_storage_buffers =
{
    quick_storage_buffer
};

LSGFW_API void Install(lsgfw_universe_t* universe, u32_t world_i)
{
    shput(universe->world_v[world_i].global, LSGFW_STORAGE_BUFFERS_TAG, (void*) &lsgfw_storage_buffers);
}

void quick_storage_buffer(u32_t buff_size, void* data, lsgfw_storage_buffer_t* lsgfw_storage_buffer)
{
    glGenBuffers(1, &lsgfw_storage_buffer->ssbo);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, lsgfw_storage_buffer->ssbo);
	glBufferStorage(GL_SHADER_STORAGE_BUFFER, buff_size, data,
        GL_DYNAMIC_STORAGE_BIT  |
        GL_MAP_WRITE_BIT        | 
        GL_MAP_READ_BIT         | 
        GL_MAP_PERSISTENT_BIT   | 
        GL_MAP_COHERENT_BIT
    );

    lsgfw_storage_buffer->mapped_buffer = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, buff_size,
        GL_MAP_PERSISTENT_BIT       |
        GL_MAP_WRITE_BIT            |
        GL_MAP_READ_BIT             |
        GL_MAP_FLUSH_EXPLICIT_BIT   |
        GL_MAP_COHERENT_BIT
    );

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
