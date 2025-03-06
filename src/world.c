LSGFW_API u32_t lsgfw_new_world()
{
	lsgfw_world_t world = { NULL };

	arrput(universe.world_v, world);

	return arrlen(universe.world_v)-1;
}

LSGFW_API void lsgfw_start_world(u32_t world_i)
{
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_INSTALL);
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_START);
}

LSGFW_API void lsgfw_loop_world(u32_t world_i)
{
	GLFWwindow* window = universe.world_v[world_i].window;

	while(!glfwWindowShouldClose(window))
	{
		glfwMakeContextCurrent(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwMakeContextCurrent(NULL);	

		lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_UPDATE);
		
		glfwSwapBuffers(window);
	}
}

LSGFW_API void lsgfw_end_world(u32_t world_i)
{
	GLFWwindow* window = universe.world_v[world_i].window;
	
	lsgfw_invoke_scripts(world_i, LSGFW_SCRIPT_END);

	if (universe.world_v[world_i].window)
	{
		glfwDestroyWindow(universe.world_v[world_i].window);
		universe.world_v[world_i].window = NULL;
	}
}

