

# Class SR\_ANIMATIONS\_NS::AnimationStateConditionOr



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationStateConditionOr**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionOr.md)



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
|   | [**~AnimationStateConditionOr**](#function-animationstateconditionor) () override<br> |


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




## Public Static Functions inherited from SR_ANIMATIONS_NS::AnimationStateCondition

See [SR\_ANIMATIONS\_NS::AnimationStateCondition](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* | [**Load**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |
















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* &gt; | [**m\_conditions**](#variable-m_conditions)  <br> |




















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Detailed Description



 


    
## Public Functions Documentation




### function GetProgress 

```C++
virtual SR_NODISCARD std::optional< float_t > SR_ANIMATIONS_NS::AnimationStateConditionOr::GetProgress () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::GetProgress*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-getprogress)


<hr>



### function IsFinished 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionOr::IsFinished (
    const StateConditionContext & context
) noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsFinished*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isfinished)


<hr>



### function IsNeedBreakUpdate 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionOr::IsNeedBreakUpdate () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsNeedBreakUpdate*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isneedbreakupdate)


<hr>



### function IsSuitable 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionOr::IsSuitable (
    const StateConditionContext & context
) noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsSuitable*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-issuitable)


<hr>



### function Reset 

```C++
virtual void SR_ANIMATIONS_NS::AnimationStateConditionOr::Reset () override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::Reset*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-reset)


<hr>



### function ~AnimationStateConditionOr 

```C++
SR_ANIMATIONS_NS::AnimationStateConditionOr::~AnimationStateConditionOr () override
```




<hr>
## Protected Attributes Documentation




### variable m\_conditions 

```C++
std::vector<AnimationStateCondition*> SR_ANIMATIONS_NS::AnimationStateConditionOr::m_conditions;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationStateCondition.h`

