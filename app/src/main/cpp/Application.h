//
// Created by Sergey Chernov on 2019-05-12.
//

#ifndef DOITDOUBLEDE_APPLICATION_H
#define DOITDOUBLEDE_APPLICATION_H

#include <memory>
#include <tuple>

#include "VulkanGraphics.h"


struct ApplicationState {

    VulkanGraphicsState graphicsState;
};


/**
 * Describes high-level relations and behaviour of application
 * Handles all lifecycle events
 * Holds root application state, can restore it and build.
 */
class Application {

public:
    Application();


    void setAndroidApp(android_app *androidApp) { this->androidApp = androidApp; }


    void onSaveState();

    void onPaused();

    void onResumed();

    void onLostFocus();

    void onGainedFocus();

    void onWindowInit();

    void onWindowTerm();

    void onWindowResize();

private:

    /**
     * Returns application state and size.
     * Application state is located in dynamic memory
     * @return
     */
    size_t stateSnapshot(ApplicationState *outState);

private:
    std::shared_ptr<VulkanGraphics> graphics;
    std::unique_ptr<ApplicationState> appState;

    bool isPaused = true;
    bool hasFocus = false;


    android_app *androidApp;
};


#endif //DOITDOUBLEDE_APPLICATION_H
