#include <cube.h>

u32_t world_i;

void run();

int main()
{
	if (!init_lsgfw())
		return 1;

	world_i = lsgfw_new_world();

	lsgfw_attach_scripts(world_i, "./scripts/");

	lsgfw_get_universe()->world_v[world_i].window = lsgfw_quick_window("window1!");
	run_lsgfw(run);
	glfwDestroyWindow(lsgfw_get_universe()->world_v[world_i].window);

	lsgfw_get_universe()->world_v[world_i].window = lsgfw_quick_window("window2!");
	run_lsgfw(run);
	glfwDestroyWindow(lsgfw_get_universe()->world_v[world_i].window);

	lsgfw_end_universe();
}

void run()
{
	lsgfw_start_world(world_i);
	lsgfw_loop_world (world_i);
	lsgfw_end_world  (world_i);
}
