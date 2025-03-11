#include <cube.h>

u32_t world_one;

void run_cb();

int main()
{
	if (!init_lsgfw() || !init_vk_instance("Cube", VK_MAKE_VERSION(1, 0, 0), 1, (char*[]) { "VK_LAYER_KHRONOS_validation" }))
		return 1;

    lsgfw_universe_t* universe = lsgfw_get_universe();

	world_one = lsgfw_new_world();	
	lsgfw_attach_scripts(world_one, "./scripts/");

	universe->world_v[world_one].window = lsgfw_quick_window("window!");
	run_lsgfw(run_cb);
	lsgfw_end_universe();
}

void run_cb()
{	
	lsgfw_start_world(world_one);
	lsgfw_loop_world (world_one);
	lsgfw_end_world  (world_one);
}
