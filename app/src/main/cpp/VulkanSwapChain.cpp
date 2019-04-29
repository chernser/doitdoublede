//
// Created by Sergey Chernov on 2019-04-27.
//

#include <vector>
#include "VulkanSwapChain.h"

VulkanSwapChain::VulkanSwapChain(std::shared_ptr<VulkanLogicDevice> device, VkSurfaceKHR surface) :
        device(device), presentMode(VK_PRESENT_MODE_FIFO_KHR), surface(surface) {
    init();
}

void VulkanSwapChain::init() {

    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevice(), surface,
            &formatCount, nullptr);

    std::vector<VkSurfaceFormatKHR> availableFormats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevice(), surface, &formatCount, availableFormats.data());

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.minImageCount = 1;
    createInfo.imageFormat = nullptr;
    createInfo.imageColorSpace = nullptr;
    createInfo.presentMode = presentMode;


    if (vkCreateSwapchainKHR(device->getDevice(), &createInfo, nullptr, &vkSwapchainKHR) != VK_SUCCESS) {
        return;
    }
}

