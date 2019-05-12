//
// Created by Sergey Chernov on 2019-04-20.
//

#ifndef DOITDOUBLEDE_APPVULKANUTILS_H
#define DOITDOUBLEDE_APPVULKANUTILS_H

#include <string>
#include <vulkan/vulkan.h>

#define QUEUE_FAMILY_FLAGS_SIZE 2
#define QUEUE_GRAPHICS_FAMILY_INDEX 0
#define QUEUE_COMPUTE_FAMILY_INDEX 1


struct VulkanLogicDeviceState {
    VkPhysicalDevice physicalDevice;
    VkDevice vkDevice;
};

class VulkanLogicDevice {

public:

    VulkanLogicDevice(VkPhysicalDevice physicalDevice, uint32_t graphicsQueuesCount, uint32_t computeQueuesCount);

    VkQueue getGraphicsQueue(uint32_t index);
    VkQueue getComputeQueue(uint32_t index);

    VkPhysicalDevice getPhysicalDevice() const;

    VkDevice getDevice() const;

    size_t stateSnapShot(VulkanLogicDeviceState *outState);

    virtual ~VulkanLogicDevice();

protected:

    uint8_t createVkLogicalDevice();
    void updateQueuesCount(uint32_t flagIndex, uint32_t count);
    uint8_t loadQueueFamilyIndex();

protected:
    bool hasChanges = true;
    VkPhysicalDevice physicalDevice;
    bool queueFamilyIndexInitialized;
    VkDevice device;

    uint32_t *queueFamilyIndex;
    bool *queueFamilyFlagsChanges;
    uint32_t *queueFamilyFlagsCount;


};


#endif //DOITDOUBLEDE_APPVULKANUTILS_H
