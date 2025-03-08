LSGFW_API GLFWwindow* lsgfw_quick_window(const char* title)
{	
	GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, universe.window);
	if (!window)
		return LSGFW_FAIL;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, 800, 600);
	
	glfwMakeContextCurrent(NULL);
	
	return window;
}

