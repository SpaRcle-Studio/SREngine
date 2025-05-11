

# File AndroidNativeAppGlue.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Platform**](dir_c017a2c280f4c252cdb104ea7a64a7b4.md) **>** [**AndroidNativeAppGlue.h**](AndroidNativeAppGlue_8h.md)

[Go to the source code of this file](AndroidNativeAppGlue_8h_source.md)



* `#include <Utils/stdInclude.h>`
* `#include <poll.h>`
* `#include <pthread.h>`
* `#include <sched.h>`
* `#include <android/configuration.h>`
* `#include <android/looper.h>`
* `#include <android/native_activity.h>`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**android\_app**](structandroid__app.md) <br> |
| struct | [**android\_poll\_source**](structandroid__poll__source.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**AndroidNativeAppGlue\_8h\_1a56a0f36da7f9eaaf54bd05cc2bf49173**](#enum-androidnativeappglue_8h_1a56a0f36da7f9eaaf54bd05cc2bf49173)  <br> |
| enum  | [**AndroidNativeAppGlue\_8h\_1ae6dceca96ec2c7a1b4aa211264a87ef6**](#enum-androidnativeappglue_8h_1ae6dceca96ec2c7a1b4aa211264a87ef6)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**\_\_attribute\_\_**](#function-__attribute__) ((deprecated("Calls to app\_dummy are no longer necessary. See " "https://github.com/android-ndk/ndk/issues/381."))) <br> |
|  void | [**android\_app\_post\_exec\_cmd**](#function-android_app_post_exec_cmd) (struct [**android\_app**](structandroid__app.md) \* android\_app, int8\_t cmd) <br> |
|  void | [**android\_app\_pre\_exec\_cmd**](#function-android_app_pre_exec_cmd) (struct [**android\_app**](structandroid__app.md) \* android\_app, int8\_t cmd) <br> |
|  int8\_t | [**android\_app\_read\_cmd**](#function-android_app_read_cmd) (struct [**android\_app**](structandroid__app.md) \* android\_app) <br> |
|  void | [**android\_main**](#function-android_main) (struct [**android\_app**](structandroid__app.md) \* app) <br> |




























## Public Types Documentation




### enum AndroidNativeAppGlue\_8h\_1a56a0f36da7f9eaaf54bd05cc2bf49173 

```C++
enum AndroidNativeAppGlue_8h_1a56a0f36da7f9eaaf54bd05cc2bf49173 {
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
    APP_CMD_DESTROY
};
```




<hr>



### enum AndroidNativeAppGlue\_8h\_1ae6dceca96ec2c7a1b4aa211264a87ef6 

```C++
enum AndroidNativeAppGlue_8h_1ae6dceca96ec2c7a1b4aa211264a87ef6 {
    LOOPER_ID_MAIN = 1,
    LOOPER_ID_INPUT = 2,
    LOOPER_ID_USER = 3
};
```




<hr>
## Public Functions Documentation




### function \_\_attribute\_\_ 

```C++
__attribute__ (
    (deprecated("Calls to app_dummy are no longer necessary. See " "https://github.com/android-ndk/ndk/issues/381."))
) 
```



Dummy function that used to be used to prevent the linker from stripping app glue code. No longer necessary, since **attribute**((visibility("default"))) does this for us. 


        

<hr>



### function android\_app\_post\_exec\_cmd 

```C++
void android_app_post_exec_cmd (
    struct android_app * android_app,
    int8_t cmd
) 
```



Call with the command returned by android\_app\_read\_cmd() to do the final post-processing of the given command. You must have done your own actions for the command before calling this function. 


        

<hr>



### function android\_app\_pre\_exec\_cmd 

```C++
void android_app_pre_exec_cmd (
    struct android_app * android_app,
    int8_t cmd
) 
```



Call with the command returned by android\_app\_read\_cmd() to do the initial pre-processing of the given command. You can perform your own actions for the command after calling this function. 


        

<hr>



### function android\_app\_read\_cmd 

```C++
int8_t android_app_read_cmd (
    struct android_app * android_app
) 
```



Call when ALooper\_pollAll() returns LOOPER\_ID\_MAIN, reading the next app command message. 


        

<hr>



### function android\_main 

```C++
void android_main (
    struct android_app * app
) 
```



This is the function that application code must implement, representing the main entry to the app. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Platform/AndroidNativeAppGlue.h`

