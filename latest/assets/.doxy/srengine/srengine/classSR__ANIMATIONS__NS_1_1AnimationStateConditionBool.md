

# Class SR\_ANIMATIONS\_NS::AnimationStateConditionBool



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationStateConditionBool**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionBool.md)



[More...](#detailed-description)

* `#include <AnimationStateCondition.h>`



Inherits the following classes: [SR\_ANIMATIONS\_NS::AnimationStateCondition](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsNeedBreakUpdate**](#function-isneedbreakupdate) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsSuitable**](#function-issuitable) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept override const<br> |
| virtual void | [**Reset**](#function-reset) () override<br> |
| virtual SR\_NODISCARD void | [**Update**](#function-update) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) override<br> |


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
|  SR\_NODISCARD [**AnimationStateConditionBool**](classSR__ANIMATIONS__NS_1_1AnimationStateConditionBool.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |


## Public Static Functions inherited from SR_ANIMATIONS_NS::AnimationStateCondition

See [SR\_ANIMATIONS\_NS::AnimationStateCondition](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* | [**Load**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |




































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Detailed Description




 


    
## Public Functions Documentation




### function IsNeedBreakUpdate 

```C++
inline virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionBool::IsNeedBreakUpdate () noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsNeedBreakUpdate*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-isneedbreakupdate)


<hr>



### function IsSuitable 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateConditionBool::IsSuitable (
    const StateConditionContext & context
) noexcept override const
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::IsSuitable*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-issuitable)


<hr>



### function Reset 

```C++
virtual void SR_ANIMATIONS_NS::AnimationStateConditionBool::Reset () override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::Reset*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-reset)


<hr>



### function Update 

```C++
virtual SR_NODISCARD void SR_ANIMATIONS_NS::AnimationStateConditionBool::Update (
    const StateConditionContext & context
) override
```



Implements [*SR\_ANIMATIONS\_NS::AnimationStateCondition::Update*](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md#function-update)


<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationStateConditionBool * SR_ANIMATIONS_NS::AnimationStateConditionBool::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationStateCondition.h`

