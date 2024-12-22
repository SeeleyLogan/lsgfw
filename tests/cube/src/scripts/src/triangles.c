#include <cube.h>

lsgfw_world_t* world;

LSGFW_EXPORT void* Start(lsgfw_universe_t* universe, u32_t world_i)
{
	world = &universe->world_v[world_i];
	
	return NULL;
}

LSGFW_EXPORT void* Update(lsgfw_universe_t* universe, u32_t world_i)
{
	return NULL;
}

LSGFW_EXPORT void* End(lsgfw_universe_t* universe, u32_t world_i)
{
	return NULL;
}
