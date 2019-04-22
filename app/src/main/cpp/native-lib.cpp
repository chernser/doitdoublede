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

#include "appLifeCycle.h"
#include "appUtils.h"


application _app;

void android_main(struct android_app *app) {

    LOGI("Android main ");

    {
        AppInitializer initializer(app);
        initializer.setApplicationName("DoItDoubleDe");
        initializer.doInit();
        _app.vkInstance = initializer.getVkInstance();
        _app.vkPhysicalDevice = initializer.getVkPhyDevice();
        _app.screen = initializer.getScreen();
        _app.screenSurface = initializer.getScreenSurface();
        LOGI("Initialization done");
    }



    {
        AppTerminator terminator(app, &_app);
        terminator.doTerminate();
        LOGI("Termination done");
    }

    LOGI("Done, done");
    exit(0);
}




