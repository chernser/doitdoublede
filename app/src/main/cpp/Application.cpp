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

Application::Application() {

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
}

void Application::onPaused() {

}

void Application::onResumed() {

}

void Application::onWindowInit() {

}

void Application::onGainedFocus() {

}

void Application::onLostFocus() {

}

void Application::onWindowTerm() {

}

void Application::onWindowResize() {

}
