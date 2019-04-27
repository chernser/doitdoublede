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

    VulkanGraphics(ANativeWindow *nativeWindow);

    VkInstance getVkInstance() {
        return vkInstance;
    }

    VkPhysicalDevice getVkPhysicalDevice() {
        return vkPhysicalDevice;
    }

    VulkanLogicDevice *getScreen()  {
        return screen;
    }

    VkSurfaceKHR *getScreenSurface()  {
        return screenSurface;
    }

    virtual ~VulkanGraphics();

private:
    void doSelectPhyDevice();

    void createLogicalDevices();

    void createSurface();

private:
    // Native platform
    ANativeWindow *nativeWindow;

    VkApplicationInfo appInfo;
    VkInstance vkInstance;
    VkPhysicalDevice vkPhysicalDevice;

    /** Main output logical device */
    VulkanLogicDevice *screen;
    VkSurfaceKHR *screenSurface;
};

#endif //DOITDOUBLEDE_VKINITIALIZER_H
