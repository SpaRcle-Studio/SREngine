

# Class SR\_TYPES\_NS::uintwide\_t

**template &lt;const size\_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned&gt;**



[**ClassList**](annotated.md) **>** [**uintwide\_t**](classSR__TYPES__NS_1_1uintwide__t.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename representation\_type::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br> |
| typedef typename representation\_type::const\_reverse\_iterator | [**const\_reverse\_iterator**](#typedef-const_reverse_iterator)  <br> |
| typedef typename detail::uint\_type\_helper&lt; static\_cast&lt; size\_t &gt;(static\_cast&lt; int &gt;(std::numeric\_limits&lt; limb\_type &gt;::digits \*static\_cast&lt; int &gt;(INT8\_C(2))))&gt;::exact\_unsigned\_type | [**double\_limb\_type**](#typedef-double_limb_type)  <br> |
| typedef uintwide\_t&lt; static\_cast&lt; size\_t &gt;(Width2 \*static\_cast&lt; size\_t &gt;(UINT8\_C(2))), limb\_type, AllocatorType, IsSigned &gt; | [**double\_width\_type**](#typedef-double_width_type)  <br> |
| typedef typename representation\_type::iterator | [**iterator**](#typedef-iterator)  <br> |
| typedef LimbType | [**limb\_type**](#typedef-limb_type)  <br> |
| typedef std::conditional\_t&lt; std::is\_same&lt; AllocatorType, void &gt;::value, [**detail::fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md)&lt; limb\_type, number\_of\_limbs &gt;, [**detail::fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md)&lt; limb\_type, number\_of\_limbs, typename std::allocator\_traits&lt; std::conditional\_t&lt; std::is\_same&lt; AllocatorType, void &gt;::value, std::allocator&lt; void &gt;, AllocatorType &gt; &gt;::template rebind\_alloc&lt; limb\_type &gt; &gt; &gt; | [**representation\_type**](#typedef-representation_type)  <br> |
| typedef typename representation\_type::reverse\_iterator | [**reverse\_iterator**](#typedef-reverse_iterator)  <br> |
| typedef double\_limb\_type | [**ularge\_type**](#typedef-ularge_type)  <br> |
| typedef limb\_type | [**ushort\_type**](#typedef-ushort_type)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr size\_t | [**my\_width2**](#variable-my_width2)   = `Width2`<br> |
|  constexpr size\_t | [**number\_of\_limbs**](#variable-number_of_limbs)   = `/* multi line expression */`<br> |
|  constexpr size\_t | [**number\_of\_limbs\_karatsuba\_threshold**](#variable-number_of_limbs_karatsuba_threshold)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**compare**](#function-compare-12) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, RePhraseIsSigned &gt; & other) const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**compare**](#function-compare-12) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, RePhraseIsSigned &gt; & other) const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**crepresentation**](#function-crepresentation) () const<br> |
|  constexpr auto | [**eval\_divide\_by\_single\_limb**](#function-eval_divide_by_single_limb) (const limb\_type short\_denominator, const unsigned\_fast\_type u\_offset, uintwide\_t \* remainder) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**is\_zero**](#function-is_zero) () const<br> |
|  constexpr auto | [**mul\_by\_limb**](#function-mul_by_limb) (const limb\_type v) <br> |
|  constexpr auto | [**negate**](#function-negate) () <br> |
|  constexpr | [**operator IntegralType**](#function-operator-integraltype) () const<br> |
|  constexpr | [**operator bool**](#function-operator-bool) () const<br> |
|  constexpr | [**operator double**](#function-operator-double) () const<br> |
|  constexpr | [**operator float**](#function-operator-float) () const<br> |
|  constexpr | [**operator long double**](#function-operator-long-double) () const<br> |
|  constexpr | [**operator uintwide\_t&lt; OtherWidth2, LimbType, AllocatorType, OtherIsSigned &gt;**](#function-operator-uintwide_t-otherwidth2-limbtype-allocatortype-otherissigned) () const<br> |
|  constexpr auto | [**operator!=**](#function-operator) (const uintwide\_t & other) const<br> |
|  constexpr auto | [**operator%=**](#function-operator_1) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator&=**](#function-operator_2) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator\*=**](#function-operator_3) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator+**](#function-operator_4) () const<br> |
|  constexpr auto | [**operator++**](#function-operator_5) () <br> |
|  constexpr auto | [**operator++**](#function-operator_6) (int) <br> |
|  constexpr auto | [**operator+=**](#function-operator_7) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator-**](#function-operator-) () const<br> |
|  constexpr auto | [**operator--**](#function-operator-) () <br> |
|  constexpr auto | [**operator--**](#function-operator-_1) (int) <br> |
|  constexpr auto | [**operator-=**](#function-operator-_1) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator/=**](#function-operator_8) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator&lt;**](#function-operator_9) (const uintwide\_t & other) const<br> |
|  constexpr auto | [**operator&lt;&lt;=**](#function-operator_10) (const SignedIntegralType n) <br> |
|  constexpr auto | [**operator&lt;&lt;=**](#function-operator_11) (const UnsignedIntegralType n) <br> |
|  constexpr auto | [**operator&lt;=**](#function-operator_12) (const uintwide\_t & other) const<br> |
|  constexpr auto | [**operator=**](#function-operator_13) (const uintwide\_t &) <br> |
|  constexpr auto | [**operator=**](#function-operator_14) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, OtherIsSigned &gt; & other) <br> |
|  constexpr auto | [**operator=**](#function-operator_15) (uintwide\_t && other) noexcept<br> |
|  constexpr auto | [**operator=**](#function-operator_16) (uintwide\_t&lt; Width2, LimbType, AllocatorType, OtherIsSigned &gt; && other) <br> |
|  constexpr auto | [**operator=**](#function-operator_17) (const std::string & estr) <br> |
|  constexpr auto | [**operator==**](#function-operator_18) (const uintwide\_t & other) const<br> |
|  constexpr auto | [**operator&gt;**](#function-operator_19) (const uintwide\_t & other) const<br> |
|  constexpr auto | [**operator&gt;=**](#function-operator_20) (const uintwide\_t & other) const<br> |
|  constexpr auto | [**operator&gt;&gt;=**](#function-operator_21) (const SignedIntegralType n) <br> |
|  constexpr auto | [**operator&gt;&gt;=**](#function-operator_22) (const UnsignedIntegralType n) <br> |
|  constexpr auto | [**operator^=**](#function-operator_23) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator\|=**](#function-operator_24) (const uintwide\_t & other) <br> |
|  constexpr auto | [**operator~**](#function-operator_25) () <br> |
|  constexpr auto | [**representation**](#function-representation-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**representation**](#function-representation-22) () const<br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-215) () = default<br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-315) (const UnsignedIntegralType v, std::enable\_if\_t&lt;(std::is\_integral&lt; UnsignedIntegralType &gt;::value &&std::is\_unsigned&lt; UnsignedIntegralType &gt;::value &&(std::numeric\_limits&lt; UnsignedIntegralType &gt;::digits&lt;=std::numeric\_limits&lt; limb\_type &gt;::digits))&gt; \*=nullptr) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-415) (const UnsignedIntegralType v, std::enable\_if\_t&lt;(std::is\_integral&lt; UnsignedIntegralType &gt;::value &&std::is\_unsigned&lt; UnsignedIntegralType &gt;::value &&(std::numeric\_limits&lt; UnsignedIntegralType &gt;::digits &gt; std::numeric\_limits&lt; limb\_type &gt;::digits))&gt; \* p\_nullparam=nullptr) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-515) (const SignedIntegralType v, std::enable\_if\_t&lt;(std::is\_integral&lt; SignedIntegralType &gt;::value &&std::is\_signed&lt; SignedIntegralType &gt;::value)&gt; \* p\_nullparam=nullptr) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-615) (const FloatingPointType f) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-715) (const uintwide\_t & other) = default<br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-815) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, OtherIsSigned &gt; & other) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-915) (const uintwide\_t&lt; OtherWidth2, LimbType, AllocatorType, OtherIsSigned &gt; & v) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-915) (const uintwide\_t&lt; OtherWidth2, LimbType, AllocatorType, OtherIsSigned &gt; & v) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-1115) (const char \* str\_input) <br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-1215) (uintwide\_t &&) noexcept<br> |
|  constexpr | [**uintwide\_t**](#function-uintwide_t-1315) (uintwide\_t&lt; Width2, LimbType, AllocatorType, OtherIsSigned &gt; && other) <br> |
|  constexpr auto | [**wr\_string**](#function-wr_string) (OutputStrIterator str\_result, const std::uint\_fast8\_t base\_rep=static\_cast&lt; std::uint\_fast8\_t &gt;(UINT8\_C(0x10)), const bool show\_base=true, const bool show\_pos=false, const bool is\_uppercase=true, unsigned\_fast\_type field\_width=static\_cast&lt; unsigned\_fast\_type &gt;(UINT8\_C(0)), const char fill\_char\_str='0') const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**from\_rep**](#function-from_rep-12) (const representation\_type & other\_rep) <br> |
|  constexpr auto | [**from\_rep**](#function-from_rep-22) (representation\_type && other\_rep) noexcept<br> |
|  constexpr auto | [**is\_neg**](#function-is_neg-12) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, RePhraseIsSigned &gt; &, std::enable\_if\_t&lt;(!RePhraseIsSigned), int &gt; \*=nullptr) <br> |
|  constexpr auto | [**is\_neg**](#function-is_neg-22) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, RePhraseIsSigned &gt; & a, std::enable\_if\_t&lt; RePhraseIsSigned, int &gt; \* p\_nullparam=nullptr) <br> |
|  constexpr auto | [**is\_not\_fill\_char**](#function-is_not_fill_char) (char c) <br> |
|  constexpr auto | [**limits\_helper\_max**](#function-limits_helper_max-12) () <br> |
|  constexpr auto | [**limits\_helper\_max**](#function-limits_helper_max-22) () <br> |
|  constexpr auto | [**limits\_helper\_min**](#function-limits_helper_min-12) () <br> |
|  constexpr auto | [**limits\_helper\_min**](#function-limits_helper_min-22) () <br> |
|  constexpr auto | [**my\_fill\_char**](#function-my_fill_char) () <br> |
|  constexpr auto | [**wr\_string\_max\_buffer\_size\_dec**](#function-wr_string_max_buffer_size_dec) () <br> |
|  constexpr auto | [**wr\_string\_max\_buffer\_size\_hex**](#function-wr_string_max_buffer_size_hex) () <br> |
|  constexpr auto | [**wr\_string\_max\_buffer\_size\_oct**](#function-wr_string_max_buffer_size_oct) () <br> |


























## Public Types Documentation




### typedef const\_iterator 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::const_iterator =  typename representation_type::const_iterator;
```




<hr>



### typedef const\_reverse\_iterator 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::const_reverse_iterator =  typename representation_type::const_reverse_iterator;
```




<hr>



### typedef double\_limb\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::double_limb_type =  typename detail::uint_type_helper<static_cast<size_t>(static_cast<int>(std::numeric_limits<limb_type>::digits* static_cast<int>(INT8_C(2))))>::exact_unsigned_type;
```




<hr>



### typedef double\_width\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::double_width_type =  uintwide_t<static_cast<size_t>(Width2* static_cast<size_t>(UINT8_C(2))), limb_type, AllocatorType, IsSigned>;
```




<hr>



### typedef iterator 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::iterator =  typename representation_type::iterator;
```




<hr>



### typedef limb\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::limb_type =  LimbType;
```




<hr>



### typedef representation\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::representation_type =  std::conditional_t <std::is_same<AllocatorType, void>::value, detail::fixed_static_array <limb_type, number_of_limbs>, detail::fixed_dynamic_array<limb_type, number_of_limbs, typename std::allocator_traits<std::conditional_t<std::is_same<AllocatorType, void>::value, std::allocator<void>, AllocatorType> >::template rebind_alloc<limb_type> >>;
```




<hr>



### typedef reverse\_iterator 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::reverse_iterator =  typename representation_type::reverse_iterator;
```




<hr>



### typedef ularge\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::ularge_type =  double_limb_type;
```




<hr>



### typedef ushort\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::ushort_type =  limb_type;
```




<hr>
## Public Static Attributes Documentation




### variable my\_width2 

```C++
constexpr size_t SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::my_width2;
```




<hr>



### variable number\_of\_limbs 

```C++
constexpr size_t SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::number_of_limbs;
```




<hr>



### variable number\_of\_limbs\_karatsuba\_threshold 

```C++
constexpr size_t SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::number_of_limbs_karatsuba_threshold;
```




<hr>
## Public Functions Documentation




### function compare [1/2]

```C++
template<const bool RePhraseIsSigned, std::enable_if_t<(!RePhraseIsSigned)> const *>
inline WIDE_INTEGER_NODISCARD constexpr auto uintwide_t::compare (
    const uintwide_t< Width2, LimbType, AllocatorType, RePhraseIsSigned > & other
) const
```




<hr>



### function compare [1/2]

```C++
template<const bool RePhraseIsSigned, std::enable_if_t< RePhraseIsSigned > const *>
inline WIDE_INTEGER_NODISCARD constexpr auto uintwide_t::compare (
    const uintwide_t< Width2, LimbType, AllocatorType, RePhraseIsSigned > & other
) const
```




<hr>



### function crepresentation 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto uintwide_t::crepresentation () const
```




<hr>



### function eval\_divide\_by\_single\_limb 

```C++
inline constexpr auto uintwide_t::eval_divide_by_single_limb (
    const limb_type short_denominator,
    const unsigned_fast_type u_offset,
    uintwide_t * remainder
) 
```




<hr>



### function is\_zero 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto uintwide_t::is_zero () const
```




<hr>



### function mul\_by\_limb 

```C++
inline constexpr auto uintwide_t::mul_by_limb (
    const limb_type v
) 
```




<hr>



### function negate 

```C++
inline constexpr auto uintwide_t::negate () 
```




<hr>



### function operator IntegralType 

```C++
template<typename IntegralType, typename>
inline explicit constexpr uintwide_t::operator IntegralType () const
```




<hr>



### function operator bool 

```C++
inline explicit constexpr uintwide_t::operator bool () const
```




<hr>



### function operator double 

```C++
inline explicit constexpr uintwide_t::operator double () const
```




<hr>



### function operator float 

```C++
inline explicit constexpr uintwide_t::operator float () const
```




<hr>



### function operator long double 

```C++
inline explicit constexpr uintwide_t::operator long double () const
```




<hr>



### function operator uintwide\_t&lt; OtherWidth2, LimbType, AllocatorType, OtherIsSigned &gt; 

```C++
template<const size_t OtherWidth2, const bool OtherIsSigned>
inline constexpr uintwide_t::operator uintwide_t< OtherWidth2, LimbType, AllocatorType, OtherIsSigned > () const
```




<hr>



### function operator!= 

```C++
inline constexpr auto uintwide_t::operator!= (
    const uintwide_t & other
) const
```




<hr>



### function operator%= 

```C++
inline constexpr auto uintwide_t::operator%= (
    const uintwide_t & other
) 
```




<hr>



### function operator&= 

```C++
inline constexpr auto uintwide_t::operator&= (
    const uintwide_t & other
) 
```




<hr>



### function operator\*= 

```C++
inline constexpr auto uintwide_t::operator*= (
    const uintwide_t & other
) 
```




<hr>



### function operator+ 

```C++
inline constexpr auto uintwide_t::operator+ () const
```




<hr>



### function operator++ 

```C++
inline constexpr auto uintwide_t::operator++ () 
```




<hr>



### function operator++ 

```C++
inline constexpr auto uintwide_t::operator++ (
    int
) 
```




<hr>



### function operator+= 

```C++
inline constexpr auto uintwide_t::operator+= (
    const uintwide_t & other
) 
```




<hr>



### function operator- 

```C++
inline constexpr auto uintwide_t::operator- () const
```




<hr>



### function operator-- 

```C++
inline constexpr auto uintwide_t::operator-- () 
```




<hr>



### function operator-- 

```C++
inline constexpr auto uintwide_t::operator-- (
    int
) 
```




<hr>



### function operator-= 

```C++
inline constexpr auto uintwide_t::operator-= (
    const uintwide_t & other
) 
```




<hr>



### function operator/= 

```C++
inline constexpr auto uintwide_t::operator/= (
    const uintwide_t & other
) 
```




<hr>



### function operator&lt; 

```C++
inline constexpr auto uintwide_t::operator< (
    const uintwide_t & other
) const
```




<hr>



### function operator&lt;&lt;= 

```C++
template<typename SignedIntegralType>
inline constexpr auto uintwide_t::operator<<= (
    const SignedIntegralType n
) 
```




<hr>



### function operator&lt;&lt;= 

```C++
template<typename UnsignedIntegralType>
inline constexpr auto uintwide_t::operator<<= (
    const UnsignedIntegralType n
) 
```




<hr>



### function operator&lt;= 

```C++
inline constexpr auto uintwide_t::operator<= (
    const uintwide_t & other
) const
```




<hr>



### function operator= 

```C++
constexpr auto uintwide_t::operator= (
    const uintwide_t &
) 
```




<hr>



### function operator= 

```C++
template<const bool OtherIsSigned, std::enable_if_t<(OtherIsSigned !=IsSigned)> const *>
inline constexpr auto uintwide_t::operator= (
    const uintwide_t< Width2, LimbType, AllocatorType, OtherIsSigned > & other
) 
```




<hr>



### function operator= 

```C++
constexpr auto uintwide_t::operator= (
    uintwide_t && other
) noexcept
```




<hr>



### function operator= 

```C++
template<const bool OtherIsSigned, std::enable_if_t<(IsSigned !=OtherIsSigned)> const *>
inline constexpr auto uintwide_t::operator= (
    uintwide_t< Width2, LimbType, AllocatorType, OtherIsSigned > && other
) 
```




<hr>



### function operator= 

```C++
inline constexpr auto uintwide_t::operator= (
    const std::string & estr
) 
```




<hr>



### function operator== 

```C++
inline constexpr auto uintwide_t::operator== (
    const uintwide_t & other
) const
```




<hr>



### function operator&gt; 

```C++
inline constexpr auto uintwide_t::operator> (
    const uintwide_t & other
) const
```




<hr>



### function operator&gt;= 

```C++
inline constexpr auto uintwide_t::operator>= (
    const uintwide_t & other
) const
```




<hr>



### function operator&gt;&gt;= 

```C++
template<typename SignedIntegralType>
inline constexpr auto uintwide_t::operator>>= (
    const SignedIntegralType n
) 
```




<hr>



### function operator&gt;&gt;= 

```C++
template<typename UnsignedIntegralType>
inline constexpr auto uintwide_t::operator>>= (
    const UnsignedIntegralType n
) 
```




<hr>



### function operator^= 

```C++
inline constexpr auto uintwide_t::operator^= (
    const uintwide_t & other
) 
```




<hr>



### function operator\|= 

```C++
inline constexpr auto uintwide_t::operator|= (
    const uintwide_t & other
) 
```




<hr>



### function operator~ 

```C++
inline constexpr auto uintwide_t::operator~ () 
```




<hr>



### function representation [1/2]

```C++
inline constexpr auto uintwide_t::representation () 
```




<hr>



### function representation [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto uintwide_t::representation () const
```




<hr>



### function uintwide\_t [2/15]

```C++
constexpr uintwide_t::uintwide_t () = default
```




<hr>



### function uintwide\_t [3/15]

```C++
template<typename UnsignedIntegralType>
inline constexpr uintwide_t::uintwide_t (
    const UnsignedIntegralType v,
    std::enable_if_t<(std::is_integral< UnsignedIntegralType >::value &&std::is_unsigned< UnsignedIntegralType >::value &&(std::numeric_limits< UnsignedIntegralType >::digits<=std::numeric_limits< limb_type >::digits))> *=nullptr
) 
```




<hr>



### function uintwide\_t [4/15]

```C++
template<typename UnsignedIntegralType>
inline constexpr uintwide_t::uintwide_t (
    const UnsignedIntegralType v,
    std::enable_if_t<(std::is_integral< UnsignedIntegralType >::value &&std::is_unsigned< UnsignedIntegralType >::value &&(std::numeric_limits< UnsignedIntegralType >::digits > std::numeric_limits< limb_type >::digits))> * p_nullparam=nullptr
) 
```




<hr>



### function uintwide\_t [5/15]

```C++
template<typename SignedIntegralType>
inline constexpr uintwide_t::uintwide_t (
    const SignedIntegralType v,
    std::enable_if_t<(std::is_integral< SignedIntegralType >::value &&std::is_signed< SignedIntegralType >::value)> * p_nullparam=nullptr
) 
```




<hr>



### function uintwide\_t [6/15]

```C++
template<typename FloatingPointType, std::enable_if_t<(std::is_floating_point< FloatingPointType >::value)> const *>
inline constexpr uintwide_t::uintwide_t (
    const FloatingPointType f
) 
```




<hr>



### function uintwide\_t [7/15]

```C++
constexpr uintwide_t::uintwide_t (
    const uintwide_t & other
) = default
```




<hr>



### function uintwide\_t [8/15]

```C++
template<const bool OtherIsSigned, std::enable_if_t<(OtherIsSigned !=IsSigned)> const *>
inline constexpr uintwide_t::uintwide_t (
    const uintwide_t< Width2, LimbType, AllocatorType, OtherIsSigned > & other
) 
```




<hr>



### function uintwide\_t [9/15]

```C++
template<const size_t OtherWidth2, const bool OtherIsSigned, std::enable_if_t<(Width2< OtherWidth2)> const *>
inline explicit constexpr uintwide_t::uintwide_t (
    const uintwide_t< OtherWidth2, LimbType, AllocatorType, OtherIsSigned > & v
) 
```




<hr>



### function uintwide\_t [9/15]

```C++
template<const size_t OtherWidth2, const bool OtherIsSigned, std::enable_if_t<(Width2 > OtherWidth2)> const *>
inline explicit constexpr uintwide_t::uintwide_t (
    const uintwide_t< OtherWidth2, LimbType, AllocatorType, OtherIsSigned > & v
) 
```




<hr>



### function uintwide\_t [11/15]

```C++
inline constexpr uintwide_t::uintwide_t (
    const char * str_input
) 
```




<hr>



### function uintwide\_t [12/15]

```C++
constexpr uintwide_t::uintwide_t (
    uintwide_t &&
) noexcept
```




<hr>



### function uintwide\_t [13/15]

```C++
template<const bool OtherIsSigned, std::enable_if_t<(IsSigned !=OtherIsSigned)> const *>
inline constexpr uintwide_t::uintwide_t (
    uintwide_t< Width2, LimbType, AllocatorType, OtherIsSigned > && other
) 
```




<hr>



### function wr\_string 

```C++
template<typename OutputStrIterator>
inline constexpr auto uintwide_t::wr_string (
    OutputStrIterator str_result,
    const std::uint_fast8_t base_rep=static_cast< std::uint_fast8_t >(UINT8_C(0x10)),
    const bool show_base=true,
    const bool show_pos=false,
    const bool is_uppercase=true,
    unsigned_fast_type field_width=static_cast< unsigned_fast_type >(UINT8_C(0)),
    const char fill_char_str='0'
) const
```




<hr>
## Public Static Functions Documentation




### function from\_rep [1/2]

```C++
static inline constexpr auto uintwide_t::from_rep (
    const representation_type & other_rep
) 
```




<hr>



### function from\_rep [2/2]

```C++
static inline constexpr auto uintwide_t::from_rep (
    representation_type && other_rep
) noexcept
```




<hr>



### function is\_neg [1/2]

```C++
template<const bool RePhraseIsSigned>
static inline constexpr auto uintwide_t::is_neg (
    const uintwide_t< Width2, LimbType, AllocatorType, RePhraseIsSigned > &,
    std::enable_if_t<(!RePhraseIsSigned), int > *=nullptr
) 
```




<hr>



### function is\_neg [2/2]

```C++
template<const bool RePhraseIsSigned>
static inline constexpr auto uintwide_t::is_neg (
    const uintwide_t< Width2, LimbType, AllocatorType, RePhraseIsSigned > & a,
    std::enable_if_t< RePhraseIsSigned, int > * p_nullparam=nullptr
) 
```




<hr>



### function is\_not\_fill\_char 

```C++
static inline constexpr auto uintwide_t::is_not_fill_char (
    char c
) 
```




<hr>



### function limits\_helper\_max [1/2]

```C++
template<const bool OtherIsSigned>
static inline constexpr auto uintwide_t::limits_helper_max () 
```




<hr>



### function limits\_helper\_max [2/2]

```C++
template<const bool OtherIsSigned>
static inline constexpr auto uintwide_t::limits_helper_max () 
```




<hr>



### function limits\_helper\_min [1/2]

```C++
template<const bool OtherIsSigned>
static inline constexpr auto uintwide_t::limits_helper_min () 
```




<hr>



### function limits\_helper\_min [2/2]

```C++
template<const bool OtherIsSigned>
static inline constexpr auto uintwide_t::limits_helper_min () 
```




<hr>



### function my\_fill\_char 

```C++
static inline constexpr auto uintwide_t::my_fill_char () 
```




<hr>



### function wr\_string\_max\_buffer\_size\_dec 

```C++
static inline constexpr auto uintwide_t::wr_string_max_buffer_size_dec () 
```




<hr>



### function wr\_string\_max\_buffer\_size\_hex 

```C++
static inline constexpr auto uintwide_t::wr_string_max_buffer_size_hex () 
```




<hr>



### function wr\_string\_max\_buffer\_size\_oct 

```C++
static inline constexpr auto uintwide_t::wr_string_max_buffer_size_oct () 
```




<hr>## Friends Documentation





### friend uintwide\_t [1/15]

```C++
template<const size_t OtherWidth2, typename OtherLimbType, typename OtherAllocatorType, const bool OtherIsSigned>
class uintwide_t::uintwide_t (
    uintwide_t
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/UintWide_t.h`

