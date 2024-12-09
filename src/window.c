LSGFW_API GLFWwindow* lsgfw_quick_window(const char* title, bool share)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window;

	if (share && arrlen(universe.worlds))
		window = glfwCreateWindow(800, 600, title, NULL, universe.worlds[0].window);
	else	
		window = glfwCreateWindow(800, 600, title, NULL, NULL);

	if (!window)
		return LSGFW_FAIL;

	glfwMakeContextCurrent(window);

	if (arrlen(universe.worlds) == 0 && !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		return LSGFW_FAIL;
	
	glViewport(0, 0, 800, 600);

	return window;
}

