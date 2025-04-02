

# Struct SR\_ANIMATIONS\_NS::UnionAnimationKey



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md)



[More...](#detailed-description)

* `#include <AnimationKey.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| union  | [**Data**](#union-data)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_ANIMATIONS\_NS::UnionAnimationKey::Data**](unionSR__ANIMATIONS__NS_1_1UnionAnimationKey_1_1Data.md) | [**data**](#variable-data)  <br> |
|  float\_t | [**time**](#variable-time)   = `0.f`<br> |
|  AnimationKeyType | [**type**](#variable-type)   = `AnimationKeyType::None`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**CopyFrom**](#function-copyfrom) (const [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & other) <br> |
|  void SR\_FASTCALL | [**Set**](#function-set-12) ([**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & animation) noexcept const<br> |
|  void SR\_FASTCALL | [**Set**](#function-set-22) ([**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & animation, float\_t toreance) noexcept const<br> |
|  void | [**SetData**](#function-setdata) (T data) <br> |
|  void SR\_FASTCALL | [**SetWithWeight**](#function-setwithweight) ([**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & animation, float\_t weight) noexcept const<br> |
|   | [**UnionAnimationKey**](#function-unionanimationkey-12) () = default<br> |
|   | [**UnionAnimationKey**](#function-unionanimationkey-22) (const [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & other) <br> |
|  void SR\_FASTCALL | [**Update**](#function-update-12) (float\_t progress, const [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & prevKey, [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & animation) noexcept const<br> |
|  void SR\_FASTCALL | [**Update**](#function-update-22) (float\_t progress, const [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & prevKey, [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & animation, float\_t toreance) noexcept const<br> |
|  void SR\_FASTCALL | [**UpdateWithWeight**](#function-updatewithweight) (float\_t progress, const [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & prevKey, [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & animation, float\_t weight) noexcept const<br> |
|  [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & | [**operator=**](#function-operator) (const [**UnionAnimationKey**](structSR__ANIMATIONS__NS_1_1UnionAnimationKey.md) & other) <br> |
|   | [**~UnionAnimationKey**](#function-unionanimationkey) () = default<br> |




























## Detailed Description



 


    
## Public Types Documentation




### union Data 

```C++

```




<hr>
## Public Attributes Documentation




### variable data 

```C++
union SR_ANIMATIONS_NS::UnionAnimationKey::Data SR_ANIMATIONS_NS::UnionAnimationKey::data;
```




<hr>



### variable time 

```C++
float_t SR_ANIMATIONS_NS::UnionAnimationKey::time;
```




<hr>



### variable type 

```C++
AnimationKeyType SR_ANIMATIONS_NS::UnionAnimationKey::type;
```




<hr>
## Public Functions Documentation




### function CopyFrom 

```C++
void SR_ANIMATIONS_NS::UnionAnimationKey::CopyFrom (
    const UnionAnimationKey & other
) 
```




<hr>



### function Set [1/2]

```C++
void SR_FASTCALL SR_ANIMATIONS_NS::UnionAnimationKey::Set (
    AnimationGameObjectData & animation
) noexcept const
```




<hr>



### function Set [2/2]

```C++
void SR_FASTCALL SR_ANIMATIONS_NS::UnionAnimationKey::Set (
    AnimationGameObjectData & animation,
    float_t toreance
) noexcept const
```




<hr>



### function SetData 

```C++
template<class T>
inline void SR_ANIMATIONS_NS::UnionAnimationKey::SetData (
    T data
) 
```




<hr>



### function SetWithWeight 

```C++
void SR_FASTCALL SR_ANIMATIONS_NS::UnionAnimationKey::SetWithWeight (
    AnimationGameObjectData & animation,
    float_t weight
) noexcept const
```




<hr>



### function UnionAnimationKey [1/2]

```C++
SR_ANIMATIONS_NS::UnionAnimationKey::UnionAnimationKey () = default
```




<hr>



### function UnionAnimationKey [2/2]

```C++
inline SR_ANIMATIONS_NS::UnionAnimationKey::UnionAnimationKey (
    const UnionAnimationKey & other
) 
```




<hr>



### function Update [1/2]

```C++
void SR_FASTCALL SR_ANIMATIONS_NS::UnionAnimationKey::Update (
    float_t progress,
    const UnionAnimationKey & prevKey,
    AnimationGameObjectData & animation
) noexcept const
```




<hr>



### function Update [2/2]

```C++
void SR_FASTCALL SR_ANIMATIONS_NS::UnionAnimationKey::Update (
    float_t progress,
    const UnionAnimationKey & prevKey,
    AnimationGameObjectData & animation,
    float_t toreance
) noexcept const
```




<hr>



### function UpdateWithWeight 

```C++
void SR_FASTCALL SR_ANIMATIONS_NS::UnionAnimationKey::UpdateWithWeight (
    float_t progress,
    const UnionAnimationKey & prevKey,
    AnimationGameObjectData & animation,
    float_t weight
) noexcept const
```




<hr>



### function operator= 

```C++
inline UnionAnimationKey & SR_ANIMATIONS_NS::UnionAnimationKey::operator= (
    const UnionAnimationKey & other
) 
```




<hr>



### function ~UnionAnimationKey 

```C++
SR_ANIMATIONS_NS::UnionAnimationKey::~UnionAnimationKey () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationKey.h`

