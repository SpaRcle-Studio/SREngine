#include <Engine/Application.h>
#include <Engine/EntryPoint.h>
#include <Engine/Engine.h>
#include <Engine/World/World.h>

#include <Utils/Platform/Platform.h>
#include <Utils/Platform/AndroidNativeAppGlue.h>
#include <Utils/Platform/AndroidEvent.h>
#include <Utils/Debug.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Time.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/Features.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/World/Scene.h>

#include <android/log.h>
#include <android/sensor.h>

#include <initializer_list>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <jni.h>
#include <cerrno>
#include <cassert>
#include <dlfcn.h>
#include <unistd.h>

// ----------------- Input Callbacks -----------------
int32_t HandleInput(struct android_app* app, AInputEvent* event) {
    SR_UTILS_NS::AndroidEvent evt;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        evt.type = SR_UTILS_NS::AndroidEvent::Motion;
        int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
        evt.motion.action = action;

        size_t pointerCount = AMotionEvent_getPointerCount(event);
        for (size_t i = 0; i < pointerCount; ++i) {
            evt.motion.pointerId = AMotionEvent_getPointerId(event, i);
            evt.motion.x = AMotionEvent_getX(event, i);
            evt.motion.y = AMotionEvent_getY(event, i);
            SR_UTILS_NS::AndroidEventQueue::Instance().PushEvent(evt);
        }
    }
    else if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY) {
        evt.type = SR_UTILS_NS::AndroidEvent::Key;
        evt.key.keyCode = AKeyEvent_getKeyCode(event);
        evt.key.action = AKeyEvent_getAction(event);
        SR_UTILS_NS::AndroidEventQueue::Instance().PushEvent(evt);
    }
    return 1; // событие обработано
}

// ----------------- Command Callbacks -----------------
void HandleCmd(struct android_app* app, int32_t cmd) {
    SR_UTILS_NS::AndroidEvent evt;
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
        case APP_CMD_TERM_WINDOW:
        case APP_CMD_WINDOW_RESIZED:
        case APP_CMD_WINDOW_REDRAW_NEEDED:
        case APP_CMD_GAINED_FOCUS:
        case APP_CMD_LOST_FOCUS:
        case APP_CMD_START:
        case APP_CMD_STOP:
        case APP_CMD_DESTROY:
        evt.type = SR_UTILS_NS::AndroidEvent::Lifecycle;
        evt.lifecycle.command = cmd;
        SR_UTILS_NS::AndroidEventQueue::Instance().PushEvent(evt);
        break;
        default:
        break;
    }
}

// ----------------- Sensor Handling -----------------
void ProcessSensorEvents(ASensorEventQueue* sensorQueue, struct android_app* app) {
    if (!sensorQueue) {
        return;
    }

    ASensorEvent event;
    while (ASensorEventQueue_getEvents(sensorQueue, &event, 1) > 0) {
        SR_UTILS_NS::AndroidEvent evt;
        evt.type = SR_UTILS_NS::AndroidEvent::Sensor;
        evt.sensorEvent.sensor = event;
        SR_UTILS_NS::AndroidEventQueue::Instance().PushEvent(evt);
    }
}

void WaitApplicationWindowShow(struct android_app* state) {
    SR_PLATFORM_NS::WriteConsoleLog("android_main() : waiting main window...");

    ANativeWindow* window = nullptr;
    while (!window) {
        [[maybe_unused]] int ident = 0;
        [[maybe_unused]] int events = 0;
        struct android_poll_source* source;

        // Блокируем до следующего события, пока нет окна
        while ((ident = ALooper_pollOnce(-1, nullptr, &events, (void**)&source)) >= 0) {
            if (source) {
                source->process(state, source);
            }

            if (state->destroyRequested) {
                return; // Прекращаем запуск, если приложение закрыли
            }

            if (state->window) {
                window = state->window;
                break;
            }
        }
    }
}

void SetImmersiveMode(ANativeActivity* activity) {
    /*JNIEnv* env = nullptr;
       activity->vm->AttachCurrentThread(&env, nullptr);

       jclass cls = env->GetObjectClass(activity->clazz);

       jmethodID getWindow = env->GetMethodID(cls, "getWindow", "()Landroid/view/Window;");
       jobject window = env->CallObjectMethod(activity->clazz, getWindow);

       jclass windowClass = env->GetObjectClass(window);
       jmethodID getDecorView = env->GetMethodID(windowClass, "getDecorView", "()Landroid/view/View;");
       jobject decorView = env->CallObjectMethod(window, getDecorView);

       jclass viewClass = env->GetObjectClass(decorView);
       const int flags =
            0x00000400 | // View.SYSTEM_UI_FLAG_FULLSCREEN
            0x00000200 | // View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
            0x00001000 | // View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
            0x00000100;  // View.SYSTEM_UI_FLAG_LAYOUT_STABLE
       jmethodID setSystemUiVisibility = env->GetMethodID(viewClass, "setSystemUiVisibility", "(I)V");
       env->CallVoidMethod(decorView, setSystemUiVisibility, flags);

       activity->vm->DetachCurrentThread();*/

    /*typedef ASensorManager *(*PF_GETINSTANCEFORPACKAGE)(const char *name);
       void* androidHandle = dlopen("libandroid.so", RTLD_NOW);
       auto getInstanceForPackageFunc = (PF_GETINSTANCEFORPACKAGE)
            dlsym(androidHandle, "ASensorManager_getInstanceForPackage");
       if (getInstanceForPackageFunc) {
        JNIEnv* env = nullptr;
        activity->vm->AttachCurrentThread(&env, nullptr);

        jclass android_content_Context = env->GetObjectClass(activity->clazz);
        jmethodID midGetPackageName = env->GetMethodID(android_content_Context,
                                                       "getPackageName",
                                                       "()Ljava/lang/String;");
        auto packageName= (jstring)env->CallObjectMethod(activity->clazz,
                                                         midGetPackageName);

        const char *nativePackageName = env->GetStringUTFChars(packageName, nullptr);
        ASensorManager* mgr = getInstanceForPackageFunc(nativePackageName);
        env->ReleaseStringUTFChars(packageName, nativePackageName);
        activity->vm->DetachCurrentThread();
        if (mgr) {
            dlclose(androidHandle);
            return mgr;
        }
       }

       typedef ASensorManager *(*PF_GETINSTANCE)();
       auto getInstanceFunc = (PF_GETINSTANCE)
            dlsym(androidHandle, "ASensorManager_getInstance");
       // by all means at this point, ASensorManager_getInstance should be available
       assert(getInstanceFunc);
       dlclose(androidHandle);*/
}

void android_main(struct android_app* state) {
    SR_PLATFORM_NS::SetInstance(state);
    WaitApplicationWindowShow(state);

    SetImmersiveMode(state->activity);

    state->onAppCmd = HandleCmd;
    state->onInputEvent = HandleInput;

    // Настройка сенсоров
    ASensorManager* sensorManager = ASensorManager_getInstance();
    ASensor const* accelerometer = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    ASensorEventQueue* sensorQueue = ASensorManager_createEventQueue(sensorManager, state->looper, LOOPER_ID_USER, nullptr, nullptr);
    if (accelerometer) {
        ASensorEventQueue_enableSensor(sensorQueue, accelerometer);
        ASensorEventQueue_setEventRate(sensorQueue, accelerometer, (1000L / 60) * 1000); // 60 Hz
    }

    SR_PLATFORM_NS::WriteConsoleLog("android_main() : running engine entry point...");

    std::thread engineThread([]() {
                             char** argv = nullptr;
                             int argc = 1;

                             if (const int code = SREngineEntryPoint(argc, argv); code == 0) {
                                 SR_PLATFORM_NS::WriteConsoleLog("android_main() : engine successfully closed!");
                             }
                             else {
                                 SR_PLATFORM_NS::WriteConsoleError("android_main() : engine closed with errors!");
                             }
        });

    SR_PLATFORM_NS::WriteConsoleLog("android_main() : entering main loop...");

    while (engineThread.joinable()) {
        int ident = 0;
        int events = 0;
        struct android_poll_source* source = nullptr;

        // 0 — не блокирует, можно поставить timeout в миллисекундах
        while ((ident = ALooper_pollOnce(0, nullptr, &events, (void**)&source)) >= 0) {
            if (source) {
                source->process(state, source);
            }

            ProcessSensorEvents(sensorQueue, state);

            if (state->destroyRequested) {
                break;
            }
        }
    }

    SR_PLATFORM_NS::WriteConsoleLog("android_main() : engine thread finished!");
}
