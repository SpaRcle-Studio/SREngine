

# Struct SR\_UTILS\_NS::SRHash&lt; std::basic\_string&lt; Elem, std::char\_traits&lt; Elem &gt;, Alloc &gt; &gt;

**template &lt;class Elem, class Alloc&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRHash&lt; std::basic\_string&lt; Elem, std::char\_traits&lt; Elem &gt;, Alloc &gt; &gt;**](structSR__UTILS__NS_1_1SRHash_3_01std_1_1basic__string_3_01Elem_00_01std_1_1char__traits_3_01Elem_01_4_00_01Alloc_01_4_01_4.md)








Inherits the following classes: [SR\_UTILS\_NS::SRConditionallyEnabledHash](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md),  [SR\_UTILS\_NS::SRConditionallyEnabledHash](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md)












































































## Public Functions inherited from SR_UTILS_NS::SRConditionallyEnabledHash

See [SR\_UTILS\_NS::SRConditionallyEnabledHash](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD constexpr size\_t | [**operator()**](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md#function-operator()) (const T & keyVal) const<br> |


## Public Functions inherited from SR_UTILS_NS::SRConditionallyEnabledHash

See [SR\_UTILS\_NS::SRConditionallyEnabledHash](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD constexpr size\_t | [**operator()**](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md#function-operator()) (const T & keyVal) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD static constexpr size\_t | [**DoHash**](#function-dohash-12) (const std::basic\_string&lt; Elem, std::char\_traits&lt; Elem &gt;, Alloc &gt; & keyVal) noexcept<br> |
|  uint64\_t | [**DoHash**](#function-dohash-22) (const std::basic\_string&lt; Elem, std::char\_traits&lt; Elem &gt;, Alloc &gt; & value) noexcept<br> |














































































## Public Static Functions Documentation




### function DoHash [1/2]

```C++
static inline SR_NODISCARD static constexpr size_t SR_UTILS_NS::SRHash< std::basic_string< Elem, std::char_traits< Elem >, Alloc > >::DoHash (
    const std::basic_string< Elem, std::char_traits< Elem >, Alloc > & keyVal
) noexcept
```




<hr>



### function DoHash [2/2]

```C++
static inline uint64_t SR_UTILS_NS::SRHash< std::basic_string< Elem, std::char_traits< Elem >, Alloc > >::DoHash (
    const std::basic_string< Elem, std::char_traits< Elem >, Alloc > & value
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Hashes.h`

