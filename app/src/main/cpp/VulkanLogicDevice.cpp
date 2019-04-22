//
// Created by Sergey Chernov on 2019-04-20.
//

#include <string.h>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "VulkanLogicDevice.h"
#include "appUtils.h"

const uint32_t *QUEUE_FAMILY_FLAGS = new uint32_t[QUEUE_FAMILY_FLAGS_SIZE]{VK_QUEUE_GRAPHICS_BIT, VK_QUEUE_COMPUTE_BIT};

void VulkanLogicDevice::setNumberOfGraphicsQueues(uint32_t count) {
    updateQueuesCount(QUEUE_GRAPHICS_FAMILY_INDEX, count);
}

void VulkanLogicDevice::setNumberOfComputeQueues(uint32_t count) {
    updateQueuesCount(QUEUE_COMPUTE_FAMILY_INDEX, count);
}

uint8_t VulkanLogicDevice::createVkLogicalDevice() {

    uint8_t result = loadQueueFamilyIndex();
    if (result != 0) {
        return result;
    }

    float queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queuesToCreate(0);
    for (uint32_t flagIndex = 0; flagIndex < QUEUE_FAMILY_FLAGS_SIZE; flagIndex++) {
        if (!queueFaimilyFlagsChanges[flagIndex]) {
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

VulkanLogicDevice::VulkanLogicDevice(VkPhysicalDevice physicalDevice) :
        physicalDevice(physicalDevice), queueFamilyFlagsCount(new uint32_t[QUEUE_FAMILY_FLAGS_SIZE]),
        queueFaimilyFlagsChanges(new bool[QUEUE_FAMILY_FLAGS_SIZE]),
        queueFamilyIndex(new uint32_t[QUEUE_FAMILY_FLAGS_SIZE]), queueFamilyIndexInitialized(false) {

    memset(queueFamilyIndex, 0, sizeof(uint32_t) * QUEUE_FAMILY_FLAGS_SIZE);
}

void VulkanLogicDevice::updateQueuesCount(uint32_t flagIndex, uint32_t count) {
    uint32_t *oldValue =
            &queueFamilyFlagsCount[flagIndex];
    if (*oldValue != count) {
        *oldValue = count;
        queueFaimilyFlagsChanges[flagIndex] = true;
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

VulkanLogicDevice::~VulkanLogicDevice() {
    vkDestroyDevice(this->device, nullptr);
}
