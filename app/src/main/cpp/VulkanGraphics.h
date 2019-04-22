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
 * Represents Vulkan Graphics API
 * Actually is facade for any graphics things
 *
 *
 */
class VulkanGraphics {

public:

    VulkanGraphics(ANativeWindow *nativeWindow);

    void setVkInstance(VkInstance vkInstance) {
        this->vkInstance = vkInstance;
    }

    void setVkPhysicalDevice(VkPhysicalDevice vkPhysicalDevice) {
        this->vkPhysicalDevice = vkPhysicalDevice;
    }

    void setScreen(VulkanLogicDevice *screen) {
        this->screen = screen;
    }

    void setScreenSurface(VkSurfaceKHR *screenSurface) {
        this->screenSurface = screenSurface;
    }

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
