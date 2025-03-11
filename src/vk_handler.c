bool_t check_validation_layer_support(u32_t validation_layer_count, char** validation_layers) {
    u32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, NULL);

    VkLayerProperties* available_layers = NULL;
	arrsetlen(available_layers, layer_count);

    vkEnumerateInstanceLayerProperties(&layer_count, available_layers);

    for (u32_t i = 0; i < validation_layer_count; i++)
	{
		char* validation_layer_name = validation_layers[i];
		bool_t layer_found = LSGFW_FALSE;
	
		for (u32_t j = 0; j < layer_count; j++)
		{
			VkLayerProperties layer_properities = available_layers[j];
			if (strcmp(validation_layer_name, layer_properities.layerName) == 0)
			{
				layer_found = LSGFW_TRUE;
				break;
			}
		}
	
		if (!layer_found)
			return LSGFW_FAIL;
	}
	
	return LSGFW_SUCCESS;
}

bool_t init_vk_instance(char* app_name, u32_t version, u32_t validation_layer_count, char** validation_layers)
{
	VkApplicationInfo app_info = { 0 };

    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    app_info.pApplicationName = app_name;
    app_info.applicationVersion = version;

    app_info.pEngineName = "lsgfw";
    app_info.engineVersion = VK_MAKE_VERSION(1, 1, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info = { 0 };
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;

	u32_t glfw_extension_count = 0;
	const char** glfw_extensions;
	const char** required_extensions = NULL;

	glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	for(u32_t i = 0; i < glfw_extension_count; i++)
		arrput(required_extensions, glfw_extensions[i]);
	
#ifdef __APPLE
	arrput(requiredExtensions, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
	create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

	create_info.enabledExtensionCount   = arrlenu(required_extensions);
	create_info.ppEnabledExtensionNames = required_extensions;

	if (validation_layer_count && check_validation_layer_support(validation_layer_count, validation_layers))
	{
		create_info.enabledLayerCount   = validation_layer_count;
    	create_info.ppEnabledLayerNames = (void*) validation_layers;
	}
	else if (!validation_layer_count)
		create_info.enabledLayerCount = 0;
	else
		return LSGFW_FAIL;

	if (vkCreateInstance(&create_info, NULL, &universe.vk_instance) != VK_SUCCESS)
		return LSGFW_FAIL;

	return LSGFW_SUCCESS;
}
