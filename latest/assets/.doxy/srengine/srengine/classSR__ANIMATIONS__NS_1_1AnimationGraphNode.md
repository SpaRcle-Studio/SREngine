

# Class SR\_ANIMATIONS\_NS::AnimationGraphNode



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md)



[More...](#detailed-description)

* `#include <AnimationGraphNode.h>`



Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::AnimationGraphNodeFinal](classSR__ANIMATIONS__NS_1_1AnimationGraphNodeFinal.md),  [SR\_ANIMATIONS\_NS::AnimationGraphNodeStateMachine](classSR__ANIMATIONS__NS_1_1AnimationGraphNodeStateMachine.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AnimationGraphNode**](#function-animationgraphnode) (uint16\_t input, uint16\_t output) <br> |
| virtual void | [**Compile**](#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) <br> |
|  void | [**ConnectTo**](#function-connectto) ([**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* pNode, uint16\_t fromPinIndex, uint16\_t toPinIndex) <br> |
|  SR\_NODISCARD uint64\_t | [**GetIndex**](#function-getindex) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetInputCount**](#function-getinputcount) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetOutputCount**](#function-getoutputcount) () noexcept const<br> |
| virtual SR\_NODISCARD AnimationGraphNodeType | [**GetType**](#function-gettype) () noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsStateActive**](#function-isstateactive) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  void | [**SetGraph**](#function-setgraph) ([**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md) \* pGraph) <br> |
| virtual SR\_NODISCARD [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md) \* | [**Update**](#function-update) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context, const [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) & from) = 0<br> |
|   | [**~AnimationGraphNode**](#function-animationgraphnode) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md) \* | [**m\_graph**](#variable-m_graph)   = `nullptr`<br> |
|  std::vector&lt; std::optional&lt; [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) &gt; &gt; | [**m\_inputPins**](#variable-m_inputpins)  <br> |
|  std::vector&lt; std::optional&lt; [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) &gt; &gt; | [**m\_outputPins**](#variable-m_outputpins)  <br> |
|  [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md) \* | [**m\_pose**](#variable-m_pose)   = `nullptr`<br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Detailed Description



 


    
## Public Functions Documentation




### function AnimationGraphNode 

```C++
explicit SR_ANIMATIONS_NS::AnimationGraphNode::AnimationGraphNode (
    uint16_t input,
    uint16_t output
) 
```





**Parameters:**


* `input` - сколько данная нода имеет входных пинов 
* `output` - сколько данная нода имеет выходных пинов 




        

<hr>



### function Compile 

```C++
inline virtual void SR_ANIMATIONS_NS::AnimationGraphNode::Compile (
    CompileContext & context
) 
```




<hr>



### function ConnectTo 

```C++
void SR_ANIMATIONS_NS::AnimationGraphNode::ConnectTo (
    AnimationGraphNode * pNode,
    uint16_t fromPinIndex,
    uint16_t toPinIndex
) 
```




<hr>



### function GetIndex 

```C++
SR_NODISCARD uint64_t SR_ANIMATIONS_NS::AnimationGraphNode::GetIndex () const
```




<hr>



### function GetInputCount 

```C++
inline SR_NODISCARD uint32_t SR_ANIMATIONS_NS::AnimationGraphNode::GetInputCount () noexcept const
```




<hr>



### function GetOutputCount 

```C++
inline SR_NODISCARD uint32_t SR_ANIMATIONS_NS::AnimationGraphNode::GetOutputCount () noexcept const
```




<hr>



### function GetType 

```C++
virtual SR_NODISCARD AnimationGraphNodeType SR_ANIMATIONS_NS::AnimationGraphNode::GetType () noexcept const = 0
```




<hr>



### function IsStateActive 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationGraphNode::IsStateActive (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function SetGraph 

```C++
inline void SR_ANIMATIONS_NS::AnimationGraphNode::SetGraph (
    AnimationGraph * pGraph
) 
```




<hr>



### function Update 

```C++
virtual SR_NODISCARD AnimationPose * SR_ANIMATIONS_NS::AnimationGraphNode::Update (
    UpdateContext & context,
    const AnimationLink & from
) = 0
```




<hr>



### function ~AnimationGraphNode 

```C++
SR_ANIMATIONS_NS::AnimationGraphNode::~AnimationGraphNode () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationGraphNode * SR_ANIMATIONS_NS::AnimationGraphNode::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_graph 

```C++
AnimationGraph* SR_ANIMATIONS_NS::AnimationGraphNode::m_graph;
```




<hr>



### variable m\_inputPins 

```C++
std::vector<std::optional<AnimationLink> > SR_ANIMATIONS_NS::AnimationGraphNode::m_inputPins;
```




<hr>



### variable m\_outputPins 

```C++
std::vector<std::optional<AnimationLink> > SR_ANIMATIONS_NS::AnimationGraphNode::m_outputPins;
```




<hr>



### variable m\_pose 

```C++
AnimationPose* SR_ANIMATIONS_NS::AnimationGraphNode::m_pose;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationGraphNode.h`

