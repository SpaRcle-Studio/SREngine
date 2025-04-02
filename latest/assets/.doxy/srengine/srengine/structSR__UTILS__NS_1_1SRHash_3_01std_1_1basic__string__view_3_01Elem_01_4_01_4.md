

# Struct SR\_UTILS\_NS::SRHash&lt; std::basic\_string\_view&lt; Elem &gt; &gt;

**template &lt;class Elem&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRHash&lt; std::basic\_string\_view&lt; Elem &gt; &gt;**](structSR__UTILS__NS_1_1SRHash_3_01std_1_1basic__string__view_3_01Elem_01_4_01_4.md)








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
|  SR\_NODISCARD static constexpr size\_t | [**DoHash**](#function-dohash-12) (const std::basic\_string\_view&lt; Elem &gt; keyVal) noexcept<br> |
|  uint64\_t | [**DoHash**](#function-dohash-22) (const std::basic\_string\_view&lt; Elem &gt; & value) noexcept<br> |














































































## Public Static Functions Documentation




### function DoHash [1/2]

```C++
static inline SR_NODISCARD static constexpr size_t SR_UTILS_NS::SRHash< std::basic_string_view< Elem > >::DoHash (
    const std::basic_string_view< Elem > keyVal
) noexcept
```




<hr>



### function DoHash [2/2]

```C++
static inline uint64_t SR_UTILS_NS::SRHash< std::basic_string_view< Elem > >::DoHash (
    const std::basic_string_view< Elem > & value
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Hashes.h`

