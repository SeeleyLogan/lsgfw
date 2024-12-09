#include <LSGFW/lsgfw.h>

int main()
{
	if (!init_lsgfw())
		exit(1);

	if (!lsgfw_new_world(lsgfw_quick_window("window!", false)))
		exit(1);
	
	GLFWwindow* window = lsgfw_get_universe()->worlds[0].window;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glfwMakeContextCurrent(NULL);

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

