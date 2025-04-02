

# Struct SR\_ANIMATIONS\_NS::AnimationGameObjectData



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationGameObjectData**](structSR__ANIMATIONS__NS_1_1AnimationGameObjectData.md)



[More...](#detailed-description)

* `#include <AnimationData.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**dirty**](#variable-dirty)   = `false`<br> |
|  std::optional&lt; bool &gt; | [**enable**](#variable-enable)  <br> |
|  std::optional&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**layer**](#variable-layer)  <br> |
|  std::optional&lt; [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) &gt; | [**rotation**](#variable-rotation)  <br> |
|  std::optional&lt; SR\_MATH\_NS::FVector3 &gt; | [**scaling**](#variable-scaling)  <br> |
|  std::optional&lt; SR\_MATH\_NS::FVector3 &gt; | [**translation**](#variable-translation)  <br> |












































## Detailed Description


Ключи меняют данные в рамках одного объекта, смешивая значения После чего, в конце кадра данные применяются на объект 


    
## Public Attributes Documentation




### variable dirty 

```C++
bool SR_ANIMATIONS_NS::AnimationGameObjectData::dirty;
```




<hr>



### variable enable 

```C++
std::optional<bool> SR_ANIMATIONS_NS::AnimationGameObjectData::enable;
```




<hr>



### variable layer 

```C++
std::optional<SR_UTILS_NS::StringAtom> SR_ANIMATIONS_NS::AnimationGameObjectData::layer;
```




<hr>



### variable rotation 

```C++
std::optional<SR_MATH_NS::Quaternion> SR_ANIMATIONS_NS::AnimationGameObjectData::rotation;
```




<hr>



### variable scaling 

```C++
std::optional<SR_MATH_NS::FVector3> SR_ANIMATIONS_NS::AnimationGameObjectData::scaling;
```




<hr>



### variable translation 

```C++
std::optional<SR_MATH_NS::FVector3> SR_ANIMATIONS_NS::AnimationGameObjectData::translation;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationData.h`

