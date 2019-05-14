//
// Created by Sergey Chernov on 2019-05-12.
//

#include "Render.h"

Render::Render(std::shared_ptr<VulkanGraphics> graphics, VkSurfaceKHR vkSurface)
        : graphics(graphics) {

    this->vkSurface = vkSurface;
}

void Render::renderFrame(const ARenderable *renderable) {
    initSwapChain();




}

void Render::initSwapChain() {
    if (vkSwapchain != 0) {
        return;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.surface = vkSurface;

    createInfo.imageFormat = VK_FORMAT_B8G8R8_UNORM;
    createInfo.minImageCount = 1;
    createInfo.imageExtent.height = 320;
    createInfo.imageExtent.width = 240;

    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
//    createInfo.preTransform
    createInfo.queueFamilyIndexCount = 2;

    if (vkCreateSwapchainKHR(graphics->getScreen()->getDevice(), &createInfo, nullptr, &vkSwapchain) != VK_SUCCESS) {
        return;
    }
}
