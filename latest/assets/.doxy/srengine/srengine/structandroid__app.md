

# Struct android\_app



[**ClassList**](annotated.md) **>** [**android\_app**](structandroid__app.md)



[More...](#detailed-description)

* `#include <AndroidNativeAppGlue.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  ANativeActivity \* | [**activity**](#variable-activity)  <br> |
|  int | [**activityState**](#variable-activitystate)  <br> |
|  struct [**android\_poll\_source**](structandroid__poll__source.md) | [**cmdPollSource**](#variable-cmdpollsource)  <br> |
|  pthread\_cond\_t | [**cond**](#variable-cond)  <br> |
|  AConfiguration \* | [**config**](#variable-config)  <br> |
|  ARect | [**contentRect**](#variable-contentrect)  <br> |
|  int | [**destroyRequested**](#variable-destroyrequested)  <br> |
|  int | [**destroyed**](#variable-destroyed)  <br> |
|  struct [**android\_poll\_source**](structandroid__poll__source.md) | [**inputPollSource**](#variable-inputpollsource)  <br> |
|  AInputQueue \* | [**inputQueue**](#variable-inputqueue)  <br> |
|  ALooper \* | [**looper**](#variable-looper)  <br> |
|  int | [**msgread**](#variable-msgread)  <br> |
|  int | [**msgwrite**](#variable-msgwrite)  <br> |
|  pthread\_mutex\_t | [**mutex**](#variable-mutex)  <br> |
|  void(\* | [**onAppCmd**](#variable-onappcmd)  <br> |
|  int32\_t(\* | [**onInputEvent**](#variable-oninputevent)  <br> |
|  ARect | [**pendingContentRect**](#variable-pendingcontentrect)  <br> |
|  AInputQueue \* | [**pendingInputQueue**](#variable-pendinginputqueue)  <br> |
|  ANativeWindow \* | [**pendingWindow**](#variable-pendingwindow)  <br> |
|  int | [**redrawNeeded**](#variable-redrawneeded)  <br> |
|  int | [**running**](#variable-running)  <br> |
|  void \* | [**savedState**](#variable-savedstate)  <br> |
|  size\_t | [**savedStateSize**](#variable-savedstatesize)  <br> |
|  int | [**stateSaved**](#variable-statesaved)  <br> |
|  pthread\_t | [**thread**](#variable-thread)  <br> |
|  void \* | [**userData**](#variable-userdata)  <br> |
|  ANativeWindow \* | [**window**](#variable-window)  <br> |












































## Detailed Description


This is the interface for the standard glue code of a threaded application. In this model, the application's code is running in its own thread separate from the main thread of the process. It is not required that this thread be associated with the Java VM, although it will need to be in order to make JNI calls any Java objects. 


    
## Public Attributes Documentation




### variable activity 

```C++
ANativeActivity* android_app::activity;
```




<hr>



### variable activityState 

```C++
int android_app::activityState;
```




<hr>



### variable cmdPollSource 

```C++
struct android_poll_source android_app::cmdPollSource;
```




<hr>



### variable cond 

```C++
pthread_cond_t android_app::cond;
```




<hr>



### variable config 

```C++
AConfiguration* android_app::config;
```




<hr>



### variable contentRect 

```C++
ARect android_app::contentRect;
```




<hr>



### variable destroyRequested 

```C++
int android_app::destroyRequested;
```




<hr>



### variable destroyed 

```C++
int android_app::destroyed;
```




<hr>



### variable inputPollSource 

```C++
struct android_poll_source android_app::inputPollSource;
```




<hr>



### variable inputQueue 

```C++
AInputQueue* android_app::inputQueue;
```




<hr>



### variable looper 

```C++
ALooper* android_app::looper;
```




<hr>



### variable msgread 

```C++
int android_app::msgread;
```




<hr>



### variable msgwrite 

```C++
int android_app::msgwrite;
```




<hr>



### variable mutex 

```C++
pthread_mutex_t android_app::mutex;
```




<hr>



### variable onAppCmd 

```C++
void(* android_app::onAppCmd) (struct android_app *app, int32_t cmd);
```




<hr>



### variable onInputEvent 

```C++
int32_t(* android_app::onInputEvent) (struct android_app *app, AInputEvent *event);
```




<hr>



### variable pendingContentRect 

```C++
ARect android_app::pendingContentRect;
```




<hr>



### variable pendingInputQueue 

```C++
AInputQueue* android_app::pendingInputQueue;
```




<hr>



### variable pendingWindow 

```C++
ANativeWindow* android_app::pendingWindow;
```




<hr>



### variable redrawNeeded 

```C++
int android_app::redrawNeeded;
```




<hr>



### variable running 

```C++
int android_app::running;
```




<hr>



### variable savedState 

```C++
void* android_app::savedState;
```




<hr>



### variable savedStateSize 

```C++
size_t android_app::savedStateSize;
```




<hr>



### variable stateSaved 

```C++
int android_app::stateSaved;
```




<hr>



### variable thread 

```C++
pthread_t android_app::thread;
```




<hr>



### variable userData 

```C++
void* android_app::userData;
```




<hr>



### variable window 

```C++
ANativeWindow* android_app::window;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Platform/AndroidNativeAppGlue.h`

