

# Class SR\_UTILS\_NS::Event

**template &lt;typename ... \_args&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Event**](classSR__UTILS__NS_1_1Event.md)








Inherits the following classes: [SR\_UTILS\_NS::IEvent](classSR__UTILS__NS_1_1IEvent.md)


Inherited by the following classes: [SR\_UTILS\_NS::InputHandler](classSR__UTILS__NS_1_1InputHandler.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Event**](#function-event) (std::string name) <br> |
| virtual void | [**Trigger**](#function-trigger) (\_args... a) <br> |
|   | [**~Event**](#function-event) () override<br> |


## Public Functions inherited from SR_UTILS_NS::IEvent

See [SR\_UTILS\_NS::IEvent](classSR__UTILS__NS_1_1IEvent.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const std::string & | [**GetEventName**](classSR__UTILS__NS_1_1IEvent.md#function-geteventname) () const = 0<br> |
















































## Protected Functions inherited from SR_UTILS_NS::IEvent

See [SR\_UTILS\_NS::IEvent](classSR__UTILS__NS_1_1IEvent.md)

| Type | Name |
| ---: | :--- |
|   | [**IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () = default<br> |
| virtual  | [**~IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () = default<br> |






## Public Functions Documentation




### function Event 

```C++
inline explicit SR_UTILS_NS::Event::Event (
    std::string name
) 
```




<hr>



### function Trigger 

```C++
inline virtual void SR_UTILS_NS::Event::Trigger (
    _args... a
) 
```




<hr>



### function ~Event 

```C++
SR_UTILS_NS::Event::~Event () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Events/Event.h`

