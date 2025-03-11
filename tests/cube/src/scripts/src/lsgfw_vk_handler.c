#define LSGFW_VK_HANDLER_IMPLEMENTATION
#include <lsgfw_vk_handler.h>
#include <stdio.h>

lsgfw_vk_handler_t lsgfw_vk_handler =
{
    .physical_device = VK_NULL_HANDLE
};

LSGFW_API void Install(lsgfw_universe_t* universe, u32_t world_i)
{
    pick_best_physical_device(universe->vk_instance, &lsgfw_vk_handler.physical_device);

    shput(universe->world_v[world_i].global, LSGFW_VK_HANDLER_TAG, (void*) &lsgfw_vk_handler);
}

void pick_best_physical_device(VkInstance vk_instance, VkPhysicalDevice* physical_device)
{ 
    u32_t physical_device_count = 0;
    vkEnumeratePhysicalDevices(vk_instance, &physical_device_count, NULL);

    if (!physical_device_count)
        return;

    VkPhysicalDevice* physical_device_v = NULL;
    arrsetlen(physical_device_v, physical_device_count);
    vkEnumeratePhysicalDevices(vk_instance, &physical_device_count, physical_device_v);

    VkPhysicalDevice best_physical_device = VK_NULL_HANDLE;
    u32_t best_score = 0;
    for (u32_t i = 0; i < physical_device_count; i++)
    {
        u32_t score = device_score(physical_device_v[i]);
        if (score > best_score)
        {
            best_physical_device = physical_device_v[i];
            best_score  = score;
        }
    }

    if (best_physical_device == VK_NULL_HANDLE)
        return;

    *physical_device = best_physical_device;
}

u32_t device_score(VkPhysicalDevice physical_device) {
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;
    vkGetPhysicalDeviceProperties(physical_device, &device_properties);
    vkGetPhysicalDeviceFeatures(physical_device, &device_features);

    if (device_properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || !device_features.geometryShader)
        return 0;

    return device_properties.limits.maxImageDimension2D;
}