

# Struct SR\_ANIMATIONS\_NS::TranslationKey



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**TranslationKey**](structSR__ANIMATIONS__NS_1_1TranslationKey.md)



[More...](#detailed-description)

* `#include <AnimationKey.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**translation**](#variable-translation)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TranslationKey**](#function-translationkey-12) () = default<br> |
|   | [**TranslationKey**](#function-translationkey-22) (const SR\_MATH\_NS::FVector3 & translation) <br> |




























## Detailed Description


Задача ключа обеспечить необходимый переход из предыдущего ключа в этот в зависимости от интервала времени. Интервал времени задается от 0.f до 1.f в зависимости от положения перехода в момент времени. Переход должен работать и в обратную сторону (от 1.f до 0.f)
 


    
## Public Attributes Documentation




### variable translation 

```C++
SR_MATH_NS::FVector3 SR_ANIMATIONS_NS::TranslationKey::translation;
```




<hr>
## Public Functions Documentation




### function TranslationKey [1/2]

```C++
SR_ANIMATIONS_NS::TranslationKey::TranslationKey () = default
```




<hr>



### function TranslationKey [2/2]

```C++
inline explicit SR_ANIMATIONS_NS::TranslationKey::TranslationKey (
    const SR_MATH_NS::FVector3 & translation
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationKey.h`

