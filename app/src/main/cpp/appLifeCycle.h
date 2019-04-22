//
// Created by Sergey Chernov on 4/16/19.
//

#ifndef DOITDOUBLEDE_VKINITIALIZER_H
#define DOITDOUBLEDE_VKINITIALIZER_H

#include <string>
#include <vector>
#include <android_native_app_glue.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "VulkanLogicDevice.h"

struct application {
    VkInstance vkInstance;
    VkPhysicalDevice vkPhysicalDevice;

    /** Main output logical device */
    VulkanLogicDevice *screen;

    VkSurfaceKHR *screenSurface;
};

/**
 * Class with application initialization routines.
 * Should exist while init
 */
class AppInitializer {
public:
    AppInitializer(android_app *app);

    void setApplicationName(const char *name);

    uint8_t doInit();

    VkInstance getVkInstance() { return vkInstance; }

    VkPhysicalDevice getVkPhyDevice() { return vkPhysicalDevice; }

    VulkanLogicDevice *getScreen() { return screen; }

    VkSurfaceKHR *getScreenSurface() { return screenSurface; }

protected:
    void doSelectPhyDevice();

    void createLogicalDevices();

    void createSurface();

protected:
    struct android_app *app;

    VkApplicationInfo appInfo;
    VkInstance vkInstance;
    VkPhysicalDevice vkPhysicalDevice;
    VulkanLogicDevice *screen;
    VkSurfaceKHR  *screenSurface;
};

class AppTerminator {
public:
    AppTerminator(android_app *androidApp, application *thisApp);

    void doTerminate();

protected:
    struct android_app *androidApp;
    struct application *thisApp;

};

#endif //DOITDOUBLEDE_VKINITIALIZER_H
