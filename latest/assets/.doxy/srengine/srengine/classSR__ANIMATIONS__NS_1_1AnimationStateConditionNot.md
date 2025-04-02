

# Class SR\_ANIMATIONS\_NS::AnimationStateConditionNot



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationStateConditionNot**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionNot.md)



[More...](#detailed-description)

* `#include <AnimationStateCondition.h>`



Inherits the following classes: [SR\_ANIMATIONS\_NS::AnimationStateCondition](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetProgress**](#function-getprogress) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsFinished**](#function-isfinished) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedBreakUpdate**](#function-isneedbreakupdate) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsSuitable**](#function-issuitable) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept override const<br> |
| virtual void | [**Reset**](#function-reset) () override<br> |
| virtual void | [**Update**](#function-update) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) override<br> |
|   | [**~AnimationStateConditionNot**](#function-animationstateconditionnot) () override<br> |


## Public Functions inherited from SR_ANIMATIONS_NS::AnimationStateCondition

See [SR\_ANIMATIONS\_NS::AnimationStateCondition](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetProgress**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-getprogress) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFinished**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isfinished) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedBreakUpdate**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isneedbreakupdate) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsSuitable**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-issuitable) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept const = 0<br> |
| virtual void | [**Reset**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-reset) () <br> |
| virtual void | [**Update**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-update) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationStateConditionNot**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionNot.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |


## Public Static Functions inherited from SR_ANIMATIONS_NS::AnimationStateCondition

See [SR\_ANIMATIONS\_NS::AnimationStateCondition](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* | [**Load**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* | [**m\_condition**](#variable-m_condition)   = `nullptr`<br> |




















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Detailed Description



 


    
## Public Functions Documentation




### function GetProgress 

```C++
virtual SR_NODISCARD std::optional< float_t > SR_ANIMATIONS_NS::AnimationStateConditionNot::GetProgress () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::GetProgress*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-getprogress)


<hr>



### function IsFinished 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionNot::IsFinished (
    const StateConditionContext & context
) noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsFinished*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isfinished)


<hr>



### function IsNeedBreakUpdate 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionNot::IsNeedBreakUpdate () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsNeedBreakUpdate*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isneedbreakupdate)


<hr>



### function IsSuitable 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionNot::IsSuitable (
    const StateConditionContext & context
) noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsSuitable*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-issuitable)


<hr>



### function Reset 

```C++
virtual void SR_ANIMATIONS_NS::AnimationStateConditionNot::Reset () override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::Reset*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-reset)


<hr>



### function Update 

```C++
virtual void SR_ANIMATIONS_NS::AnimationStateConditionNot::Update (
    const StateConditionContext & context
) override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::Update*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-update)


<hr>



### function ~AnimationStateConditionNot 

```C++
SR_ANIMATIONS_NS::AnimationStateConditionNot::~AnimationStateConditionNot () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationStateConditionNot * SR_ANIMATIONS_NS::AnimationStateConditionNot::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_condition 

```C++
AnimationStateCondition* SR_ANIMATIONS_NS::AnimationStateConditionNot::m_condition;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationStateCondition.h`

