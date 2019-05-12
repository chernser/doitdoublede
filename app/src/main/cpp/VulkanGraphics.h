//
// Created by Sergey Chernov on 4/16/19.
//

#ifndef DOITDOUBLEDE_VKINITIALIZER_H
#define DOITDOUBLEDE_VKINITIALIZER_H

#include <string>
#include <vector>
#include <android_native_app_glue.h>
#include <android/native_window.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "VulkanLogicDevice.h"


struct VulkanGraphicsState {
    VkInstance vkInstance;
    VulkanLogicDeviceState logicDeviceState;

};


/**
 * Aux class to extract logic of swap chain creation and handling resize events
 */
class SwapChain {

};

/**
 * Bootstrap Class that helps to do essential things
 * Also is kind of proxy for Vulkan API.
 * Intent of this class is to implement bootstrap logic + utility routines
 * any Vulkan application might need.
 * Doesn't implements render.
 *
 */
class VulkanGraphics {

public:

    VulkanGraphics();


    VkInstance getVkInstance() {
        return vkInstance;
    }

    VulkanLogicDevice *getScreen()  {
        return screen;
    }

    VkPhysicalDevice findPhysicalDevice();

    void createLogicalDevices();

    VkSurfaceKHR createSurface(ANativeWindow *nativeWindow);

    size_t stateSnapshot(VulkanGraphicsState *outState);

    virtual ~VulkanGraphics();

private:

private:
    VkInstance vkInstance;
    VulkanLogicDevice *screen;

};

#endif //DOITDOUBLEDE_VKINITIALIZER_H
