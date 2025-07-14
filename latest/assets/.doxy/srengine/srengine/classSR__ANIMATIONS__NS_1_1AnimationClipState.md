

# Class SR\_ANIMATIONS\_NS::AnimationClipState



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationClipState**](classSR__ANIMATIONS__NS_1_1AnimationClipState.md)



[More...](#detailed-description)

* `#include <AnimationState.h>`



Inherits the following classes: [SR\_ANIMATIONS\_NS::AnimationState](classSR__ANIMATIONS__NS_1_1AnimationState.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**Compile**](#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) override<br> |
| virtual SR\_NODISCARD float\_t | [**GetDuration**](#function-getduration) () noexcept override const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () noexcept override const<br> |
| virtual SR\_NODISCARD float\_t | [**GetProgress**](#function-getprogress) () noexcept override const<br> |
| virtual SR\_NODISCARD float\_t | [**GetTime**](#function-gettime) () noexcept override const<br> |
| virtual void | [**Reset**](#function-reset) () override<br> |
|  void | [**SetClip**](#function-setclip) (const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**AnimationClip**](classSR__ANIMATIONS__NS_1_1AnimationClip.md) &gt; & pClip) <br> |
| virtual void | [**Update**](#function-update) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) override<br> |
|   | [**~AnimationClipState**](#function-animationclipstate) () override<br> |


## Public Functions inherited from SR_ANIMATIONS_NS::AnimationState

See [SR\_ANIMATIONS\_NS::AnimationState](classSR__ANIMATIONS__NS_1_1AnimationState.md)

| Type | Name |
| ---: | :--- |
|  T \* | [**AddTransition**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-addtransition-12) (Args &&... args) <br> |
|  T \* | [**AddTransition**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-addtransition-22) (T \* pTransition) <br> |
|   | [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-animationstate) () <br> |
| virtual bool | [**Compile**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) <br> |
|  SR\_NODISCARD [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* | [**GetActiveTransition**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getactivetransition) () noexcept const<br> |
| virtual SR\_NODISCARD float\_t | [**GetDuration**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getduration) () noexcept const<br> |
|  SR\_NODISCARD [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**GetMachine**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getmachine) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getname) () noexcept const = 0<br> |
| virtual SR\_NODISCARD float\_t | [**GetProgress**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getprogress) () noexcept const<br> |
| virtual SR\_NODISCARD float\_t | [**GetTime**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-gettime) () noexcept const<br> |
|  SR\_NODISCARD Transitions & | [**GetTransitions**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-gettransitions-12) () noexcept<br> |
|  SR\_NODISCARD const Transitions & | [**GetTransitions**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-gettransitions-22) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResetOnPlay**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-isresetonplay) () noexcept const<br> |
|  void | [**OnTransitionBegin**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-ontransitionbegin) ([**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* pTransition) <br> |
|  void | [**OnTransitionDone**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-ontransitiondone) () <br> |
| virtual void | [**Reset**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-reset) () <br> |
|  void | [**SetMachine**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-setmachine) ([**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* pMachine) <br> |
|  void | [**SetResetOnPlay**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-setresetonplay) (bool reset) <br> |
| virtual void | [**Update**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-update-12) (const [**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) <br> |
| virtual void | [**Update**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-update-22) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) <br> |
|   | [**~AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-animationstate) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationClipState**](classSR__ANIMATIONS__NS_1_1AnimationClipState.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |


## Public Static Functions inherited from SR_ANIMATIONS_NS::AnimationState

See [SR\_ANIMATIONS\_NS::AnimationState](classSR__ANIMATIONS__NS_1_1AnimationState.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**Load**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**ChannelUpdateContext**](structSR__ANIMATIONS__NS_1_1ChannelUpdateContext.md) &gt; | [**m\_channelContexts**](#variable-m_channelcontexts)  <br> |
|  std::vector&lt; uint32\_t &gt; | [**m\_channelPlayState**](#variable-m_channelplaystate)  <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**AnimationClip**](classSR__ANIMATIONS__NS_1_1AnimationClip.md) &gt; | [**m\_clip**](#variable-m_clip)   = `nullptr`<br> |
|  float\_t | [**m\_duration**](#variable-m_duration)   = `0.f`<br> |
|  uint32\_t | [**m\_maxKeyFrame**](#variable-m_maxkeyframe)   = `0`<br> |
|  float\_t | [**m\_time**](#variable-m_time)   = `0.f`<br> |


## Protected Attributes inherited from SR_ANIMATIONS_NS::AnimationState

See [SR\_ANIMATIONS\_NS::AnimationState](classSR__ANIMATIONS__NS_1_1AnimationState.md)

| Type | Name |
| ---: | :--- |
|  [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* | [**m\_activeTransition**](classSR__ANIMATIONS__NS_1_1AnimationState.md#variable-m_activetransition)   = `nullptr`<br> |
|  [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**m\_machine**](classSR__ANIMATIONS__NS_1_1AnimationState.md#variable-m_machine)   = `nullptr`<br> |
|  bool | [**m\_resetOnPlay**](classSR__ANIMATIONS__NS_1_1AnimationState.md#variable-m_resetonplay)   = `false`<br> |
|  Transitions | [**m\_transitions**](classSR__ANIMATIONS__NS_1_1AnimationState.md#variable-m_transitions)  <br> |


















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Detailed Description



 


    
## Public Functions Documentation




### function Compile 

```C++
virtual bool SR_ANIMATIONS_NS::AnimationClipState::Compile (
    CompileContext & context
) override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::Compile*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-compile)


<hr>



### function GetDuration 

```C++
inline virtual SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationClipState::GetDuration () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::GetDuration*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getduration)


<hr>



### function GetName 

```C++
virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_ANIMATIONS_NS::AnimationClipState::GetName () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::GetName*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getname)


<hr>



### function GetProgress 

```C++
virtual SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationClipState::GetProgress () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::GetProgress*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getprogress)


<hr>



### function GetTime 

```C++
inline virtual SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationClipState::GetTime () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::GetTime*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-gettime)


<hr>



### function Reset 

```C++
virtual void SR_ANIMATIONS_NS::AnimationClipState::Reset () override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::Reset*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-reset)


<hr>



### function SetClip 

```C++
void SR_ANIMATIONS_NS::AnimationClipState::SetClip (
    const SR_HTYPES_NS::SharedPtr < AnimationClip > & pClip
) 
```




<hr>



### function Update 

```C++
virtual void SR_ANIMATIONS_NS::AnimationClipState::Update (
    UpdateContext & context
) override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::Update*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-update-22)


<hr>



### function ~AnimationClipState 

```C++
SR_ANIMATIONS_NS::AnimationClipState::~AnimationClipState () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationClipState * SR_ANIMATIONS_NS::AnimationClipState::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_channelContexts 

```C++
std::vector<ChannelUpdateContext> SR_ANIMATIONS_NS::AnimationClipState::m_channelContexts;
```




<hr>



### variable m\_channelPlayState 

```C++
std::vector<uint32_t> SR_ANIMATIONS_NS::AnimationClipState::m_channelPlayState;
```




<hr>



### variable m\_clip 

```C++
SR_HTYPES_NS::SharedPtr<AnimationClip> SR_ANIMATIONS_NS::AnimationClipState::m_clip;
```




<hr>



### variable m\_duration 

```C++
float_t SR_ANIMATIONS_NS::AnimationClipState::m_duration;
```




<hr>



### variable m\_maxKeyFrame 

```C++
uint32_t SR_ANIMATIONS_NS::AnimationClipState::m_maxKeyFrame;
```




<hr>



### variable m\_time 

```C++
float_t SR_ANIMATIONS_NS::AnimationClipState::m_time;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationState.h`

