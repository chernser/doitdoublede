//
// Created by Sergey Chernov on 4/16/19.
//
#include <android_native_app_glue.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_android.h>
#include <vector>

#include "appUtils.h"
#include "VulkanGraphics.h"

VulkanGraphics::VulkanGraphics(ANativeWindow *nativeWindow) : nativeWindow(nativeWindow) {

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = NULL;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // For scaling up
    ANativeWindow_setBuffersGeometry(nativeWindow, 1024, 768, 0);


    VkInstanceCreateInfo createInfo = {};
    memset((char *) &createInfo, 0, sizeof(VkInstanceCreateInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;


    if (vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS) {
        LOGW("Failed to create vulkan instance");
        throw "Failed to create vulkan instance";
    } else {
        LOGI("Vulkan instance created");
    };

    doSelectPhyDevice();
    createLogicalDevices();
    createSurface();

}

VulkanGraphics::~VulkanGraphics() {
    vkDestroySurfaceKHR(vkInstance, *screenSurface, nullptr);
    delete screen;
    vkDestroyInstance(vkInstance, nullptr);
}

void VulkanGraphics::createLogicalDevices() {
    screen = new VulkanLogicDevice(vkPhysicalDevice, 1, 1);
}

void VulkanGraphics::doSelectPhyDevice() {
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
            uint32_t extCount;
            if (vkEnumerateDeviceExtensionProperties(dev, nullptr, &extCount, nullptr) != VK_SUCCESS) {
                LOGW("Failed to get device extensions");
                continue;
            }

            std::vector<VkExtensionProperties> extensions(extCount);
            vkEnumerateDeviceExtensionProperties(dev, nullptr, &extCount, extensions.data());


            bool swapChainExtensionFound = false;
            for (auto extension : extensions) {
                if (strcasecmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
                    swapChainExtensionFound = true;
                    break;
                }
            }

            if (swapChainExtensionFound) {
                vkPhysicalDevice = dev;
                break;
            } else {
                LOGW("No swapchain extension found");
            }
        }
    }
}

void VulkanGraphics::createSurface() {
    VkAndroidSurfaceCreateInfoKHR createInfoKHR;
    createInfoKHR.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfoKHR.window = nativeWindow;
    createInfoKHR.pNext = nullptr;

    if (vkCreateAndroidSurfaceKHR(vkInstance, &createInfoKHR, nullptr, screenSurface) != VK_SUCCESS) {
        LOGW("Failed to create surface");
        return;
    }
}
