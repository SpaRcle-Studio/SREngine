

# Class SR\_ANIMATIONS\_NS::AnimationState



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::AnimationClipState](classSR__ANIMATIONS__NS_1_1AnimationClipState.md),  [SR\_ANIMATIONS\_NS::AnimationEntryPointState](classSR__ANIMATIONS__NS_1_1AnimationEntryPointState.md),  [SR\_ANIMATIONS\_NS::AnimationNoneState](classSR__ANIMATIONS__NS_1_1AnimationNoneState.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  T \* | [**AddTransition**](#function-addtransition-12) (Args &&... args) <br> |
|  T \* | [**AddTransition**](#function-addtransition-22) (T \* pTransition) <br> |
|   | [**AnimationState**](#function-animationstate) () <br> |
| virtual bool | [**Compile**](#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) <br> |
|  SR\_NODISCARD [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* | [**GetActiveTransition**](#function-getactivetransition) () noexcept const<br> |
| virtual SR\_NODISCARD float\_t | [**GetDuration**](#function-getduration) () noexcept const<br> |
|  SR\_NODISCARD [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**GetMachine**](#function-getmachine) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () noexcept const = 0<br> |
| virtual SR\_NODISCARD float\_t | [**GetProgress**](#function-getprogress) () noexcept const<br> |
| virtual SR\_NODISCARD float\_t | [**GetTime**](#function-gettime) () noexcept const<br> |
|  SR\_NODISCARD Transitions & | [**GetTransitions**](#function-gettransitions-12) () noexcept<br> |
|  SR\_NODISCARD const Transitions & | [**GetTransitions**](#function-gettransitions-22) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResetOnPlay**](#function-isresetonplay) () noexcept const<br> |
|  void | [**OnTransitionBegin**](#function-ontransitionbegin) ([**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* pTransition) <br> |
|  void | [**OnTransitionDone**](#function-ontransitiondone) () <br> |
| virtual void | [**Reset**](#function-reset) () <br> |
|  void | [**SetMachine**](#function-setmachine) ([**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* pMachine) <br> |
|  void | [**SetResetOnPlay**](#function-setresetonplay) (bool reset) <br> |
| virtual void | [**Update**](#function-update-12) (const [**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) <br> |
| virtual void | [**Update**](#function-update-22) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) <br> |
|   | [**~AnimationState**](#function-animationstate) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* | [**m\_activeTransition**](#variable-m_activetransition)   = `nullptr`<br> |
|  [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**m\_machine**](#variable-m_machine)   = `nullptr`<br> |
|  bool | [**m\_resetOnPlay**](#variable-m_resetonplay)   = `false`<br> |
|  Transitions | [**m\_transitions**](#variable-m_transitions)  <br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AddTransition [1/2]

```C++
template<class T, typename ... Args>
inline T * SR_ANIMATIONS_NS::AnimationState::AddTransition (
    Args &&... args
) 
```




<hr>



### function AddTransition [2/2]

```C++
template<class T>
inline T * SR_ANIMATIONS_NS::AnimationState::AddTransition (
    T * pTransition
) 
```




<hr>



### function AnimationState 

```C++
inline explicit SR_ANIMATIONS_NS::AnimationState::AnimationState () 
```




<hr>



### function Compile 

```C++
inline virtual bool SR_ANIMATIONS_NS::AnimationState::Compile (
    CompileContext & context
) 
```




<hr>



### function GetActiveTransition 

```C++
inline SR_NODISCARD AnimationStateTransition * SR_ANIMATIONS_NS::AnimationState::GetActiveTransition () noexcept const
```




<hr>



### function GetDuration 

```C++
inline virtual SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationState::GetDuration () noexcept const
```




<hr>



### function GetMachine 

```C++
inline SR_NODISCARD AnimationStateMachine * SR_ANIMATIONS_NS::AnimationState::GetMachine () noexcept const
```




<hr>



### function GetName 

```C++
virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_ANIMATIONS_NS::AnimationState::GetName () noexcept const = 0
```




<hr>



### function GetProgress 

```C++
inline virtual SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationState::GetProgress () noexcept const
```




<hr>



### function GetTime 

```C++
inline virtual SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationState::GetTime () noexcept const
```




<hr>



### function GetTransitions [1/2]

```C++
inline SR_NODISCARD Transitions & SR_ANIMATIONS_NS::AnimationState::GetTransitions () noexcept
```




<hr>



### function GetTransitions [2/2]

```C++
inline SR_NODISCARD const Transitions & SR_ANIMATIONS_NS::AnimationState::GetTransitions () noexcept const
```




<hr>



### function IsResetOnPlay 

```C++
inline SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationState::IsResetOnPlay () noexcept const
```




<hr>



### function OnTransitionBegin 

```C++
void SR_ANIMATIONS_NS::AnimationState::OnTransitionBegin (
    AnimationStateTransition * pTransition
) 
```




<hr>



### function OnTransitionDone 

```C++
void SR_ANIMATIONS_NS::AnimationState::OnTransitionDone () 
```




<hr>



### function Reset 

```C++
inline virtual void SR_ANIMATIONS_NS::AnimationState::Reset () 
```




<hr>



### function SetMachine 

```C++
inline void SR_ANIMATIONS_NS::AnimationState::SetMachine (
    AnimationStateMachine * pMachine
) 
```




<hr>



### function SetResetOnPlay 

```C++
inline void SR_ANIMATIONS_NS::AnimationState::SetResetOnPlay (
    bool reset
) 
```




<hr>



### function Update [1/2]

```C++
inline virtual void SR_ANIMATIONS_NS::AnimationState::Update (
    const UpdateContext & context
) 
```




<hr>



### function Update [2/2]

```C++
inline virtual void SR_ANIMATIONS_NS::AnimationState::Update (
    UpdateContext & context
) 
```




<hr>



### function ~AnimationState 

```C++
SR_ANIMATIONS_NS::AnimationState::~AnimationState () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationState * SR_ANIMATIONS_NS::AnimationState::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_activeTransition 

```C++
AnimationStateTransition* SR_ANIMATIONS_NS::AnimationState::m_activeTransition;
```




<hr>



### variable m\_machine 

```C++
AnimationStateMachine* SR_ANIMATIONS_NS::AnimationState::m_machine;
```




<hr>



### variable m\_resetOnPlay 

```C++
bool SR_ANIMATIONS_NS::AnimationState::m_resetOnPlay;
```




<hr>



### variable m\_transitions 

```C++
Transitions SR_ANIMATIONS_NS::AnimationState::m_transitions;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationState.h`

