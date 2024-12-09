#include <LSGFW/lsgfw.h>

int main()
{
	if (!init_lsgfw())
		exit(1);

	if (!lsgfw_new_world(lsgfw_quick_window("window1!")))
		exit(1);
	
	if (!lsgfw_new_world(lsgfw_quick_window("window2!")))
		exit(1);

	lsgfw_universe_t* universe = lsgfw_get_universe();

	#pragma omp parallel sections shared(universe)
	{

		#pragma omp section
		{
			lsgfw_world_t world = universe->worlds[0];

			lsgfw_start_world(&world);
			lsgfw_loop_world(&world);
			lsgfw_end_world(&world);
		}

		#pragma omp section
		{
			lsgfw_world_t world = universe->worlds[1];

			lsgfw_start_world(&world);
			lsgfw_loop_world(&world);
			lsgfw_end_world(&world);
		}
	}
}

