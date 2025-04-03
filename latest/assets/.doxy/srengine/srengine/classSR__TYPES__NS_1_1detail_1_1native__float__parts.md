

# Class SR\_TYPES\_NS::detail::native\_float\_parts

**template &lt;typename FloatingPointType&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**get\_exponent**](#function-get_exponent) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**get\_mantissa**](#function-get_mantissa) () const<br> |
|  constexpr | [**native\_float\_parts**](#function-native_float_parts-14) () = delete<br> |
|  constexpr | [**native\_float\_parts**](#function-native_float_parts-24) (const FloatingPointType f) <br> |
|  constexpr | [**native\_float\_parts**](#function-native_float_parts-34) (const [**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) & other) <br> |
|  constexpr | [**native\_float\_parts**](#function-native_float_parts-44) ([**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) && other) noexcept<br> |
|  constexpr auto | [**operator=**](#function-operator) (const [**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) & other) noexcept<br> |
|  constexpr auto | [**operator=**](#function-operator_1) ([**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) && other) noexcept<br> |
|   | [**~native\_float\_parts**](#function-native_float_parts) () = default<br> |




























## Public Functions Documentation




### function get\_exponent 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::native_float_parts::get_exponent () const
```




<hr>



### function get\_mantissa 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::native_float_parts::get_mantissa () const
```




<hr>



### function native\_float\_parts [1/4]

```C++
constexpr SR_TYPES_NS::detail::native_float_parts::native_float_parts () = delete
```




<hr>



### function native\_float\_parts [2/4]

```C++
inline explicit constexpr SR_TYPES_NS::detail::native_float_parts::native_float_parts (
    const FloatingPointType f
) 
```




<hr>



### function native\_float\_parts [3/4]

```C++
inline constexpr SR_TYPES_NS::detail::native_float_parts::native_float_parts (
    const native_float_parts & other
) 
```




<hr>



### function native\_float\_parts [4/4]

```C++
inline constexpr SR_TYPES_NS::detail::native_float_parts::native_float_parts (
    native_float_parts && other
) noexcept
```




<hr>



### function operator= 

```C++
inline constexpr auto SR_TYPES_NS::detail::native_float_parts::operator= (
    const native_float_parts & other
) noexcept
```




<hr>



### function operator= 

```C++
inline constexpr auto SR_TYPES_NS::detail::native_float_parts::operator= (
    native_float_parts && other
) noexcept
```




<hr>



### function ~native\_float\_parts 

```C++
SR_TYPES_NS::detail::native_float_parts::~native_float_parts () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

