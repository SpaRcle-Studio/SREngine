

# File AndroidNativeAppGlue.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Platform**](dir_c017a2c280f4c252cdb104ea7a64a7b4.md) **>** [**AndroidNativeAppGlue.h**](AndroidNativeAppGlue_8h.md)

[Go to the documentation of this file](AndroidNativeAppGlue_8h.md)


```C++
#ifndef _ANDROID_NATIVE_APP_GLUE_H
#define _ANDROID_NATIVE_APP_GLUE_H

#include <Utils/stdInclude.h>

#include <poll.h>
#include <pthread.h>
#include <sched.h>

#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>

#ifdef __cplusplus
    extern "C" {
#endif

struct android_app;

struct android_poll_source {
    // The identifier of this source.  May be LOOPER_ID_MAIN or
    // LOOPER_ID_INPUT.
    int32_t id;

    // The android_app this ident is associated with.
    struct android_app* app;

    // Function to call to perform the standard processing of data from
    // this source.
    void (*process)(struct android_app* app, struct android_poll_source* source);
};

struct android_app {
    // The application can place a pointer to its own state object
    // here if it likes.
    void* userData;

    // Fill this in with the function to process main app commands (APP_CMD_*)
    void (*onAppCmd)(struct android_app* app, int32_t cmd);

    // Fill this in with the function to process input events.  At this point
    // the event has already been pre-dispatched, and it will be finished upon
    // return.  Return 1 if you have handled the event, 0 for any default
    // dispatching.
    int32_t (*onInputEvent)(struct android_app* app, AInputEvent* event);

    // The ANativeActivity object instance that this app is running in.
    ANativeActivity* activity;

    // The current configuration the app is running in.
    AConfiguration* config;

    // This is the last instance's saved state, as provided at creation time.
    // It is NULL if there was no state.  You can use this as you need; the
    // memory will remain around until you call android_app_exec_cmd() for
    // APP_CMD_RESUME, at which point it will be freed and savedState set to NULL.
    // These variables should only be changed when processing a APP_CMD_SAVE_STATE,
    // at which point they will be initialized to NULL and you can malloc your
    // state and place the information here.  In that case the memory will be
    // freed for you later.
    void* savedState;
    size_t savedStateSize;

    // The ALooper associated with the app's thread.
    ALooper* looper;

    // When non-NULL, this is the input queue from which the app will
    // receive user input events.
    AInputQueue* inputQueue;

    // When non-NULL, this is the window surface that the app can draw in.
    ANativeWindow* window;

    // Current content rectangle of the window; this is the area where the
    // window's content should be placed to be seen by the user.
    ARect contentRect;

    // Current state of the app's activity.  May be either APP_CMD_START,
    // APP_CMD_RESUME, APP_CMD_PAUSE, or APP_CMD_STOP; see below.
    int activityState;

    // This is non-zero when the application's NativeActivity is being
    // destroyed and waiting for the app thread to complete.
    int destroyRequested;

    // -------------------------------------------------
    // Below are "private" implementation of the glue code.

    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int msgread;
    int msgwrite;

    pthread_t thread;

    struct android_poll_source cmdPollSource;
    struct android_poll_source inputPollSource;

    int running;
    int stateSaved;
    int destroyed;
    int redrawNeeded;
    AInputQueue* pendingInputQueue;
    ANativeWindow* pendingWindow;
    ARect pendingContentRect;
};

enum {
    LOOPER_ID_MAIN = 1,

    LOOPER_ID_INPUT = 2,

    LOOPER_ID_USER = 3,
};

enum {
    APP_CMD_INPUT_CHANGED,

    APP_CMD_INIT_WINDOW,

    APP_CMD_TERM_WINDOW,

    APP_CMD_WINDOW_RESIZED,

    APP_CMD_WINDOW_REDRAW_NEEDED,

    APP_CMD_CONTENT_RECT_CHANGED,

    APP_CMD_GAINED_FOCUS,

    APP_CMD_LOST_FOCUS,

    APP_CMD_CONFIG_CHANGED,

    APP_CMD_LOW_MEMORY,

    APP_CMD_START,

    APP_CMD_RESUME,

    APP_CMD_SAVE_STATE,

    APP_CMD_PAUSE,

    APP_CMD_STOP,

    APP_CMD_DESTROY,
};

int8_t android_app_read_cmd(struct android_app* android_app);

void android_app_pre_exec_cmd(struct android_app* android_app, int8_t cmd);

void android_app_post_exec_cmd(struct android_app* android_app, int8_t cmd);

__attribute__((
    deprecated("Calls to app_dummy are no longer necessary. See "
               "https://github.com/android-ndk/ndk/issues/381."))) void
app_dummy();

extern void android_main(struct android_app* app);

#ifdef __cplusplus
}
#endif

#endif /* _ANDROID_NATIVE_APP_GLUE_H */
```


