#include <cube.h>

u32_t world_i;

void run_cb();

int main()
{
	if (!init_lsgfw())
		return 1;

	world_i = lsgfw_new_world();	
	lsgfw_get_universe()->world_v[world_i].window = lsgfw_quick_window("window!");
	lsgfw_attach_scripts(world_i, "./scripts/");
	
	run_lsgfw(run_cb);
}

void run_cb()
{
	lsgfw_start_world(world_i);
	lsgfw_loop_world (world_i);
	lsgfw_end_world  (world_i);

	lsgfw_end_universe();
}
