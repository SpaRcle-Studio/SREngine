

# Class SR\_GRAPH\_GUI\_NS::Node



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_GUI\_NS**](namespaceSR__GRAPH__GUI__NS.md) **>** [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddInput**](#function-addinput-14) (Pin \* pin) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddInput**](#function-addinput-24) (PinType type) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddInput**](#function-addinput-34) (const std::string & name, PinType type) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddInput**](#function-addinput-44) (const std::string & name, [**SR\_SRLM\_NS::DataType**](classSR__SRLM__NS_1_1DataType.md) \* pDataType) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddOutput**](#function-addoutput-14) (Pin \* pin) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddOutput**](#function-addoutput-24) (PinType type) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddOutput**](#function-addoutput-34) (const std::string & name, PinType type) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**AddOutput**](#function-addoutput-44) (const std::string & name, [**SR\_SRLM\_NS::DataType**](classSR__SRLM__NS_1_1DataType.md) \* pDataType) <br> |
|  void | [**Draw**](#function-draw) (NodeBuilder \* pBuilder, Pin \* pNewLinkPin) <br> |
|  SR\_NODISCARD uint64\_t | [**GetHashName**](#function-gethashname) () const<br> |
|  SR\_NODISCARD uintptr\_t | [**GetId**](#function-getid) () const<br> |
|  SR\_NODISCARD Pin \* | [**GetInputPin**](#function-getinputpin) (uint32\_t index) <br> |
|  SR\_NODISCARD const std::vector&lt; Pin \* &gt; & | [**GetInputs**](#function-getinputs) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_SRLM\_NS::LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**GetLogicalNode**](#function-getlogicalnode) () const<br> |
|  SR\_NODISCARD std::string | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD Pin \* | [**GetOutputPin**](#function-getoutputpin) (uint32\_t index) <br> |
|  SR\_NODISCARD const std::vector&lt; Pin \* &gt; & | [**GetOutputs**](#function-getoutputs) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetPinIndex**](#function-getpinindex) (const Pin \* pPin) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetPosition**](#function-getposition) () const<br> |
|  SR\_NODISCARD bool | [**IsConnector**](#function-isconnector) () const<br> |
|   | [**Node**](#function-node-16) () <br> |
|   | [**Node**](#function-node-26) (const std::string & name) <br> |
|   | [**Node**](#function-node-36) ([**SR\_SRLM\_NS::LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode) <br> |
|   | [**Node**](#function-node-46) (const std::string & name, NodeType type) <br> |
|   | [**Node**](#function-node-56) (const std::string & name, ImColor color) <br> |
|   | [**Node**](#function-node-66) (std::string name, NodeType type, ImColor color) <br> |
|  void | [**PostDraw**](#function-postdraw) () <br> |
|  void | [**RemoveInput**](#function-removeinput) (uint32\_t index) <br> |
|  void | [**RemoveOutput**](#function-removeoutput) (uint32\_t index) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**SetName**](#function-setname) (std::string name) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**SetPosition**](#function-setposition) (const SR\_MATH\_NS::FVector2 & pos) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) & | [**SetType**](#function-settype) (NodeType type) <br> |
|   | [**~Node**](#function-node) () override<br> |


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




### function AddInput [1/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddInput (
    Pin * pin
) 
```




<hr>



### function AddInput [2/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddInput (
    PinType type
) 
```




<hr>



### function AddInput [3/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddInput (
    const std::string & name,
    PinType type
) 
```




<hr>



### function AddInput [4/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddInput (
    const std::string & name,
    SR_SRLM_NS::DataType * pDataType
) 
```




<hr>



### function AddOutput [1/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddOutput (
    Pin * pin
) 
```




<hr>



### function AddOutput [2/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddOutput (
    PinType type
) 
```




<hr>



### function AddOutput [3/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddOutput (
    const std::string & name,
    PinType type
) 
```




<hr>



### function AddOutput [4/4]

```C++
Node & SR_GRAPH_GUI_NS::Node::AddOutput (
    const std::string & name,
    SR_SRLM_NS::DataType * pDataType
) 
```




<hr>



### function Draw 

```C++
void SR_GRAPH_GUI_NS::Node::Draw (
    NodeBuilder * pBuilder,
    Pin * pNewLinkPin
) 
```




<hr>



### function GetHashName 

```C++
SR_NODISCARD uint64_t SR_GRAPH_GUI_NS::Node::GetHashName () const
```




<hr>



### function GetId 

```C++
SR_NODISCARD uintptr_t SR_GRAPH_GUI_NS::Node::GetId () const
```




<hr>



### function GetInputPin 

```C++
SR_NODISCARD Pin * SR_GRAPH_GUI_NS::Node::GetInputPin (
    uint32_t index
) 
```




<hr>



### function GetInputs 

```C++
inline SR_NODISCARD const std::vector< Pin * > & SR_GRAPH_GUI_NS::Node::GetInputs () noexcept const
```




<hr>



### function GetLogicalNode 

```C++
inline SR_NODISCARD SR_SRLM_NS::LogicalNode * SR_GRAPH_GUI_NS::Node::GetLogicalNode () const
```




<hr>



### function GetName 

```C++
SR_NODISCARD std::string SR_GRAPH_GUI_NS::Node::GetName () const
```




<hr>



### function GetOutputPin 

```C++
SR_NODISCARD Pin * SR_GRAPH_GUI_NS::Node::GetOutputPin (
    uint32_t index
) 
```




<hr>



### function GetOutputs 

```C++
inline SR_NODISCARD const std::vector< Pin * > & SR_GRAPH_GUI_NS::Node::GetOutputs () noexcept const
```




<hr>



### function GetPinIndex 

```C++
SR_NODISCARD int32_t SR_GRAPH_GUI_NS::Node::GetPinIndex (
    const Pin * pPin
) const
```




<hr>



### function GetPosition 

```C++
SR_NODISCARD SR_MATH_NS::FVector2 SR_GRAPH_GUI_NS::Node::GetPosition () const
```




<hr>



### function IsConnector 

```C++
inline SR_NODISCARD bool SR_GRAPH_GUI_NS::Node::IsConnector () const
```




<hr>



### function Node [1/6]

```C++
SR_GRAPH_GUI_NS::Node::Node () 
```




<hr>



### function Node [2/6]

```C++
explicit SR_GRAPH_GUI_NS::Node::Node (
    const std::string & name
) 
```




<hr>



### function Node [3/6]

```C++
explicit SR_GRAPH_GUI_NS::Node::Node (
    SR_SRLM_NS::LogicalNode * pNode
) 
```




<hr>



### function Node [4/6]

```C++
SR_GRAPH_GUI_NS::Node::Node (
    const std::string & name,
    NodeType type
) 
```




<hr>



### function Node [5/6]

```C++
SR_GRAPH_GUI_NS::Node::Node (
    const std::string & name,
    ImColor color
) 
```




<hr>



### function Node [6/6]

```C++
SR_GRAPH_GUI_NS::Node::Node (
    std::string name,
    NodeType type,
    ImColor color
) 
```




<hr>



### function PostDraw 

```C++
void SR_GRAPH_GUI_NS::Node::PostDraw () 
```




<hr>



### function RemoveInput 

```C++
void SR_GRAPH_GUI_NS::Node::RemoveInput (
    uint32_t index
) 
```




<hr>



### function RemoveOutput 

```C++
void SR_GRAPH_GUI_NS::Node::RemoveOutput (
    uint32_t index
) 
```




<hr>



### function SetName 

```C++
Node & SR_GRAPH_GUI_NS::Node::SetName (
    std::string name
) 
```




<hr>



### function SetPosition 

```C++
Node & SR_GRAPH_GUI_NS::Node::SetPosition (
    const SR_MATH_NS::FVector2 & pos
) 
```




<hr>



### function SetType 

```C++
Node & SR_GRAPH_GUI_NS::Node::SetType (
    NodeType type
) 
```




<hr>



### function ~Node 

```C++
SR_GRAPH_GUI_NS::Node::~Node () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Node.h`

