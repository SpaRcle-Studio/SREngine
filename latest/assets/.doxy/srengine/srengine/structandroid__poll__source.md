

# Struct android\_poll\_source



[**ClassList**](annotated.md) **>** [**android\_poll\_source**](structandroid__poll__source.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  struct [**android\_app**](structandroid__app.md) \* | [**app**](#variable-app)  <br> |
|  int32\_t | [**id**](#variable-id)  <br> |
|  void(\* | [**process**](#variable-process)  <br> |












































## Public Attributes Documentation




### variable app 

```C++
struct android_app* android_poll_source::app;
```




<hr>



### variable id 

```C++
int32_t android_poll_source::id;
```




<hr>



### variable process 

```C++
void(* android_poll_source::process) (struct android_app *app, struct android_poll_source *source);
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Platform/AndroidNativeAppGlue.h`

