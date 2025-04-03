

# Struct SR\_UTILS\_NS::GetFirstOfTypeFromSequence&lt; T, Pair &gt;

**template &lt;class T, class Pair&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**GetFirstOfTypeFromSequence&lt; T, Pair &gt;**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequence_3_01T_00_01Pair_01_4.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE constexpr auto | [**value**](#variable-value)   = `std::conditional\_t&lt;std::is\_same\_v&lt;T, typename Pair::type&gt;, Pair, [**GetFirstOfTypeFromSequenceAssert**](structSR__UTILS__NS_1_1GetFirstOfTypeFromSequenceAssert.md)&lt;T&gt;&gt;::value`<br> |










































## Public Static Attributes Documentation




### variable value 

```C++
SR_INLINE constexpr auto SR_UTILS_NS::GetFirstOfTypeFromSequence< T, Pair >::value;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/TypeTraits.h`

