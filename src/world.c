LSGFW_API u32_t lsgfw_new_world()
{
	lsgfw_world_t world = { NULL };

	arrput(universe.worlds, world);

	return arrlen(universe.worlds)-1;
}

LSGFW_API void lsgfw_start_world(u32_t world_i, void (*script_cb)())
{
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_START, script_cb);
}

LSGFW_API void lsgfw_loop_world(u32_t world_i, void (*script_cb)())
{
	GLFWwindow* window = universe.worlds[world_i].window;

	#pragma omp parallel sections shared(window)
	{
		#pragma omp section
		{
			while(!glfwWindowShouldClose(window))
			{
				#pragma omp critical
        			{
					glfwMakeContextCurrent(window);

					glfwPollEvents();

					glfwMakeContextCurrent(NULL);
				}
			}
		}

		#pragma omp section
		{
			while(!glfwWindowShouldClose(window))
			{
				#pragma omp critical
        			{	
					glfwMakeContextCurrent(window);
					
					glClear(GL_COLOR_BUFFER_BIT);
					
					glfwMakeContextCurrent(NULL);
				}

				lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_UPDATE, script_cb);

				glfwSwapBuffers(window);
			}
		}
	}
}

LSGFW_API void lsgfw_end_world(u32_t world_i, void (*script_cb)())
{
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_END, script_cb);

	if (universe.worlds[world_i].window)
	{
		glfwDestroyWindow(universe.worlds[world_i].window);
		universe.worlds[world_i].window = NULL;
	}
}

