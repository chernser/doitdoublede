//
// Created by Sergey Chernov on 2019-04-27.
//

#ifndef DOITDOUBLEDE_VULKANSWAPCHAIN_H
#define DOITDOUBLEDE_VULKANSWAPCHAIN_H


#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanLogicDevice.h"

/**
 * Implement 'presentation' of the rendered image.
 * Swap chain is more system and hardware specific and responsible for rendering to
 * window of screen .
 *
 */
class VulkanSwapChain {


public:
    VulkanSwapChain(std::shared_ptr<VulkanLogicDevice> device, VkSurfaceKHR surface);

private:

    void init();

protected:
    // Mandatory parameters;
    std::shared_ptr<VulkanLogicDevice> device;
    VkSurfaceKHR surface;

    // swap chain parameters
    VkPresentModeKHR presentMode;


    // Result entities
    VkSwapchainKHR vkSwapchainKHR;

};


#endif //DOITDOUBLEDE_VULKANSWAPCHAIN_H
