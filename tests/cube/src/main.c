#include <cube.h>
#include <stdio.h>

u32_t world_i;

void init_cb(lsgfw_universe_t* universe);
void run_cb(lsgfw_universe_t* universe);

int main()
{
	return !init_lsgfw(run_cb, init_cb);  // logical not because fail = 0 and succes = 1
}

void init_cb(lsgfw_universe_t* universe)
{
	world_i = lsgfw_new_world();	
	universe->worlds[world_i].window = lsgfw_quick_window("window!");
}

void run_cb(lsgfw_universe_t* universe)
{
	lsgfw_attach_scripts(world_i, "./scripts/");

	lsgfw_start_world(world_i, NULL);
	lsgfw_loop_world (world_i, NULL);
	lsgfw_end_world  (world_i, NULL);
	
	lsgfw_end_universe();
}

