#include <initializer_list>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <jni.h>
#include <cerrno>
#include <cassert>
#include <dlfcn.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>

#include <Core/Application.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Platform/AndroidNativeAppGlue.h>
#include <Utils/Debug.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Time.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/Features.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/World/Scene.h>

#include <Core/Engine.h>
#include <Core/World/World.h>

#include <android/log.h>


#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SREngine", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "SREngine", __VA_ARGS__))

struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

static int engine_init_display(struct engine* engine) {
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config = nullptr;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, nullptr, nullptr);

    /* Here, the application chooses the configuration it desires.
     * find the best match if possible, otherwise use the very first one
     */
    eglChooseConfig(display, attribs, nullptr,0, &numConfigs);
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    assert(supportedConfigs);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
    assert(numConfigs);
    auto i = 0;
    for (; i < numConfigs; i++) {
        auto& cfg = supportedConfigs[i];
        EGLint r, g, b, d;
        if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r)   &&
            eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
            eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b)  &&
            eglGetConfigAttrib(display, cfg, EGL_DEPTH_SIZE, &d) &&
            r == 8 && g == 8 && b == 8 && d == 0 ) {

            config = supportedConfigs[i];
            break;
        }
    }
    if (i == numConfigs) {
        config = supportedConfigs[0];
    }

    if (config == nullptr) {
        LOGW("Unable to initialize EGLConfig");
        return -1;
    }

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    surface = eglCreateWindowSurface(display, config, engine->app->window, nullptr);
    context = eglCreateContext(display, config, nullptr, nullptr);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    // Check openGL on the system
    auto opengl_info = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
    for (auto name : opengl_info) {
        auto info = glGetString(name);
        LOGI("OpenGL Info: %s", info);
    }
    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    return 0;
}

static void engine_draw_frame(struct engine* engine) {
    if (engine->display == nullptr) {
        // No display.
        return;
    }

    // Just fill the screen with a color.
    glClearColor(((float)engine->state.x)/engine->width, engine->state.angle,
                 ((float)engine->state.y)/engine->height, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    eglSwapBuffers(engine->display, engine->surface);
}

static void engine_term_display(struct engine* engine) {
    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
    auto* engine = (struct engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        if (engine) {
            engine->animating = 1;
            engine->state.x = AMotionEvent_getX(event, 0);
            engine->state.y = AMotionEvent_getY(event, 0);
        }
        else {
            app->onInputEvent = nullptr;
        }
        return 1;
    }
    return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    auto* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != nullptr) {
                engine_init_display(engine);
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (engine->accelerometerSensor != nullptr) {
                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                                               engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                                               engine->accelerometerSensor,
                                               (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != nullptr) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                                                engine->accelerometerSensor);
            }
            // Also stop animating.
            engine->animating = 0;
            engine_draw_frame(engine);
            break;
        default:
            break;
    }
}

ASensorManager* AcquireASensorManagerInstance(android_app* app) {
    if(!app)
        return nullptr;

    typedef ASensorManager *(*PF_GETINSTANCEFORPACKAGE)(const char *name);
    void* androidHandle = dlopen("libandroid.so", RTLD_NOW);
    auto getInstanceForPackageFunc = (PF_GETINSTANCEFORPACKAGE)
            dlsym(androidHandle, "ASensorManager_getInstanceForPackage");
    if (getInstanceForPackageFunc) {
        JNIEnv* env = nullptr;
        app->activity->vm->AttachCurrentThread(&env, nullptr);

        jclass android_content_Context = env->GetObjectClass(app->activity->clazz);
        jmethodID midGetPackageName = env->GetMethodID(android_content_Context,
                                                       "getPackageName",
                                                       "()Ljava/lang/String;");
        auto packageName= (jstring)env->CallObjectMethod(app->activity->clazz,
                                                         midGetPackageName);

        const char *nativePackageName = env->GetStringUTFChars(packageName, nullptr);
        ASensorManager* mgr = getInstanceForPackageFunc(nativePackageName);
        env->ReleaseStringUTFChars(packageName, nativePackageName);
        app->activity->vm->DetachCurrentThread();
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
    dlclose(androidHandle);

    return getInstanceFunc();
}

#include <unistd.h>

void android_main(struct android_app* state) {

    state->onInputEvent = engine_handle_input;

    /*//SREngine

    auto&& pApplication = SR_CORE_NS::Application::MakeShared();

    int32_t code = 0;

    char **argv = nullptr;
    int argc = 1;

    if (!pApplication->PreInit(argc, argv)) {
        SR_PLATFORM_NS::WriteConsoleError("Failed to pre-initialize application!\n");
        code = -1;
    }

    if (code == 0 && !pApplication->Init()) {
        SR_ERROR("Failed to initialize application!");
        code = -2;
    }

    if (code == 0 && !pApplication->Execute()) {
        SR_ERROR("Failed to execute application!");
        code = -3;
    }

    pApplication.AutoFree([](auto&& pData) {
        delete pData;
    });

    //return code;

    //SREngine*/

    struct engine engineAndroid{};

    memset(&engineAndroid, 0, sizeof(engine));
    state->userData = &engineAndroid;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engineAndroid.app = state;

    // Prepare to monitor accelerometer
    engineAndroid.sensorManager = AcquireASensorManagerInstance(state);
    engineAndroid.accelerometerSensor = ASensorManager_getDefaultSensor(
            engineAndroid.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engineAndroid.sensorEventQueue = ASensorManager_createEventQueue(
            engineAndroid.sensorManager,
            state->looper, LOOPER_ID_USER,
            nullptr, nullptr);

    if (state->savedState != nullptr) {
        // We are starting with a previous saved state; restore from it.
        engineAndroid.state = *(struct saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (true) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(engineAndroid.animating ? 0 : -1, nullptr, &events,
                                      (void**)&source)) >= 0) {

            // Process this event.
            if (source != nullptr) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engineAndroid.accelerometerSensor != nullptr) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engineAndroid.sensorEventQueue,
                                                       &event, 1) > 0) {
                        //LOGI("accelerometer: x=%f y=%f z=%f",
                        //     event.acceleration.x, event.acceleration.y,
                        //     event.acceleration.z);
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engineAndroid);
                return;
            }
        }

        if (engineAndroid.animating) {
            // Done with events; draw next animation frame.
            engineAndroid.state.angle += .01f;
            if (engineAndroid.state.angle > 1) {
                engineAndroid.state.angle = 0;
            }

            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(&engineAndroid);
        }
    }
}
