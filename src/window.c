LSGFW_API GLFWwindow* lsgfw_quick_window(const char* title)
{	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef __APPLE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, universe.window);
	if (!window)
		return LSGFW_FAIL;

	glfwMakeContextCurrent(window);
	
	glViewport(0, 0, 800, 600);
	
	glEnable(GL_DEPTH_TEST);
	
	glfwMakeContextCurrent(NULL);
	
	return window;
}

