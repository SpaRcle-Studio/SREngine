

# Class SR\_ANIMATIONS\_NS::AnimationGraphNodeStateMachine



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationGraphNodeStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationGraphNodeStateMachine.md)



[More...](#detailed-description)

* `#include <AnimationGraphNode.h>`



Inherits the following classes: [SR\_ANIMATIONS\_NS::AnimationGraphNode](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AnimationGraphNodeStateMachine**](#function-animationgraphnodestatemachine) () <br> |
| virtual void | [**Compile**](#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) override<br> |
|  SR\_NODISCARD [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**GetMachine**](#function-getmachine) () noexcept const<br> |
| virtual SR\_NODISCARD AnimationGraphNodeType | [**GetType**](#function-gettype) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsStateActive**](#function-isstateactive) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) override const<br> |
|  void | [**SetStateMachine**](#function-setstatemachine) ([**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* pMachine) <br> |
| virtual SR\_NODISCARD [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md) \* | [**Update**](#function-update) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context, const [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) & from) override<br> |
|   | [**~AnimationGraphNodeStateMachine**](#function-animationgraphnodestatemachine) () override<br> |


## Public Functions inherited from SR_ANIMATIONS_NS::AnimationGraphNode

See [SR\_ANIMATIONS\_NS::AnimationGraphNode](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md)

| Type | Name |
| ---: | :--- |
|   | [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-animationgraphnode) (uint16\_t input, uint16\_t output) <br> |
| virtual void | [**Compile**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) <br> |
|  void | [**ConnectTo**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-connectto) ([**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* pNode, uint16\_t fromPinIndex, uint16\_t toPinIndex) <br> |
|  SR\_NODISCARD uint64\_t | [**GetIndex**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-getindex) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetInputCount**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-getinputcount) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetOutputCount**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-getoutputcount) () noexcept const<br> |
| virtual SR\_NODISCARD AnimationGraphNodeType | [**GetType**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-gettype) () noexcept const = 0<br> |
| virtual SR\_NODISCARD bool | [**IsStateActive**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-isstateactive) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  void | [**SetGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-setgraph) ([**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md) \* pGraph) <br> |
| virtual SR\_NODISCARD [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md) \* | [**Update**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-update) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context, const [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) & from) = 0<br> |
|   | [**~AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-animationgraphnode) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationGraphNodeStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationGraphNodeStateMachine.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |


## Public Static Functions inherited from SR_ANIMATIONS_NS::AnimationGraphNode

See [SR\_ANIMATIONS\_NS::AnimationGraphNode](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* | [**Load**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**m\_stateMachine**](#variable-m_statemachine)   = `nullptr`<br> |


## Protected Attributes inherited from SR_ANIMATIONS_NS::AnimationGraphNode

See [SR\_ANIMATIONS\_NS::AnimationGraphNode](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md)

| Type | Name |
| ---: | :--- |
|  [**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md) \* | [**m\_graph**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#variable-m_graph)   = `nullptr`<br> |
|  std::vector&lt; std::optional&lt; [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) &gt; &gt; | [**m\_inputPins**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#variable-m_inputpins)  <br> |
|  std::vector&lt; std::optional&lt; [**AnimationLink**](structSR__ANIMATIONS__NS_1_1AnimationLink.md) &gt; &gt; | [**m\_outputPins**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#variable-m_outputpins)  <br> |
|  [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md) \* | [**m\_pose**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#variable-m_pose)   = `nullptr`<br> |


















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Detailed Description



 


    
## Public Functions Documentation




### function AnimationGraphNodeStateMachine 

```C++
inline SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::AnimationGraphNodeStateMachine () 
```




<hr>



### function Compile 

```C++
virtual void SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::Compile (
    CompileContext & context
) override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationGraphNode::Compile*](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-compile)


<hr>



### function GetMachine 

```C++
inline SR_NODISCARD AnimationStateMachine * SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::GetMachine () noexcept const
```




<hr>



### function GetType 

```C++
inline virtual SR_NODISCARD AnimationGraphNodeType SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::GetType () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationGraphNode::GetType*](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-gettype)


<hr>



### function IsStateActive 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::IsStateActive (
    SR_UTILS_NS::StringAtom name
) override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationGraphNode::IsStateActive*](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-isstateactive)


<hr>



### function SetStateMachine 

```C++
void SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::SetStateMachine (
    AnimationStateMachine * pMachine
) 
```




<hr>



### function Update 

```C++
virtual SR_NODISCARD AnimationPose * SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::Update (
    UpdateContext & context,
    const AnimationLink & from
) override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationGraphNode::Update*](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md#function-update)


<hr>



### function ~AnimationGraphNodeStateMachine 

```C++
SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::~AnimationGraphNodeStateMachine () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationGraphNodeStateMachine * SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_stateMachine 

```C++
AnimationStateMachine* SR_ANIMATIONS_NS::AnimationGraphNodeStateMachine::m_stateMachine;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationGraphNode.h`

