#include <Engine/Application.h>
#include <Engine/EntryPoint.h>
#include <Engine/Engine.h>
#include <Engine/World/World.h>

#include <Utils/Platform/Platform.h>
#include <Utils/Platform/AndroidNativeAppGlue.h>
#include <Utils/Platform/AndroidEvent.h>
#include <Utils/Platform/AndroidInput.h>
#include <Utils/Platform/AndroidLifecycle.h>
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
    return SR_PLATFORM_NS::QueueAndroidInputEvent(event);
}

// ----------------- Command Callbacks -----------------
void HandleCmd(struct android_app* app, int32_t cmd) {
    SR_PLATFORM_NS::PublishAndroidLifecycle(cmd, app->window);
}

// ----------------- Sensor Handling -----------------
void ProcessSensorEvents(ASensorEventQueue* sensorQueue, struct android_app* app) {
    if (!sensorQueue){
        return;
    }

    ASensorEvent event;
    while (ASensorEventQueue_getEvents(sensorQueue, &event, 1) > 0) {
        SR_UTILS_NS::AndroidEvent evt;
        evt.type = SR_UTILS_NS::AndroidEvent::Sensor;
        evt.sensorEvent.sensor = event;
        SR_PLATFORM_NS::PushAndroidInputEvent(evt);
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

            if (state->window && ANativeWindow_getWidth(state->window) > 0 && ANativeWindow_getHeight(state->window) > 0) {
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
    state->onAppCmd = HandleCmd;
    state->onInputEvent = HandleInput;
    WaitApplicationWindowShow(state);
    if (state->destroyRequested || !state->window) {
        SR_PLATFORM_NS::NotifyAndroidEngineStopped();
        return;
    }
    SetImmersiveMode(state->activity);

    // Настройка сенсоров
    ASensorManager* sensorManager = ASensorManager_getInstance();
    ASensor const* accelerometer = sensorManager ? ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER) : nullptr;
    ASensorEventQueue* sensorQueue = sensorManager ? ASensorManager_createEventQueue(sensorManager, state->looper, LOOPER_ID_USER, nullptr, nullptr) : nullptr;
    bool sensorEnabled = false;

    SR_PLATFORM_NS::WriteConsoleLog("android_main() : running engine entry point...");

    std::atomic<bool> engineFinished = false;
    // This launcher thread outlives the engine Thread::Factory destroyed by the entry point.
    std::thread engineThread([&engineFinished, state]() {
        char program[] = "SREngine";
        char* arguments[] = {program, nullptr};

        if (const int code = SREngineEntryPoint(1, arguments); code == 0) {
            SR_PLATFORM_NS::WriteConsoleLog("android_main() : engine successfully closed!");
        }
        else {
            SR_PLATFORM_NS::WriteConsoleError("android_main() : engine closed with errors!");
        }
        SR_PLATFORM_NS::NotifyAndroidEngineStopped();
        engineFinished = true;
        ALooper_wake(state->looper);
    });

    SR_PLATFORM_NS::WriteConsoleLog("android_main() : entering main loop...");

    while (!engineFinished.load()) {
        int32_t ident = 0;
        int32_t events = 0;
        struct android_poll_source* source = nullptr;

        // Engine completion wakes the looper; the timeout also prevents idle busy-spinning.
        if ((ident = ALooper_pollOnce(100, nullptr, &events, (void**)&source)) >= 0) {
            if (source) {
                source->process(state, source);
            }

            const bool enableSensor = state->activityState == APP_CMD_RESUME && !state->destroyRequested;
            if (sensorQueue && accelerometer && sensorEnabled != enableSensor) {
                if (enableSensor) {
                    ASensorEventQueue_enableSensor(sensorQueue, accelerometer);
                    ASensorEventQueue_setEventRate(sensorQueue, accelerometer, (1000L / 60) * 1000);
                }
                else {
                    ASensorEventQueue_disableSensor(sensorQueue, accelerometer);
                }
                sensorEnabled = enableSensor;
            }
            ProcessSensorEvents(sensorQueue, state);
        }
    }

    engineThread.join();
    if (sensorQueue) {
        ASensorManager_destroyEventQueue(sensorManager, sensorQueue);
    }
    if (!state->destroyRequested) {
        ANativeActivity_finish(state->activity);
        while (!state->destroyRequested) {
            int32_t events = 0;
            android_poll_source* source = nullptr;
            if (ALooper_pollOnce(-1, nullptr, &events, reinterpret_cast<void**>(&source)) >= 0 && source) {
                source->process(state, source);
            }
        }
    }

    SR_PLATFORM_NS::WriteConsoleLog("android_main() : engine thread finished!");
}
