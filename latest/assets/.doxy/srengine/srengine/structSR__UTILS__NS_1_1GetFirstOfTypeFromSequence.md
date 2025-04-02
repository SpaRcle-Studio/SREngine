

# Struct SR\_UTILS\_NS::GetFirstOfTypeFromSequence

**template &lt;class T, class Pair, class... Pairs&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**GetFirstOfTypeFromSequence**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequence.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE constexpr auto | [**value**](#variable-value)   = `std::conditional\_t&lt;std::is\_same\_v&lt;T, typename Pair::type&gt;, Pair, [**GetFirstOfTypeFromSequence**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequence.md)&lt;T, Pairs...&gt;&gt;::value`<br> |










































## Public Static Attributes Documentation




### variable value 

```C++
SR_INLINE constexpr auto SR_UTILS_NS::GetFirstOfTypeFromSequence< T, Pair, Pairs >::value;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/TypeTraits.h`

