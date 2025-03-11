#include <stdio.h>

bool_t init_vk_instance(char* app_name, u32_t version, u32_t validation_layer_c, char** validation_layer_v)
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

	if (validation_layer_c && check_validation_layer_support(validation_layer_c, validation_layer_v))
	{
		create_info.enabledLayerCount   = validation_layer_c;
    	create_info.ppEnabledLayerNames = (void*) validation_layer_v;
	}
	else if (!validation_layer_c)
		create_info.enabledLayerCount = 0;
	else
		return LSGFW_FAIL;
	
	if (vkCreateInstance(&create_info, NULL, &universe.vk_instance) != VK_SUCCESS)
		return LSGFW_FAIL;

	arrfree(required_extensions);

	return LSGFW_SUCCESS;
}

bool_t check_validation_layer_support(u32_t validation_layer_c, char** validation_layer_v)
{
    u32_t layer_c;
    vkEnumerateInstanceLayerProperties(&layer_c, NULL);

    VkLayerProperties* available_layer_v = NULL;
	arrsetlen(available_layer_v, layer_c);

    vkEnumerateInstanceLayerProperties(&layer_c, available_layer_v);

    for (u32_t i = 0; i < validation_layer_c; i++)
	{
		char* validation_layer_name = validation_layer_v[i];
		bool_t layer_found = LSGFW_FALSE;
	
		for (u32_t j = 0; j < layer_c; j++)
		{
			VkLayerProperties layer_properities = available_layer_v[j];
			if (strcmp(validation_layer_name, layer_properities.layerName) == 0)
			{
				layer_found = LSGFW_TRUE;
				break;
			}
		}
	
		if (!layer_found)
			return LSGFW_FAIL;
	}

	arrfree(available_layer_v);
	
	return LSGFW_SUCCESS;
}
