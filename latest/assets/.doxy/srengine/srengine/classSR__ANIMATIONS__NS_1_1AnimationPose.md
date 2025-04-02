

# Class SR\_ANIMATIONS\_NS::AnimationPose



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationPose**](classSR__ANIMATIONS__NS_1_1AnimationPose.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) & | [**GetGameObjectData**](#function-getgameobjectdata) (Index index) noexcept<br> |
|  SR\_NODISCARD std::vector&lt; [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md) &gt; & | [**GetGameObjects**](#function-getgameobjects) () noexcept<br> |
|  void | [**SetGameObjectsCount**](#function-setgameobjectscount) (uint32\_t count) <br> |
|   | [**~AnimationPose**](#function-animationpose) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function GetGameObjectData 

```C++
SR_NODISCARD AnimationGameObjectData & SR_ANIMATIONS_NS::AnimationPose::GetGameObjectData (
    Index index
) noexcept
```




<hr>



### function GetGameObjects 

```C++
inline SR_NODISCARD std::vector< AnimationGameObjectData > & SR_ANIMATIONS_NS::AnimationPose::GetGameObjects () noexcept
```




<hr>



### function SetGameObjectsCount 

```C++
void SR_ANIMATIONS_NS::AnimationPose::SetGameObjectsCount (
    uint32_t count
) 
```




<hr>



### function ~AnimationPose 

```C++
SR_ANIMATIONS_NS::AnimationPose::~AnimationPose () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationPose.h`

