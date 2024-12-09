LSGFW_API lsgfw_world_t* lsgfw_new_world(GLFWwindow* window)
{
	if (!window)
		return LSGFW_FAIL;

	lsgfw_world_t world =
	{
		window
	};

	arrput(universe.worlds, world);

	return &(universe.worlds[arrlen(universe.worlds)-1]);
}

LSGFW_API void lsgfw_start_world(lsgfw_world_t* world)
{
	glfwShowWindow(world->window);

	// test
	#pragma omp critical
	{
		glfwMakeContextCurrent(world->window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glfwMakeContextCurrent(NULL);
	}
}

LSGFW_API void lsgfw_loop_world(lsgfw_world_t* world)
{
	GLFWwindow* window = world->window;

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

				// . . .

				glfwSwapBuffers(window);
			}
		}
	}
}

LSGFW_API void lsgfw_end_world(lsgfw_world_t* world)
{
	glfwDestroyWindow(world->window);
}

