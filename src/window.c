GLFWwindow* lsgfw_quick_window(const char* title)
{	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, NULL);
	if (!window)
		return LSGFW_FAIL;
	
	return window;
}
