

# Struct SR\_UTILS\_NS::AndroidEvent



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Type**](#enum-type)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_UTILS\_NS::AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md) | [**AndroidEvent**](#variable-androidevent)  <br> |
|  int32\_t | [**action**](#variable-action)  <br> |
|  int32\_t | [**command**](#variable-command)  <br> |
|  struct [**SR\_UTILS\_NS::AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md) | [**key**](#variable-key)  <br> |
|  int32\_t | [**keyCode**](#variable-keycode)  <br> |
|  struct [**SR\_UTILS\_NS::AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md) | [**lifecycle**](#variable-lifecycle)  <br> |
|  struct [**SR\_UTILS\_NS::AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md) | [**motion**](#variable-motion)  <br> |
|  int32\_t | [**pointerId**](#variable-pointerid)  <br> |
|  ASensorEvent | [**sensor**](#variable-sensor)  <br> |
|  struct [**SR\_UTILS\_NS::AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md) | [**sensorEvent**](#variable-sensorevent)  <br> |
|  enum SR\_UTILS\_NS::AndroidEvent::Type | [**type**](#variable-type)  <br> |
|  ANativeWindow \* | [**window**](#variable-window)  <br> |
|  struct [**SR\_UTILS\_NS::AndroidEvent**](structSR__UTILS__NS_1_1AndroidEvent.md) | [**windowEvent**](#variable-windowevent)  <br> |
|  float | [**x**](#variable-x)  <br> |
|  float | [**y**](#variable-y)  <br> |












































## Public Types Documentation




### enum Type 

```C++
enum SR_UTILS_NS::AndroidEvent::Type {
    Motion,
    Key,
    Lifecycle,
    Window,
    Sensor
};
```




<hr>
## Public Attributes Documentation




### variable AndroidEvent 

```C++
union SR_UTILS_NS::AndroidEvent SR_UTILS_NS::AndroidEvent;
```




<hr>



### variable action 

```C++
int32_t SR_UTILS_NS::AndroidEvent::action;
```




<hr>



### variable command 

```C++
int32_t SR_UTILS_NS::AndroidEvent::command;
```




<hr>



### variable key 

```C++
struct SR_UTILS_NS::AndroidEvent SR_UTILS_NS::AndroidEvent::key;
```




<hr>



### variable keyCode 

```C++
int32_t SR_UTILS_NS::AndroidEvent::keyCode;
```




<hr>



### variable lifecycle 

```C++
struct SR_UTILS_NS::AndroidEvent SR_UTILS_NS::AndroidEvent::lifecycle;
```




<hr>



### variable motion 

```C++
struct SR_UTILS_NS::AndroidEvent SR_UTILS_NS::AndroidEvent::motion;
```




<hr>



### variable pointerId 

```C++
int32_t SR_UTILS_NS::AndroidEvent::pointerId;
```




<hr>



### variable sensor 

```C++
ASensorEvent SR_UTILS_NS::AndroidEvent::sensor;
```




<hr>



### variable sensorEvent 

```C++
struct SR_UTILS_NS::AndroidEvent SR_UTILS_NS::AndroidEvent::sensorEvent;
```




<hr>



### variable type 

```C++
enum SR_UTILS_NS::AndroidEvent::Type SR_UTILS_NS::AndroidEvent::type;
```




<hr>



### variable window 

```C++
ANativeWindow* SR_UTILS_NS::AndroidEvent::window;
```




<hr>



### variable windowEvent 

```C++
struct SR_UTILS_NS::AndroidEvent SR_UTILS_NS::AndroidEvent::windowEvent;
```




<hr>



### variable x 

```C++
float SR_UTILS_NS::AndroidEvent::x;
```




<hr>



### variable y 

```C++
float SR_UTILS_NS::AndroidEvent::y;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Platform/AndroidEvent.h`

