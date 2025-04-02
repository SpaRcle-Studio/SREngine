

# Class SR\_GRAPH\_NS::GUI::NodeBuilder



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**GUI**](namespaceSR__GRAPH__NS_1_1GUI.md) **>** [**NodeBuilder**](classSR__GRAPH__NS_1_1GUI_1_1NodeBuilder.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Begin**](#function-begin) (Node \* pNode) <br> |
|  void | [**End**](#function-end) () <br> |
|  void | [**EndHeader**](#function-endheader) () <br> |
|  void | [**EndInput**](#function-endinput) () <br> |
|  void | [**EndOutput**](#function-endoutput) () <br> |
|  void | [**Header**](#function-header) (const ImVec4 & color=ImVec4(1, 1, 1, 1)) <br> |
|  void | [**Input**](#function-input) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pPin) <br> |
|  void | [**Middle**](#function-middle) () <br> |
|   | [**NodeBuilder**](#function-nodebuilder) ([**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) \* pTexture) <br> |
|  void | [**Output**](#function-output) ([**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) \* pPin) <br> |
|   | [**~NodeBuilder**](#function-nodebuilder) () override<br> |


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




### function Begin 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::Begin (
    Node * pNode
) 
```




<hr>



### function End 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::End () 
```




<hr>



### function EndHeader 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::EndHeader () 
```




<hr>



### function EndInput 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::EndInput () 
```




<hr>



### function EndOutput 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::EndOutput () 
```




<hr>



### function Header 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::Header (
    const ImVec4 & color=ImVec4(1, 1, 1, 1)
) 
```




<hr>



### function Input 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::Input (
    Pin * pPin
) 
```




<hr>



### function Middle 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::Middle () 
```




<hr>



### function NodeBuilder 

```C++
explicit SR_GRAPH_NS::GUI::NodeBuilder::NodeBuilder (
    SR_GTYPES_NS::Texture * pTexture
) 
```




<hr>



### function Output 

```C++
void SR_GRAPH_NS::GUI::NodeBuilder::Output (
    Pin * pPin
) 
```




<hr>



### function ~NodeBuilder 

```C++
SR_GRAPH_NS::GUI::NodeBuilder::~NodeBuilder () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/NodeBuilder.h`

