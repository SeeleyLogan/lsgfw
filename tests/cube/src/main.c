#include <cube.h>

int main()
{
	lsgfw_universe_t* universe = init_lsgfw();

	u32_t world_i = lsgfw_new_world();
	universe->worlds[world_i].window = lsgfw_quick_window("window!");

	lsgfw_attach_scripts(world_i, "./scripts/");

	lsgfw_start_world(world_i, NULL);
	lsgfw_loop_world (world_i, NULL);
	lsgfw_end_world  (world_i, NULL);
	
	lsgfw_end_universe();
}

