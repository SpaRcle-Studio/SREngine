

# Struct SR\_UTILS\_NS::Base64::FixedString

**template &lt;size\_t N&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Base64**](namespaceSR__UTILS__NS_1_1Base64.md) **>** [**FixedString**](structSR__UTILS__NS_1_1Base64_1_1FixedString.md)








Inherits the following classes: std::array< char, N >


































## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**FixedString**](#function-fixedstring-12) (const char(&) input) <br> |
|  constexpr | [**FixedString**](#function-fixedstring-22) (const char(&) input, std::index\_sequence&lt; Is... &gt;) <br> |




























## Public Functions Documentation




### function FixedString [1/2]

```C++
inline explicit constexpr SR_UTILS_NS::Base64::FixedString::FixedString (
    const char(&) input
) 
```




<hr>



### function FixedString [2/2]

```C++
template<size_t... Is>
inline constexpr SR_UTILS_NS::Base64::FixedString::FixedString (
    const char(&) input,
    std::index_sequence< Is... >
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/Base64.h`

