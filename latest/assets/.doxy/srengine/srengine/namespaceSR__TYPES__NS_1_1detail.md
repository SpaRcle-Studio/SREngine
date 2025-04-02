

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
| class | [**dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1dynamic__array.md) &lt;typename ValueType, typename AllocatorType, typename SizeType, typename DiffType&gt;<br> |
| class | [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) &lt;typename MyType, MySize, typename MyAlloc&gt;<br> |
| class | [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &lt;typename MyType, MySize&gt;<br> |
| class | [**native\_float\_parts**](classSR__TYPES__NS_1_1detail_1_1native__float__parts.md) &lt;typename FloatingPointType&gt;<br> |
| struct | [**uint\_type\_helper**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper.md) &lt;BitCount, typename EnableType&gt;<br> |
| struct | [**uint\_type\_helper&lt; BitCount, std::enable\_if\_t&lt;(BitCount &gt;=static\_cast&lt; size\_t &gt;(UINT8\_C(17))) &&(BitCount&lt;=static\_cast&lt; size\_t &gt;(UINT8\_C(32)))&gt; &gt;**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper_3_01BitCount_00_01std_1_1enable__if__t_3_07B63fb5b46f0a854a3fab1d24dd63c093c.md) &lt;BitCount&gt;<br> |
| struct | [**uint\_type\_helper&lt; BitCount, std::enable\_if\_t&lt;(BitCount &gt;=static\_cast&lt; size\_t &gt;(UINT8\_C(33))) &&(BitCount&lt;=static\_cast&lt; size\_t &gt;(UINT8\_C(64)))&gt; &gt;**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper_3_01BitCount_00_01std_1_1enable__if__t_3_07B7a78e65e0b63e6416c6fcf49f479b0b2.md) &lt;BitCount&gt;<br> |
| struct | [**uint\_type\_helper&lt; BitCount, std::enable\_if\_t&lt;(BitCount &gt;=static\_cast&lt; size\_t &gt;(UINT8\_C(9))) &&(BitCount&lt;=static\_cast&lt; size\_t &gt;(UINT8\_C(16)))&gt; &gt;**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper_3_01BitCount_00_01std_1_1enable__if__t_3_07B9690eca38ad16b6a63c1a5996945ca18.md) &lt;BitCount&gt;<br> |
| struct | [**uint\_type\_helper&lt; BitCount, std::enable\_if\_t&lt;(BitCount&lt;=static\_cast&lt; size\_t &gt;(UINT8\_C(8)))&gt; &gt;**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper_3_01BitCount_00_01std_1_1enable__if__t_3_07Bf7e46a28771bbe653b06d7e6f6aa2491.md) &lt;BitCount&gt;<br> |
| struct | [**verify\_power\_of\_two**](structSR__TYPES__NS_1_1detail_1_1verify__power__of__two.md) &lt;Width2&gt;<br> |
| struct | [**verify\_power\_of\_two\_times\_granularity\_one\_sixty\_fourth**](structSR__TYPES__NS_1_1detail_1_1verify__power__of__two__times__granularity__one__sixty__fourth.md) &lt;Width2&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::int32\_t | [**ptrdiff\_t**](#typedef-ptrdiff_t)  <br> |
| typedef typename [**uint\_type\_helper**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper.md)&lt; static\_cast&lt; size\_t &gt;(std::numeric\_limits&lt; ptrdiff\_t &gt;::digits+1)&gt;::fast\_signed\_type | [**signed\_fast\_type**](#typedef-signed_fast_type)  <br> |
| typedef std::uint32\_t | [**size\_t**](#typedef-size_t)  <br> |
| typedef typename [**uint\_type\_helper**](structSR__TYPES__NS_1_1detail_1_1uint__type__helper.md)&lt; static\_cast&lt; size\_t &gt;(std::numeric\_limits&lt; size\_t &gt;::digits+0)&gt;::fast\_unsigned\_type | [**unsigned\_fast\_type**](#typedef-unsigned_fast_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  ArithmeticType | [**abs\_unsafe**](#function-abs_unsafe) (ArithmeticType val) <br> |
|  InputIterator | [**advance\_and\_point**](#function-advance_and_point) (InputIterator it, IntegralType n) <br> |
|  bool | [**binary\_search\_unsafe**](#function-binary_search_unsafe) (ForwardIt first, ForwardIt last, const T & value) <br> |
|  std::enable\_if\_t&lt;((std::is\_integral&lt; UnsignedIntegralType &gt;::value) &&(std::is\_unsigned&lt; UnsignedIntegralType &gt;::value)), unsigned &gt; | [**clz\_unsafe**](#function-clz_unsafe) (UnsignedIntegralType v) noexcept<br> |
|  DestinationIterator | [**copy\_backward\_unsafe**](#function-copy_backward_unsafe) (InputIterator first, InputIterator last, DestinationIterator dest) <br> |
|  DestinationIterator | [**copy\_unsafe**](#function-copy_unsafe) (InputIterator first, InputIterator last, DestinationIterator dest) <br> |
|  std::enable\_if\_t&lt;((std::is\_integral&lt; UnsignedIntegralType &gt;::value) &&(std::is\_unsigned&lt; UnsignedIntegralType &gt;::value)), unsigned &gt; | [**ctz\_unsafe**](#function-ctz_unsafe) (const UnsignedIntegralType v) noexcept<br> |
|  typename [**iterator\_detail::iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md)&lt; It &gt;::difference\_type | [**distance\_unsafe**](#function-distance_unsafe) (It first, It last) <br> |
|  bool | [**equal\_unsafe**](#function-equal_unsafe) (InputIt1 first1, InputIt1 last1, InputIt2 first2) <br> |
|  void | [**fill\_unsafe**](#function-fill_unsafe) (DestinationIterator first, DestinationIterator last, ValueType val) <br> |
|  InputIt | [**find\_if\_unsafe**](#function-find_if_unsafe) (InputIt first, InputIt last, UnaryPredicate p) <br> |
|  std::enable\_if\_t&lt;((std::is\_integral&lt; UnsignedIntegralType &gt;::value) &&(std::is\_unsigned&lt; UnsignedIntegralType &gt;::value)), UnsignedIntegralType &gt; | [**gcd\_unsafe**](#function-gcd_unsafe) (UnsignedIntegralType u, UnsignedIntegralType v) <br> |
|  OutputIterator | [**import\_export\_helper**](#function-import_export_helper) (ForwardIterator in, OutputIterator out, const signed\_fast\_type total\_bits\_to\_use, const unsigned\_fast\_type chunk\_size\_in, const unsigned\_fast\_type chunk\_size\_out) <br> |
|  UnsignedShortType | [**integer\_gcd\_reduce**](#function-integer_gcd_reduce) (UnsignedShortType u, UnsignedShortType v) <br> |
|  void | [**iter\_swap\_unsafe**](#function-iter_swap_unsafe) (IteratorType a, IteratorType b) <br> |
|  IntegerType | [**lcm\_impl**](#function-lcm_impl) (const IntegerType & a, const IntegerType & b) <br> |
|  bool | [**lexicographical\_compare\_unsafe**](#function-lexicographical_compare_unsafe) (InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) <br> |
|  ForwardIt | [**lower\_bound\_unsafe**](#function-lower_bound_unsafe) (ForwardIt first, ForwardIt last, const T & value) <br> |
|  unsigned\_fast\_type | [**lsb\_helper**](#function-lsb_helper) (const UnsignedIntegralType & u) <br> |
|  UnsignedShortType | [**make\_hi**](#function-make_hi) (const UnsignedLargeType & u) <br> |
|  UnsignedLargeType | [**make\_large**](#function-make_large) (const UnsignedShortType & lo, const UnsignedShortType & hi) <br> |
|  UnsignedShortType | [**make\_lo**](#function-make_lo) (const UnsignedLargeType & u) <br> |
|  ArithmeticType | [**max\_unsafe**](#function-max_unsafe) (const ArithmeticType & left, const ArithmeticType & right) <br> |
|  ArithmeticType | [**min\_unsafe**](#function-min_unsafe) (const ArithmeticType & left, const ArithmeticType & right) <br> |
|  unsigned\_fast\_type | [**msb\_helper**](#function-msb_helper) (const UnsignedIntegralType & u) <br> |
|  unsigned\_fast\_type | [**msb\_helper&lt; std::uint16\_t &gt;**](#function-msb_helper<-std::uint16_t->) (const std::uint16\_t & u) <br> |
|  unsigned\_fast\_type | [**msb\_helper&lt; std::uint16\_t &gt;**](#function-msb_helper<-std::uint16_t->) (const std::uint16\_t & u) <br> |
|  unsigned\_fast\_type | [**msb\_helper&lt; std::uint32\_t &gt;**](#function-msb_helper<-std::uint32_t->) (const std::uint32\_t & u) <br> |
|  unsigned\_fast\_type | [**msb\_helper&lt; std::uint32\_t &gt;**](#function-msb_helper<-std::uint32_t->) (const std::uint32\_t & u) <br> |
|  unsigned\_fast\_type | [**msb\_helper&lt; std::uint8\_t &gt;**](#function-msb_helper<-std::uint8_t->) (const std::uint8\_t & u) <br> |
|  unsigned\_fast\_type | [**msb\_helper&lt; std::uint8\_t &gt;**](#function-msb_helper<-std::uint8_t->) (const std::uint8\_t & u) <br> |
|  std::enable\_if\_t&lt;(std::is\_integral&lt; UnsignedIntegralType &gt;::value &&std::is\_unsigned&lt; UnsignedIntegralType &gt;::value), UnsignedIntegralType &gt; | [**negate**](#function-negate) (UnsignedIntegralType u) <br> |
|  std::enable\_if\_t&lt;(std::is\_integral&lt; SignedIntegralType &gt;::value &&std::is\_signed&lt; SignedIntegralType &gt;::value), SignedIntegralType &gt; | [**negate**](#function-negate) (SignedIntegralType n) <br> |
|  DestinationIterator | [**strcpy\_unsafe**](#function-strcpy_unsafe) (DestinationIterator dst, SourceIterator src) <br> |
|  unsigned\_fast\_type | [**strlen\_unsafe**](#function-strlen_unsafe) (const char \* p\_str) <br> |
|  ForwardIt2 | [**swap\_ranges\_unsafe**](#function-swap_ranges_unsafe) (ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2) <br> |
|  void | [**swap\_unsafe**](#function-swap_unsafe) (T & left, T & right) <br> |
|  void | [**swap\_unsafe**](#function-swap_unsafe) (T && left, T && right) <br> |




























## Public Types Documentation




### typedef ptrdiff\_t 

```C++
using SR_TYPES_NS::detail::ptrdiff_t =  std::int32_t;
```




<hr>



### typedef signed\_fast\_type 

```C++
using SR_TYPES_NS::detail::signed_fast_type =  typename uint_type_helper<static_cast<size_t>(std::numeric_limits<ptrdiff_t>::digits + 1)>::fast_signed_type;
```




<hr>



### typedef size\_t 

```C++
using SR_TYPES_NS::detail::size_t =  std::uint32_t;
```




<hr>



### typedef unsigned\_fast\_type 

```C++
using SR_TYPES_NS::detail::unsigned_fast_type =  typename uint_type_helper<static_cast<size_t>(std::numeric_limits<size_t   >::digits + 0)>::fast_unsigned_type;
```




<hr>
## Public Functions Documentation




### function abs\_unsafe 

```C++
template<typename ArithmeticType>
ArithmeticType SR_TYPES_NS::detail::abs_unsafe (
    ArithmeticType val
) 
```




<hr>



### function advance\_and\_point 

```C++
template<typename InputIterator, typename IntegralType>
InputIterator SR_TYPES_NS::detail::advance_and_point (
    InputIterator it,
    IntegralType n
) 
```




<hr>



### function binary\_search\_unsafe 

```C++
template<class ForwardIt, class T>
bool SR_TYPES_NS::detail::binary_search_unsafe (
    ForwardIt first,
    ForwardIt last,
    const T & value
) 
```




<hr>



### function clz\_unsafe 

```C++
template<class UnsignedIntegralType>
std::enable_if_t<((std::is_integral< UnsignedIntegralType >::value) &&(std::is_unsigned< UnsignedIntegralType >::value)), unsigned > SR_TYPES_NS::detail::clz_unsafe (
    UnsignedIntegralType v
) noexcept
```




<hr>



### function copy\_backward\_unsafe 

```C++
template<typename InputIterator, typename DestinationIterator>
DestinationIterator SR_TYPES_NS::detail::copy_backward_unsafe (
    InputIterator first,
    InputIterator last,
    DestinationIterator dest
) 
```




<hr>



### function copy\_unsafe 

```C++
template<typename InputIterator, typename DestinationIterator>
DestinationIterator SR_TYPES_NS::detail::copy_unsafe (
    InputIterator first,
    InputIterator last,
    DestinationIterator dest
) 
```




<hr>



### function ctz\_unsafe 

```C++
template<typename UnsignedIntegralType>
std::enable_if_t<((std::is_integral< UnsignedIntegralType >::value) &&(std::is_unsigned< UnsignedIntegralType >::value)), unsigned > SR_TYPES_NS::detail::ctz_unsafe (
    const UnsignedIntegralType v
) noexcept
```




<hr>



### function distance\_unsafe 

```C++
template<class It>
typename iterator_detail::iterator_traits < It >::difference_type SR_TYPES_NS::detail::distance_unsafe (
    It first,
    It last
) 
```




<hr>



### function equal\_unsafe 

```C++
template<class InputIt1, class InputIt2>
bool SR_TYPES_NS::detail::equal_unsafe (
    InputIt1 first1,
    InputIt1 last1,
    InputIt2 first2
) 
```




<hr>



### function fill\_unsafe 

```C++
template<typename DestinationIterator, typename ValueType>
void SR_TYPES_NS::detail::fill_unsafe (
    DestinationIterator first,
    DestinationIterator last,
    ValueType val
) 
```




<hr>



### function find\_if\_unsafe 

```C++
template<typename InputIt, typename UnaryPredicate>
InputIt SR_TYPES_NS::detail::find_if_unsafe (
    InputIt first,
    InputIt last,
    UnaryPredicate p
) 
```




<hr>



### function gcd\_unsafe 

```C++
template<typename UnsignedIntegralType>
std::enable_if_t<((std::is_integral< UnsignedIntegralType >::value) &&(std::is_unsigned< UnsignedIntegralType >::value)), UnsignedIntegralType > SR_TYPES_NS::detail::gcd_unsafe (
    UnsignedIntegralType u,
    UnsignedIntegralType v
) 
```




<hr>



### function import\_export\_helper 

```C++
template<typename ForwardIterator, typename OutputIterator>
OutputIterator SR_TYPES_NS::detail::import_export_helper (
    ForwardIterator in,
    OutputIterator out,
    const signed_fast_type total_bits_to_use,
    const unsigned_fast_type chunk_size_in,
    const unsigned_fast_type chunk_size_out
) 
```




<hr>



### function integer\_gcd\_reduce 

```C++
template<typename UnsignedShortType>
UnsignedShortType SR_TYPES_NS::detail::integer_gcd_reduce (
    UnsignedShortType u,
    UnsignedShortType v
) 
```




<hr>



### function iter\_swap\_unsafe 

```C++
template<typename IteratorType>
void SR_TYPES_NS::detail::iter_swap_unsafe (
    IteratorType a,
    IteratorType b
) 
```




<hr>



### function lcm\_impl 

```C++
template<typename IntegerType>
IntegerType SR_TYPES_NS::detail::lcm_impl (
    const IntegerType & a,
    const IntegerType & b
) 
```




<hr>



### function lexicographical\_compare\_unsafe 

```C++
template<class InputIt1, class InputIt2>
bool SR_TYPES_NS::detail::lexicographical_compare_unsafe (
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
ForwardIt SR_TYPES_NS::detail::lower_bound_unsafe (
    ForwardIt first,
    ForwardIt last,
    const T & value
) 
```




<hr>



### function lsb\_helper 

```C++
template<typename UnsignedIntegralType>
unsigned_fast_type SR_TYPES_NS::detail::lsb_helper (
    const UnsignedIntegralType & u
) 
```




<hr>



### function make\_hi 

```C++
template<typename UnsignedShortType, typename UnsignedLargeType>
UnsignedShortType SR_TYPES_NS::detail::make_hi (
    const UnsignedLargeType & u
) 
```




<hr>



### function make\_large 

```C++
template<typename UnsignedShortType, typename UnsignedLargeType>
UnsignedLargeType SR_TYPES_NS::detail::make_large (
    const UnsignedShortType & lo,
    const UnsignedShortType & hi
) 
```




<hr>



### function make\_lo 

```C++
template<typename UnsignedShortType, typename UnsignedLargeType>
UnsignedShortType SR_TYPES_NS::detail::make_lo (
    const UnsignedLargeType & u
) 
```




<hr>



### function max\_unsafe 

```C++
template<typename ArithmeticType>
ArithmeticType SR_TYPES_NS::detail::max_unsafe (
    const ArithmeticType & left,
    const ArithmeticType & right
) 
```




<hr>



### function min\_unsafe 

```C++
template<typename ArithmeticType>
ArithmeticType SR_TYPES_NS::detail::min_unsafe (
    const ArithmeticType & left,
    const ArithmeticType & right
) 
```




<hr>



### function msb\_helper 

```C++
template<typename UnsignedIntegralType>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper (
    const UnsignedIntegralType & u
) 
```




<hr>



### function msb\_helper&lt; std::uint16\_t &gt; 

```C++
template<>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper< std::uint16_t > (
    const std::uint16_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint16\_t &gt; 

```C++
template<>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper< std::uint16_t > (
    const std::uint16_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint32\_t &gt; 

```C++
template<>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper< std::uint32_t > (
    const std::uint32_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint32\_t &gt; 

```C++
template<>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper< std::uint32_t > (
    const std::uint32_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint8\_t &gt; 

```C++
template<>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper< std::uint8_t > (
    const std::uint8_t & u
) 
```




<hr>



### function msb\_helper&lt; std::uint8\_t &gt; 

```C++
template<>
unsigned_fast_type SR_TYPES_NS::detail::msb_helper< std::uint8_t > (
    const std::uint8_t & u
) 
```




<hr>



### function negate 

```C++
template<typename UnsignedIntegralType>
std::enable_if_t<(std::is_integral< UnsignedIntegralType >::value &&std::is_unsigned< UnsignedIntegralType >::value), UnsignedIntegralType > SR_TYPES_NS::detail::negate (
    UnsignedIntegralType u
) 
```




<hr>



### function negate 

```C++
template<typename SignedIntegralType>
std::enable_if_t<(std::is_integral< SignedIntegralType >::value &&std::is_signed< SignedIntegralType >::value), SignedIntegralType > SR_TYPES_NS::detail::negate (
    SignedIntegralType n
) 
```




<hr>



### function strcpy\_unsafe 

```C++
template<typename DestinationIterator, typename SourceIterator>
DestinationIterator SR_TYPES_NS::detail::strcpy_unsafe (
    DestinationIterator dst,
    SourceIterator src
) 
```




<hr>



### function strlen\_unsafe 

```C++
unsigned_fast_type SR_TYPES_NS::detail::strlen_unsafe (
    const char * p_str
) 
```




<hr>



### function swap\_ranges\_unsafe 

```C++
template<class ForwardIt1, class ForwardIt2>
ForwardIt2 SR_TYPES_NS::detail::swap_ranges_unsafe (
    ForwardIt1 first1,
    ForwardIt1 last1,
    ForwardIt2 first2
) 
```




<hr>



### function swap\_unsafe 

```C++
template<typename T>
void SR_TYPES_NS::detail::swap_unsafe (
    T & left,
    T & right
) 
```




<hr>



### function swap\_unsafe 

```C++
template<typename T>
void SR_TYPES_NS::detail::swap_unsafe (
    T && left,
    T && right
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

