//
// Created by Sergey Chernov on 4/18/19.
//

#ifndef DOITDOUBLEDE_APPUTILS_H
#define DOITDOUBLEDE_APPUTILS_H

#include <android/log.h>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "engine", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "engine", __VA_ARGS__))


#endif //DOITDOUBLEDE_APPUTILS_H
