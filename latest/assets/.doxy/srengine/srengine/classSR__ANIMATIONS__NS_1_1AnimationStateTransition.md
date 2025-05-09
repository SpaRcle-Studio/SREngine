

# Class SR\_ANIMATIONS\_NS::AnimationStateTransition



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AnimationStateTransition**](#function-animationstatetransition-12) ([**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* pSource, [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* pDestination, [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* pCondition) <br> |
|   | [**AnimationStateTransition**](#function-animationstatetransition-22) ([**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* pSource, [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* pDestination) <br> |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**GetDestination**](#function-getdestination) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetProgress**](#function-getprogress) () noexcept const<br> |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**GetSource**](#function-getsource) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsActive**](#function-isactive) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFinished**](#function-isfinished) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsSuitable**](#function-issuitable) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept const<br> |
|  void | [**OnTransitionBegin**](#function-ontransitionbegin) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) <br> |
| virtual void | [**Reset**](#function-reset) () <br> |
| virtual void | [**Update**](#function-update) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) <br> |
|   | [**~AnimationStateTransition**](#function-animationstatetransition) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationStateTransition**](classSR__ANIMATIONS__NS_1_1AnimationStateTransition.md) \* | [**Load**](#function-load) ([**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* pSource, [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* pDestination, const SR\_XML\_NS::Node & nodeXml) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* | [**m\_condition**](#variable-m_condition)   = `nullptr`<br> |
|  [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**m\_destinationState**](#variable-m_destinationstate)   = `nullptr`<br> |
|  bool | [**m\_isActive**](#variable-m_isactive)   = `false`<br> |
|  [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**m\_sourceState**](#variable-m_sourcestate)   = `nullptr`<br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef Super 

```C++
using SR_ANIMATIONS_NS::AnimationStateTransition::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Functions Documentation




### function AnimationStateTransition [1/2]

```C++
SR_ANIMATIONS_NS::AnimationStateTransition::AnimationStateTransition (
    AnimationState * pSource,
    AnimationState * pDestination,
    AnimationStateCondition * pCondition
) 
```




<hr>



### function AnimationStateTransition [2/2]

```C++
SR_ANIMATIONS_NS::AnimationStateTransition::AnimationStateTransition (
    AnimationState * pSource,
    AnimationState * pDestination
) 
```




<hr>



### function GetDestination 

```C++
inline SR_NODISCARD AnimationState * SR_ANIMATIONS_NS::AnimationStateTransition::GetDestination () noexcept const
```




<hr>



### function GetProgress 

```C++
inline SR_NODISCARD float_t SR_ANIMATIONS_NS::AnimationStateTransition::GetProgress () noexcept const
```




<hr>



### function GetSource 

```C++
inline SR_NODISCARD AnimationState * SR_ANIMATIONS_NS::AnimationStateTransition::GetSource () noexcept const
```




<hr>



### function IsActive 

```C++
inline SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateTransition::IsActive () noexcept const
```




<hr>



### function IsFinished 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateTransition::IsFinished (
    const StateConditionContext & context
) noexcept const
```




<hr>



### function IsSuitable 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateTransition::IsSuitable (
    const StateConditionContext & context
) noexcept const
```




<hr>



### function OnTransitionBegin 

```C++
void SR_ANIMATIONS_NS::AnimationStateTransition::OnTransitionBegin (
    const StateConditionContext & context
) 
```




<hr>



### function Reset 

```C++
virtual void SR_ANIMATIONS_NS::AnimationStateTransition::Reset () 
```




<hr>



### function Update 

```C++
virtual void SR_ANIMATIONS_NS::AnimationStateTransition::Update (
    const StateConditionContext & context
) 
```




<hr>



### function ~AnimationStateTransition 

```C++
SR_ANIMATIONS_NS::AnimationStateTransition::~AnimationStateTransition () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationStateTransition * SR_ANIMATIONS_NS::AnimationStateTransition::Load (
    AnimationState * pSource,
    AnimationState * pDestination,
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_condition 

```C++
AnimationStateCondition* SR_ANIMATIONS_NS::AnimationStateTransition::m_condition;
```




<hr>



### variable m\_destinationState 

```C++
AnimationState* SR_ANIMATIONS_NS::AnimationStateTransition::m_destinationState;
```




<hr>



### variable m\_isActive 

```C++
bool SR_ANIMATIONS_NS::AnimationStateTransition::m_isActive;
```




<hr>



### variable m\_sourceState 

```C++
AnimationState* SR_ANIMATIONS_NS::AnimationStateTransition::m_sourceState;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationStateTransition.h`

