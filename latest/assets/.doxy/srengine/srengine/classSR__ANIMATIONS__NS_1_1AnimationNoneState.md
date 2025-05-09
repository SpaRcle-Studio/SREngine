

# Class SR\_ANIMATIONS\_NS::AnimationNoneState



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationNoneState**](classSR__ANIMATIONS__NS_1_1AnimationNoneState.md)



[More...](#detailed-description)

* `#include <AnimationState.h>`



Inherits the following classes: [SR\_ANIMATIONS\_NS::AnimationState](classSR__ANIMATIONS__NS_1_1AnimationState.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () noexcept override const<br> |


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




## Public Static Functions inherited from SR_ANIMATIONS_NS::AnimationState

See [SR\_ANIMATIONS\_NS::AnimationState](classSR__ANIMATIONS__NS_1_1AnimationState.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**Load**](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |


















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




### function GetName 

```C++
inline virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_ANIMATIONS_NS::AnimationNoneState::GetName () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationState::GetName*](classSR__ANIMATIONS__NS_1_1AnimationState.md#function-getname)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationState.h`

