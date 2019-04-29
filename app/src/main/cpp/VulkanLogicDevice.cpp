//
// Created by Sergey Chernov on 2019-04-20.
//

#include <string.h>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "VulkanLogicDevice.h"
#include "appUtils.h"

uint8_t VulkanLogicDevice::createVkLogicalDevice() {

    uint8_t result = loadQueueFamilyIndex();
    if (result != 0) {
        return result;
    }

    float queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queuesToCreate(0);
    for (uint32_t flagIndex = 0; flagIndex < QUEUE_FAMILY_FLAGS_SIZE; flagIndex++) {
        if (!queueFamilyFlagsChanges[flagIndex]) {
            continue;
        }
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex[flagIndex];
        queueCreateInfo.queueCount = queueFamilyFlagsCount[flagIndex];
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queuesToCreate.push_back(queueCreateInfo);
    }


    VkDeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = queuesToCreate.data();
    std::vector<const char *> extensionNames = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t >(extensionNames.size());
    deviceCreateInfo.ppEnabledExtensionNames = extensionNames.data();

    if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
        LOGW("Failed to create logic device");
        return 200;
    }

    return 0;
}

VkQueue VulkanLogicDevice::getGraphicsQueue(uint32_t index) {
    return nullptr;
}

VkQueue VulkanLogicDevice::getComputeQueue(uint32_t index) {
    return nullptr;
}

void VulkanLogicDevice::updateQueuesCount(uint32_t flagIndex, uint32_t count) {
    uint32_t *oldValue =
            &queueFamilyFlagsCount[flagIndex];
    if (*oldValue != count) {
        *oldValue = count;
        queueFamilyFlagsChanges[flagIndex] = true;
        hasChanges = true;
    }
}

uint8_t VulkanLogicDevice::loadQueueFamilyIndex() {

    if (queueFamilyIndexInitialized) {
        return 0;
    }

    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
    if (count > 0) {
        std::vector<VkQueueFamilyProperties> queueFamilies(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, queueFamilies.data());

        for (uint32_t familyIndex = 0; familyIndex < queueFamilies.size(); familyIndex++) {
            if (queueFamilies[familyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                queueFamilyIndex[QUEUE_GRAPHICS_FAMILY_INDEX] = familyIndex;
            }
            if (queueFamilies[familyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                queueFamilyIndex[QUEUE_COMPUTE_FAMILY_INDEX] = familyIndex;
            }
        }

    } else {
        return 100;
    }

    return 0;
}


VulkanLogicDevice::VulkanLogicDevice(VkPhysicalDevice physicalDevice, uint32_t graphicsQueuesCount,
                                     uint32_t computeQueuesCount) :
        physicalDevice(physicalDevice), queueFamilyFlagsCount(new uint32_t[QUEUE_FAMILY_FLAGS_SIZE]),
        queueFamilyFlagsChanges(new bool[QUEUE_FAMILY_FLAGS_SIZE]),
        queueFamilyIndex(new uint32_t[QUEUE_FAMILY_FLAGS_SIZE]), queueFamilyIndexInitialized(false) {


    updateQueuesCount(QUEUE_GRAPHICS_FAMILY_INDEX, graphicsQueuesCount);
    updateQueuesCount(QUEUE_COMPUTE_FAMILY_INDEX, computeQueuesCount);
    memset(queueFamilyIndex, 0, sizeof(uint32_t) * QUEUE_FAMILY_FLAGS_SIZE);

    createVkLogicalDevice();
}


VulkanLogicDevice::~VulkanLogicDevice() {
    vkDestroyDevice(this->device, nullptr);
}

VkPhysicalDevice  VulkanLogicDevice::getPhysicalDevice() const {
    return physicalDevice;
}

VkDevice VulkanLogicDevice::getDevice() const {
    return device;
}
