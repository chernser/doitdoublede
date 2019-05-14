//
// Created by Sergey Chernov on 2019-05-12.
//

#ifndef DOITDOUBLEDE_RENDER_H
#define DOITDOUBLEDE_RENDER_H

#include <memory>

#include "VulkanGraphics.h"




class ARenderable {

public:

};


/**
 * Renders primitives by map provided from Scene
 * Scene is state of the graphics.
 * Render is engine which draws scene elements
 */
class Render {


public:

    explicit Render(std::shared_ptr<VulkanGraphics> graphics, VkSurfaceKHR vkSurface);

    void renderFrame(const ARenderable *renderable);

private:

    void initSwapChain();

private:
    std::shared_ptr<VulkanGraphics> graphics;

    VkSurfaceKHR vkSurface;
    VkSwapchainKHR vkSwapchain;
};


#endif //DOITDOUBLEDE_RENDER_H
