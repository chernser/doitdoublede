//
// Created by Sergey Chernov on 2019-05-12.
//
#include <cstdlib>
#include <memory>

#include "Application.h"

#include <android/log.h>

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "app", __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "app", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "app", __VA_ARGS__))


size_t Application::stateSnapshot(ApplicationState *outState) {
    return 0;
}

Application::Application() : graphics(nullptr),
                             render(nullptr) {

    graphics = std::shared_ptr<VulkanGraphics>(new VulkanGraphics());
}

void Application::onSaveState() {
    LOGI("Saving state");
    auto state = (ApplicationState *) malloc(sizeof(ApplicationState));
    auto size = this->stateSnapshot(state);
    if (size > 0) {
        androidApp->savedState = reinterpret_cast<void *>(state);
        androidApp->savedStateSize = size;
    } else {
        free(state);
    }
    render = nullptr;
    scene = nullptr;
}

void Application::onPaused() {
    this->isPaused = true;
}

void Application::onResumed() {
    this->isPaused = false;
    graphics->createLogicalDevices();
    // load state to scene
    scene = std::shared_ptr<Scene>(new Scene());
}

void Application::onWindowInit() {

    if (isPaused) {
        // At this point user sees snapshot in applications preview.
    } else {
        auto surface = graphics->createSurface(androidApp->window);
        render = std::unique_ptr<Render>(new Render(this->graphics, surface));
    }
}

void Application::onGainedFocus() {
    this->hasFocus = true;
    // finalize initialization
}

void Application::onLostFocus() {
    this->hasFocus = false;
}

void Application::onWindowTerm() {

}

void Application::onWindowResize() {

}

void Application::onLoopEnd() {

    if (hasFocus) {
        render->renderFrame((ARenderable *) scene.get());
    }
}
