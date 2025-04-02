

# Class SR\_GRAPH\_NS::GUI::Link



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**GUI**](namespaceSR__GRAPH__NS_1_1GUI.md) **>** [**Link**](classSR__GRAPH__NS_1_1GUI_1_1Link.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Broke**](#function-broke) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pFrom) <br> |
|  void | [**Draw**](#function-draw) () const<br> |
|  SR\_NODISCARD [**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* | [**GetEnd**](#function-getend) () const<br> |
|  SR\_NODISCARD uintptr\_t | [**GetId**](#function-getid) () const<br> |
|  SR\_NODISCARD [**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* | [**GetStart**](#function-getstart) () const<br> |
|  SR\_NODISCARD bool | [**IsLinked**](#function-islinked-12) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pPin) const<br> |
|  SR\_NODISCARD bool | [**IsLinked**](#function-islinked-22) () const<br> |
|   | [**Link**](#function-link-13) () <br> |
|   | [**Link**](#function-link-23) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* start, [**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* end) <br> |
|   | [**Link**](#function-link-33) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* start, [**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* end, ImColor color) <br> |
|  void | [**SetEnd**](#function-setend) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pPin) <br> |
|  void | [**SetStart**](#function-setstart) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pPin) <br> |
|   | [**~Link**](#function-link) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function Broke 

```C++
void SR_GRAPH_NS::GUI::Link::Broke (
    Pin * pFrom
) 
```




<hr>



### function Draw 

```C++
void SR_GRAPH_NS::GUI::Link::Draw () const
```




<hr>



### function GetEnd 

```C++
inline SR_NODISCARD Pin * SR_GRAPH_NS::GUI::Link::GetEnd () const
```




<hr>



### function GetId 

```C++
SR_NODISCARD uintptr_t SR_GRAPH_NS::GUI::Link::GetId () const
```




<hr>



### function GetStart 

```C++
inline SR_NODISCARD Pin * SR_GRAPH_NS::GUI::Link::GetStart () const
```




<hr>



### function IsLinked [1/2]

```C++
SR_NODISCARD bool SR_GRAPH_NS::GUI::Link::IsLinked (
    Pin * pPin
) const
```




<hr>



### function IsLinked [2/2]

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::GUI::Link::IsLinked () const
```




<hr>



### function Link [1/3]

```C++
SR_GRAPH_NS::GUI::Link::Link () 
```




<hr>



### function Link [2/3]

```C++
SR_GRAPH_NS::GUI::Link::Link (
    Pin * start,
    Pin * end
) 
```




<hr>



### function Link [3/3]

```C++
SR_GRAPH_NS::GUI::Link::Link (
    Pin * start,
    Pin * end,
    ImColor color
) 
```




<hr>



### function SetEnd 

```C++
void SR_GRAPH_NS::GUI::Link::SetEnd (
    Pin * pPin
) 
```




<hr>



### function SetStart 

```C++
void SR_GRAPH_NS::GUI::Link::SetStart (
    Pin * pPin
) 
```




<hr>



### function ~Link 

```C++
SR_GRAPH_NS::GUI::Link::~Link () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Link.h`

