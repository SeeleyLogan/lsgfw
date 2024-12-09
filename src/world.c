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

