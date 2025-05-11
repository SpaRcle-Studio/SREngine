

# Namespace SR\_TYPES\_NS::detail



[**Namespace List**](namespaces.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**array\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1array__detail.md) <br> |
| namespace | [**distance\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1distance__detail.md) <br> |
| namespace | [**iterator\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1iterator__detail.md) <br> |
| namespace | [**my\_own**](namespaceSR__TYPES__NS_1_1detail_1_1my__own.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**allocator\_dummy\_unsafe**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md) <br> |
| class | [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) &lt;typename MyType, MySize, typename MyAlloc&gt;<br> |
| class | [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &lt;typename MyType, MySize&gt;<br> |
| class | [**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) &lt;typename FloatingPointType&gt;<br> |
| struct | [**verify\_power\_of\_two\_times\_granularity\_one\_sixty\_fourth**](structSR__TYPES__NS_1_1detail_1_1verify__power__of__two__times__granularity__one__sixty__fourth.md) &lt;Width2&gt;<br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**abs\_unsafe**](#function-abs_unsafe) (ArithmeticType val) <br> |
|  constexpr auto | [**advance\_and\_point**](#function-advance_and_point) (InputIterator it, IntegralType n) <br> |
|  constexpr auto | [**binary\_search\_unsafe**](#function-binary_search_unsafe) (ForwardIt first, ForwardIt last, const T & value) <br> |
|  constexpr auto | [**clz\_unsafe**](#function-clz_unsafe) (UnsignedIntegralType v) noexcept<br> |
|  constexpr auto | [**copy\_backward\_unsafe**](#function-copy_backward_unsafe) (InputIterator first, InputIterator last, DestinationIterator dest) <br> |
|  constexpr auto | [**copy\_unsafe**](#function-copy_unsafe) (InputIterator first, InputIterator last, DestinationIterator dest) <br> |
|  constexpr auto | [**ctz\_unsafe**](#function-ctz_unsafe) (const UnsignedIntegralType v) noexcept<br> |
|  constexpr auto | [**distance\_unsafe**](#function-distance_unsafe) (It first, It last) <br> |
|  constexpr auto | [**equal\_unsafe**](#function-equal_unsafe) (InputIt1 first1, InputIt1 last1, InputIt2 first2) <br> |
|  constexpr auto | [**fill\_unsafe**](#function-fill_unsafe) (DestinationIterator first, DestinationIterator last, ValueType val) <br> |
|  constexpr auto | [**find\_if\_unsafe**](#function-find_if_unsafe) (InputIt first, InputIt last, UnaryPredicate p) <br> |
|  constexpr auto | [**gcd\_unsafe**](#function-gcd_unsafe) (UnsignedIntegralType u, UnsignedIntegralType v) <br> |
|  constexpr auto | [**integer\_gcd\_reduce**](#function-integer_gcd_reduce) (UnsignedShortType u, UnsignedShortType v) <br> |
|  constexpr auto | [**iter\_swap\_unsafe**](#function-iter_swap_unsafe) (IteratorType a, IteratorType b) <br> |
|  constexpr auto | [**lcm\_impl**](#function-lcm_impl) (const IntegerType & a, const IntegerType & b) <br> |
|  constexpr auto | [**lexicographical\_compare\_unsafe**](#function-lexicographical_compare_unsafe) (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) <br> |
|  constexpr auto | [**lower\_bound\_unsafe**](#function-lower_bound_unsafe) (ForwardIt first, ForwardIt last, const T & value) <br> |
|  constexpr auto | [**lsb\_helper**](#function-lsb_helper) (const UnsignedIntegralType & u) <br> |
|  constexpr auto | [**make\_hi**](#function-make_hi) (const UnsignedLargeType & u) <br> |
|  constexpr auto | [**make\_large**](#function-make_large) (const UnsignedShortType & lo, const UnsignedShortType & hi) <br> |
|  constexpr auto | [**make\_lo**](#function-make_lo) (const UnsignedLargeType & u) <br> |
|  constexpr auto | [**max\_unsafe**](#function-max_unsafe) (const ArithmeticType & left, const ArithmeticType & right) <br> |
|  constexpr auto | [**min\_unsafe**](#function-min_unsafe) (const ArithmeticType & left, const ArithmeticType & right) <br> |
|  constexpr auto | [**msb\_helper**](#function-msb_helper) (const UnsignedIntegralType & u) <br> |
|  constexpr auto | [**msb\_helper&lt; std::uint16\_t &gt;**](#function-msb_helper<-std::uint16_t->) (const std::uint16\_t & u) <br> |
|  constexpr auto | [**msb\_helper&lt; std::uint16\_t &gt;**](#function-msb_helper<-std::uint16_t->) (const std::uint16\_t & u) <br> |
|  constexpr auto | [**msb\_helper&lt; std::uint32\_t &gt;**](#function-msb_helper<-std::uint32_t->) (const std::uint32\_t & u) <br> |
|  constexpr auto | [**msb\_helper&lt; std::uint32\_t &gt;**](#function-msb_helper<-std::uint32_t->) (const std::uint32\_t & u) <br> |
|  constexpr auto | [**msb\_helper&lt; std::uint8\_t &gt;**](#function-msb_helper<-std::uint8_t->) (const std::uint8\_t & u) <br> |
|  constexpr auto | [**msb\_helper&lt; std::uint8\_t &gt;**](#function-msb_helper<-std::uint8_t->) (const std::uint8\_t & u) <br> |
|  constexpr auto | [**negate**](#function-negate) (UnsignedIntegralType u) <br> |
|  constexpr auto | [**negate**](#function-negate) (SignedIntegralType n) <br> |
|  constexpr auto | [**strcpy\_unsafe**](#function-strcpy_unsafe) (DestinationIterator dst, SourceIterator src) <br> |
|  constexpr auto | [**strlen\_unsafe**](#function-strlen_unsafe) (const char \* p\_str) <br> |
|  constexpr auto | [**swap\_ranges\_unsafe**](#function-swap_ranges_unsafe) (ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) <br> |
|  constexpr auto | [**swap\_unsafe**](#function-swap_unsafe) (T & left, T & right) <br> |
|  constexpr auto | [**swap\_unsafe**](#function-swap_unsafe) (T && left, T && right) <br> |




























## Public Functions Documentation




### function abs\_unsafe 

```C++
template<typename ArithmeticType>
constexpr auto SR_TYPES_NS::detail::abs_unsafe (
    ArithmeticType val
) 
```




<hr>



### function advance\_and\_point 

```C++
template<typename InputIterator, typename IntegralType>
constexpr auto SR_TYPES_NS::detail::advance_and_point (
    InputIterator it,
    IntegralType n
) 
```




<hr>



### function binary\_search\_unsafe 

```C++
template<class ForwardIt, class T>
constexpr auto SR_TYPES_NS::detail::binary_search_unsafe (
    ForwardIt first,
    ForwardIt last,
    const T & value
) 
```




<hr>



### function clz\_unsafe 

```C++
template<class UnsignedIntegralType>
constexpr auto SR_TYPES_NS::detail::clz_unsafe (
    UnsignedIntegralType v
) noexcept
```




<hr>



### function copy\_backward\_unsafe 

```C++
template<typename InputIterator, typename DestinationIterator>
constexpr auto SR_TYPES_NS::detail::copy_backward_unsafe (
    InputIterator first,
    InputIterator last,
    DestinationIterator dest
) 
```




<hr>



### function copy\_unsafe 

```C++
template<typename InputIterator, typename DestinationIterator>
constexpr auto SR_TYPES_NS::detail::copy_unsafe (
    InputIterator first,
    InputIterator last,
    DestinationIterator dest
) 
```




<hr>



### function ctz\_unsafe 

```C++
template<typename UnsignedIntegralType>
constexpr auto SR_TYPES_NS::detail::ctz_unsafe (
    const UnsignedIntegralType v
) noexcept
```




<hr>



### function distance\_unsafe 

```C++
template<class It>
constexpr auto SR_TYPES_NS::detail::distance_unsafe (
    It first,
    It last
) 
```




<hr>



### function equal\_unsafe 

```C++
template<class InputIt1, class InputIt2>
constexpr auto SR_TYPES_NS::detail::equal_unsafe (
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2
) 
```




<hr>



### function fill\_unsafe 

```C++
template<typename DestinationIterator, typename ValueType>
constexpr auto SR_TYPES_NS::detail::fill_unsafe (
    DestinationIterator first,
    DestinationIterator last,
    ValueType val
) 
```




<hr>



### function find\_if\_unsafe 

```C++
template<typename InputIt, typename UnaryPredicate>
constexpr auto SR_TYPES_NS::detail::find_if_unsafe (
    InputIt first,
    InputIt last,
    UnaryPredicate p
) 
```




<hr>



### function gcd\_unsafe 

```C++
template<typename UnsignedIntegralType>
constexpr auto SR_TYPES_NS::detail::gcd_unsafe (
    UnsignedIntegralType u,
    UnsignedIntegralType v
) 
```




<hr>



### function integer\_gcd\_reduce 

```C++
template<typename UnsignedShortType>
constexpr auto SR_TYPES_NS::detail::integer_gcd_reduce (
    UnsignedShortType u,
    UnsignedShortType v
) 
```




<hr>



### function iter\_swap\_unsafe 

```C++
template<typename IteratorType>
constexpr auto SR_TYPES_NS::detail::iter_swap_unsafe (
    IteratorType a,
    IteratorType b
) 
```




<hr>



### function lcm\_impl 

```C++
template<typename IntegerType>
constexpr auto SR_TYPES_NS::detail::lcm_impl (
    const IntegerType & a,
    const IntegerType & b
) 
```




<hr>



### function lexicographical\_compare\_unsafe 

```C++
template<class InputIt1, class InputIt2>
constexpr auto SR_TYPES_NS::detail::lexicographical_compare_unsafe (
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2,
    InputIt2 last2
) 
```




<hr>



### function lower\_bound\_unsafe 

```C++
template<typename ForwardIt, typename T>
constexpr auto SR_TYPES_NS::detail::lower_bound_unsafe (
    ForwardIt first,
    ForwardIt last,
    const T & value
) 
```




<hr>



### function lsb\_helper 

```C++
template<typename UnsignedIntegralType>
constexpr auto SR_TYPES_NS::detail::lsb_helper (
    const UnsignedIntegralType & u
) 
```




<hr>



### function make\_hi 

```C++
template<typename UnsignedShortType, typename UnsignedLargeType>
constexpr auto SR_TYPES_NS::detail::make_hi (
    const UnsignedLargeType & u
) 
```




<hr>



### function make\_large 

```C++
template<typename UnsignedShortType, typename UnsignedLargeType>
constexpr auto SR_TYPES_NS::detail::make_large (
    const UnsignedShortType & lo,
    const UnsignedShortType & hi
) 
```




<hr>



### function make\_lo 

```C++
template<typename UnsignedShortType, typename UnsignedLargeType>
constexpr auto SR_TYPES_NS::detail::make_lo (
    const UnsignedLargeType & u
) 
```




<hr>



### function max\_unsafe 

```C++
template<typename ArithmeticType>
constexpr auto SR_TYPES_NS::detail::max_unsafe (
    const ArithmeticType & left,
    const ArithmeticType & right
) 
```




<hr>



### function min\_unsafe 

```C++
template<typename ArithmeticType>
constexpr auto SR_TYPES_NS::detail::min_unsafe (
    const ArithmeticType & left,
    const ArithmeticType & right
) 
```




<hr>



### function msb\_helper 

```C++
template<typename UnsignedIntegralType>
constexpr auto SR_TYPES_NS::detail::msb_helper (
    const UnsignedIntegralType & u
) 
```




<hr>



### function msb\_helper&lt; std::uint16\_t &gt; 

```C++
template<>
constexpr auto SR_TYPES_NS::detail::msb_helper< std::uint16_t > (
    const std::uint16_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint16\_t &gt; 

```C++
template<>
constexpr auto SR_TYPES_NS::detail::msb_helper< std::uint16_t > (
    const std::uint16_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint32\_t &gt; 

```C++
template<>
constexpr auto SR_TYPES_NS::detail::msb_helper< std::uint32_t > (
    const std::uint32_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint32\_t &gt; 

```C++
template<>
constexpr auto SR_TYPES_NS::detail::msb_helper< std::uint32_t > (
    const std::uint32_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint8\_t &gt; 

```C++
template<>
constexpr auto SR_TYPES_NS::detail::msb_helper< std::uint8_t > (
    const std::uint8_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint8\_t &gt; 

```C++
template<>
constexpr auto SR_TYPES_NS::detail::msb_helper< std::uint8_t > (
    const std::uint8_t & u
) 
```




<hr>



### function negate 

```C++
template<typename UnsignedIntegralType>
constexpr auto SR_TYPES_NS::detail::negate (
    UnsignedIntegralType u
) 
```




<hr>



### function negate 

```C++
template<typename SignedIntegralType>
constexpr auto SR_TYPES_NS::detail::negate (
    SignedIntegralType n
) 
```




<hr>



### function strcpy\_unsafe 

```C++
template<typename DestinationIterator, typename SourceIterator>
constexpr auto SR_TYPES_NS::detail::strcpy_unsafe (
    DestinationIterator dst,
    SourceIterator src
) 
```




<hr>



### function strlen\_unsafe 

```C++
constexpr auto SR_TYPES_NS::detail::strlen_unsafe (
    const char * p_str
) 
```




<hr>



### function swap\_ranges\_unsafe 

```C++
template<class ForwardIt1, class ForwardIt2>
constexpr auto SR_TYPES_NS::detail::swap_ranges_unsafe (
    ForwardIt1 first1,
    ForwardIt1 last1,
    ForwardIt2 first2
) 
```




<hr>



### function swap\_unsafe 

```C++
template<typename T>
constexpr auto SR_TYPES_NS::detail::swap_unsafe (
    T & left,
    T & right
) 
```




<hr>



### function swap\_unsafe 

```C++
template<typename T>
constexpr auto SR_TYPES_NS::detail::swap_unsafe (
    T && left,
    T && right
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/UintWide_t.h`

