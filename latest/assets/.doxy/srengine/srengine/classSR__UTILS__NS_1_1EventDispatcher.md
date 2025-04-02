

# Class SR\_UTILS\_NS::EventDispatcher



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EventDispatcher**](classSR__UTILS__NS_1_1EventDispatcher.md)










Inherited by the following classes: [SR\_UTILS\_NS::InputDispatcher](classSR__UTILS__NS_1_1InputDispatcher.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Dispatch**](#function-dispatch-12) (\_args... a) <br> |
|  void | [**Dispatch**](#function-dispatch-22) (const std::string & eventName, \_args... a) <br> |
|   | [**EventDispatcher**](#function-eventdispatcher) () = default<br> |
|  void | [**Register**](#function-register) ([**IEvent**](classSR__UTILS__NS_1_1IEvent.md) \* event) <br> |
|  void | [**Unregister**](#function-unregister) ([**IEvent**](classSR__UTILS__NS_1_1IEvent.md) \* event) <br> |
|  void | [**UnregisterAll**](#function-unregisterall) () <br> |
| virtual  | [**~EventDispatcher**](#function-eventdispatcher) () <br> |




























## Public Functions Documentation




### function Dispatch [1/2]

```C++
template<typename T, typename ... _args>
inline void SR_UTILS_NS::EventDispatcher::Dispatch (
    _args... a
) 
```




<hr>



### function Dispatch [2/2]

```C++
template<typename ... _args>
inline void SR_UTILS_NS::EventDispatcher::Dispatch (
    const std::string & eventName,
    _args... a
) 
```




<hr>



### function EventDispatcher 

```C++
SR_UTILS_NS::EventDispatcher::EventDispatcher () = default
```




<hr>



### function Register 

```C++
void SR_UTILS_NS::EventDispatcher::Register (
    IEvent * event
) 
```




<hr>



### function Unregister 

```C++
void SR_UTILS_NS::EventDispatcher::Unregister (
    IEvent * event
) 
```




<hr>



### function UnregisterAll 

```C++
void SR_UTILS_NS::EventDispatcher::UnregisterAll () 
```




<hr>



### function ~EventDispatcher 

```C++
virtual SR_UTILS_NS::EventDispatcher::~EventDispatcher () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Events/EventDispatcher.h`

