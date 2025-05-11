

# Class SR\_ANIMATIONS\_NS::AnimationStateCondition



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::AnimationStateConditionAnd](classSR__ANIMATIONS__NS_1_1AnimationStateConditionAnd.md),  [SR\_ANIMATIONS\_NS::AnimationStateConditionBool](classSR__ANIMATIONS__NS_1_1AnimationStateConditionBool.md),  [SR\_ANIMATIONS\_NS::AnimationStateConditionExitTime](classSR__ANIMATIONS__NS_1_1AnimationStateConditionExitTime.md),  [SR\_ANIMATIONS\_NS::AnimationStateConditionNot](classSR__ANIMATIONS__NS_1_1AnimationStateConditionNot.md),  [SR\_ANIMATIONS\_NS::AnimationStateConditionOr](classSR__ANIMATIONS__NS_1_1AnimationStateConditionOr.md),  [SR\_ANIMATIONS\_NS::AnimationStateConditionTrue](classSR__ANIMATIONS__NS_1_1AnimationStateConditionTrue.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetProgress**](#function-getprogress) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFinished**](#function-isfinished) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedBreakUpdate**](#function-isneedbreakupdate) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsSuitable**](#function-issuitable) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) noexcept const = 0<br> |
| virtual void | [**Reset**](#function-reset) () <br> |
| virtual void | [**Update**](#function-update) (const [**StateConditionContext**](structSR__ANIMATIONS__NS_1_1StateConditionContext.md) & context) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationStateCondition**](classSR__ANIMATIONS__NS_1_1AnimationStateCondition.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function GetProgress 

```C++
inline virtual SR_NODISCARD std::optional< float_t > SR_ANIMATIONS_NS::AnimationStateCondition::GetProgress () noexcept const
```




<hr>



### function IsFinished 

```C++
inline virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateCondition::IsFinished (
    const StateConditionContext & context
) noexcept const
```




<hr>



### function IsNeedBreakUpdate 

```C++
inline virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateCondition::IsNeedBreakUpdate () noexcept const
```




<hr>



### function IsSuitable 

```C++
virtual SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateCondition::IsSuitable (
    const StateConditionContext & context
) noexcept const = 0
```




<hr>



### function Reset 

```C++
inline virtual void SR_ANIMATIONS_NS::AnimationStateCondition::Reset () 
```




<hr>



### function Update 

```C++
inline virtual void SR_ANIMATIONS_NS::AnimationStateCondition::Update (
    const StateConditionContext & context
) 
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationStateCondition * SR_ANIMATIONS_NS::AnimationStateCondition::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationStateCondition.h`

