//
// Created by Sergey Chernov on 4/16/19.
//
#include <android_native_app_glue.h>
#include <vulkan/vulkan.h>
#include <vector>

#include "appUtils.h"
#include "appLifeCycle.h"

AppInitializer::AppInitializer(struct android_app *app) :
        app(app), vkPhysicalDevice(VK_NULL_HANDLE), vkInstance(VK_NULL_HANDLE) {
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = NULL;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
}

void AppInitializer::setApplicationName(const char *name) {
    this->appInfo.pApplicationName = name;
}

uint8_t AppInitializer::doInit() {

    VkInstanceCreateInfo createInfo = {};
    memset((char *) &createInfo, 0, sizeof(VkInstanceCreateInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;


    if (vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS) {
        LOGW("Failed to create vulkan instance");
        return 1;
    } else {
        LOGI("Vulkan instance created");
    };

    doSelectPhyDevice();
    createLogicalDevices();

    return 0;
}


void AppInitializer::doSelectPhyDevice() {
    // Get the list of physical devices
    uint32_t devCount = 1;
    if (VK_SUCCESS != vkEnumeratePhysicalDevices(vkInstance, &devCount, NULL) || devCount == 0) {
        LOGW("Failed searching for Vulkan physical devices");
        return;
    }

    std::vector<VkPhysicalDevice> phyDevices;
    phyDevices.resize(devCount);
    if (VK_SUCCESS != vkEnumeratePhysicalDevices(vkInstance, &devCount, phyDevices.data()) ||
        devCount == 0) {
        LOGW("Failed enumerating Vulkan physical devices");
        return;
    }


    // Go through the list of physical devices and select only those that are capable of running the API version we want.
    for (auto dev : phyDevices) {
        VkPhysicalDeviceProperties props = {};
        vkGetPhysicalDeviceProperties(dev, &props);
        LOGI("DEV: %s %d", props.deviceName, props.apiVersion);
        // TODO: do proper device filtering here
        if (vkPhysicalDevice == VK_NULL_HANDLE) {
            vkPhysicalDevice = dev;
        }
    }
}

void AppInitializer::createLogicalDevices() {

    screen = new VulkanLogicDevice(vkPhysicalDevice);
    screen->setNumberOfComputeQueues(1);
    screen->setNumberOfGraphicsQueues(1);

    uint8_t result = screen->createVkLogicalDevice();
    if (result != 0) {
        LOGW("Failed to apply logic device changes: %d", result);
        return;
    }
}

AppTerminator::AppTerminator(android_app *androidApp, application *thisApp) :
        androidApp(androidApp), thisApp(thisApp) {

}

void AppTerminator::doTerminate() {
    if (thisApp->screen != nullptr) {
        delete thisApp->screen;
    } else {
        LOGW("screen is already null");
    }

    if (thisApp->vkInstance != nullptr) {
        vkDestroyInstance(thisApp->vkInstance, nullptr);
        thisApp->vkInstance = nullptr;
    } else {
        LOGW("vkInstance is already null");
    }
}
