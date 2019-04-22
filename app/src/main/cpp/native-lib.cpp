#include <initializer_list>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <jni.h>
#include <errno.h>
#include <cassert>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

//#include <android/sensor.h>
#include <android_native_app_glue.h>

#include "VulkanGraphics.h"
#include "appUtils.h"

class Application : public VulkanGraphics {
public:
    Application(ANativeWindow *nativeWindow) : VulkanGraphics(nativeWindow)
    {

    }

};

void android_main(struct android_app *app) {
    LOGI("Android main ");

    Application application(app->window);

    LOGI("Done, done");
    exit(0);
}




