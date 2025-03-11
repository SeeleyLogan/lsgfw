#ifndef LSGFW_VK_HANDLER_H
#define LSGFW_VK_HANDLER_H

#ifndef LSGFW_VK_HANDLER_TAG
    // all tags should be unique, change this to handle collisions
    #define LSGFW_VK_HANDLER_TAG "lsgfw_vk_handler"
#else
    #error "Tag collision detected"
#endif

#include <lsgfw.h>

#include <stb/stb_ds.h>

#include <stdio.h>

#ifdef LSGFW_VK_HANDLER_IMPLEMENTATION

void   pick_best_physical_device(VkInstance vk_instance, VkPhysicalDevice* physical_device);
u32_t  device_score             (VkPhysicalDevice device);

#endif // #ifdef LSGFW_VK_HANDLER_IMPLEMENTATION

typedef struct lsgfw_vk_handler_s
{
    VkPhysicalDevice physical_device;
}
lsgfw_vk_handler_t;

// DO NOT CALL THIS IN ANY INSTALL FUNCTIONS
void lsgfw_shaders_load(lsgfw_kv_t* lsgfw_kv, lsgfw_vk_handler_t** lsgfw_vk_handler)
{
    *lsgfw_vk_handler = (lsgfw_vk_handler_t*) shget(lsgfw_kv, LSGFW_VK_HANDLER_TAG);
}

#endif  // #ifndef LSGFW_VK_HANDLER_H
