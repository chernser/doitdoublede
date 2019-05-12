#include <initializer_list>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <jni.h>
#include <errno.h>
#include <cassert>
#include <tuple>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

//#include <android/sensor.h>
#include <android_native_app_glue.h>


#include "Application.h"
#include "appUtils.h"

/**
 * Handles command from OS while chaning lifecycle
 * @param app
 * @param cmd
 */
static void app_handle_os_cmd(struct android_app *app, int32_t cmd) {
    auto application = (Application *) app->userData;
    application->setAndroidApp(app);
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            application->onSaveState();
        case APP_CMD_INIT_WINDOW:
            LOGD("lifecycle: init window");
            application->onWindowInit();
            break;
        case APP_CMD_WINDOW_RESIZED:
            LOGD("lifecycle: window resized");
            application->onWindowResize();
            break;
        case APP_CMD_TERM_WINDOW:
            LOGD("lifecycle: Terminate window");
            application->onWindowTerm();
            break;
        case APP_CMD_GAINED_FOCUS:
            LOGD("lifecycle: Gained focus");
            application->onGainedFocus();
            break;
        case APP_CMD_LOST_FOCUS:
            LOGD("lifecycle: Lost focus");
            application->onLostFocus();
            break;
        case APP_CMD_DESTROY:
            LOGD("lifecycle: Destroy");
            break;
        case APP_CMD_LOW_MEMORY:
            LOGW("Low memory! Do something!");
            break;
        case APP_CMD_PAUSE:
            LOGD("lifecycle: Paused");
            application->onPaused();
            break;
        case APP_CMD_RESUME:
            LOGD("lifecycle: Resumed");
            application->onResumed();
            break;
        default:
            break;
    }
}

int32_t app_handle_input(struct android_app *app, AInputEvent *event) {
    auto type = AInputEvent_getType(event);
    LOGD("Input event ", type);

    return 0;
}

void android_main(struct android_app *app) {
    LOGI("Android main ");
    Application application;

    app->userData = &application;
    app->onAppCmd = app_handle_os_cmd;
    app->onInputEvent = app_handle_input;

    // Main loop
    while (true) {

        // Reading events
        for (auto[eventCount, source, eventId] = std::tuple<int, android_poll_source *, int>{0,
                                                                                             NULL,
                                                                                             0};
             (eventId = ALooper_pollAll(100, nullptr, &eventCount, (void **) &source)) >= 0;) {

            if (source != nullptr) {
                source->process(app, source);
            }

            if (eventId == ALOOPER_EVENT_ERROR) {
                LOGW("Error happened");
                return;
            }
        }
    }
}




