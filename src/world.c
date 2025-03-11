u32_t lsgfw_new_world()
{
	lsgfw_world_t world = { NULL };

	arrput(universe.world_v, world);

	return arrlen(universe.world_v)-1;
}

void lsgfw_start_world(u32_t world_i)
{
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_INSTALL);
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_START);
}

void lsgfw_loop_world(u32_t world_i)
{
	lsgfw_world_t* world  = &universe.world_v[world_i];
	GLFWwindow* window 	  = world->window;

	while(!glfwWindowShouldClose(window))
	{
		lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_UPDATE);

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
		glfwMakeContextCurrent(NULL);

		LSGFW_SLEEP(1);
	}
}

void lsgfw_end_world(u32_t world_i)
{
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_END);
}

