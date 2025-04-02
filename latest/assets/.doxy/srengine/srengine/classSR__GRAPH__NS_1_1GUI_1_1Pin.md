

# Class SR\_GRAPH\_NS::GUI::Pin



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**GUI**](namespaceSR__GRAPH__NS_1_1GUI.md) **>** [**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddLink**](#function-addlink) ([**Link**](classSR__GRAPH__NS_1_1GUI_1_1Link.md) \* link) <br> |
|  void | [**Begin**](#function-begin) (PinKind kind) const<br> |
|  SR\_NODISCARD bool | [**CanLink**](#function-canlink) () const<br> |
|  void | [**DrawOption**](#function-drawoption) () <br> |
|  void | [**DrawPinIcon**](#function-drawpinicon) (bool connected, uint32\_t alpha) <br> |
|  void | [**End**](#function-end) () const<br> |
|  SR\_NODISCARD DataTypePtr | [**GetDataType**](#function-getdatatype) () const<br> |
|  SR\_NODISCARD uintptr\_t | [**GetId**](#function-getid) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetIndex**](#function-getindex) () const<br> |
|  SR\_NODISCARD PinKind | [**GetKind**](#function-getkind) () const<br> |
|  SR\_NODISCARD const std::string & | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD Node \* | [**GetNode**](#function-getnode) () const<br> |
|  SR\_NODISCARD PinType | [**GetType**](#function-gettype) () const<br> |
|  SR\_NODISCARD float\_t | [**GetWidth**](#function-getwidth) () const<br> |
|  SR\_NODISCARD bool | [**IsLinked**](#function-islinked-12) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pin) const<br> |
|  SR\_NODISCARD bool | [**IsLinked**](#function-islinked-22) () const<br> |
|   | [**Pin**](#function-pin-15) () <br> |
|   | [**Pin**](#function-pin-25) (const std::string & name) <br> |
|   | [**Pin**](#function-pin-35) (const std::string & name, DataTypePtr pData) <br> |
|   | [**Pin**](#function-pin-45) (const std::string & name, PinKind kind) <br> |
|   | [**Pin**](#function-pin-55) (std::string name, PinKind kind, DataTypePtr pData) <br> |
|  void | [**PostDrawOption**](#function-postdrawoption) () <br> |
|  void | [**RemoveLink**](#function-removelink) ([**Link**](classSR__GRAPH__NS_1_1GUI_1_1Link.md) \* link) <br> |
|  void | [**SetNode**](#function-setnode) (Node \* node) <br> |
|   | [**~Pin**](#function-pin) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  ImColor | [**GetIconColor**](#function-geticoncolor) (const PinType & type) <br> |
|  IconType | [**GetIconType**](#function-geticontype) (const PinType & type) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function AddLink 

```C++
void SR_GRAPH_NS::GUI::Pin::AddLink (
    Link * link
) 
```




<hr>



### function Begin 

```C++
void SR_GRAPH_NS::GUI::Pin::Begin (
    PinKind kind
) const
```




<hr>



### function CanLink 

```C++
SR_NODISCARD bool SR_GRAPH_NS::GUI::Pin::CanLink () const
```




<hr>



### function DrawOption 

```C++
void SR_GRAPH_NS::GUI::Pin::DrawOption () 
```




<hr>



### function DrawPinIcon 

```C++
void SR_GRAPH_NS::GUI::Pin::DrawPinIcon (
    bool connected,
    uint32_t alpha
) 
```




<hr>



### function End 

```C++
void SR_GRAPH_NS::GUI::Pin::End () const
```




<hr>



### function GetDataType 

```C++
inline SR_NODISCARD DataTypePtr SR_GRAPH_NS::GUI::Pin::GetDataType () const
```




<hr>



### function GetId 

```C++
inline SR_NODISCARD uintptr_t SR_GRAPH_NS::GUI::Pin::GetId () const
```




<hr>



### function GetIndex 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::GUI::Pin::GetIndex () const
```




<hr>



### function GetKind 

```C++
inline SR_NODISCARD PinKind SR_GRAPH_NS::GUI::Pin::GetKind () const
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD const std::string & SR_GRAPH_NS::GUI::Pin::GetName () const
```




<hr>



### function GetNode 

```C++
inline SR_NODISCARD Node * SR_GRAPH_NS::GUI::Pin::GetNode () const
```




<hr>



### function GetType 

```C++
SR_NODISCARD PinType SR_GRAPH_NS::GUI::Pin::GetType () const
```




<hr>



### function GetWidth 

```C++
SR_NODISCARD float_t SR_GRAPH_NS::GUI::Pin::GetWidth () const
```




<hr>



### function IsLinked [1/2]

```C++
SR_NODISCARD bool SR_GRAPH_NS::GUI::Pin::IsLinked (
    Pin * pin
) const
```




<hr>



### function IsLinked [2/2]

```C++
SR_NODISCARD bool SR_GRAPH_NS::GUI::Pin::IsLinked () const
```




<hr>



### function Pin [1/5]

```C++
SR_GRAPH_NS::GUI::Pin::Pin () 
```




<hr>



### function Pin [2/5]

```C++
explicit SR_GRAPH_NS::GUI::Pin::Pin (
    const std::string & name
) 
```




<hr>



### function Pin [3/5]

```C++
SR_GRAPH_NS::GUI::Pin::Pin (
    const std::string & name,
    DataTypePtr pData
) 
```




<hr>



### function Pin [4/5]

```C++
SR_GRAPH_NS::GUI::Pin::Pin (
    const std::string & name,
    PinKind kind
) 
```




<hr>



### function Pin [5/5]

```C++
SR_GRAPH_NS::GUI::Pin::Pin (
    std::string name,
    PinKind kind,
    DataTypePtr pData
) 
```




<hr>



### function PostDrawOption 

```C++
void SR_GRAPH_NS::GUI::Pin::PostDrawOption () 
```




<hr>



### function RemoveLink 

```C++
void SR_GRAPH_NS::GUI::Pin::RemoveLink (
    Link * link
) 
```




<hr>



### function SetNode 

```C++
void SR_GRAPH_NS::GUI::Pin::SetNode (
    Node * node
) 
```




<hr>



### function ~Pin 

```C++
SR_GRAPH_NS::GUI::Pin::~Pin () override
```




<hr>
## Public Static Functions Documentation




### function GetIconColor 

```C++
static ImColor SR_GRAPH_NS::GUI::Pin::GetIconColor (
    const PinType & type
) 
```




<hr>



### function GetIconType 

```C++
static IconType SR_GRAPH_NS::GUI::Pin::GetIconType (
    const PinType & type
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Pin.h`

