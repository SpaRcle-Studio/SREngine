

# Struct SR\_TYPES\_NS::uintwide\_t::digits\_ratio

**template &lt;typename UnknownBuiltInIntegralType&gt;**



[**ClassList**](annotated.md) **>** [**digits\_ratio**](structSR__TYPES__NS_1_1uintwide__t_1_1digits__ratio.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef UnknownBuiltInIntegralType | [**local\_unknown\_builtin\_integral\_type**](#typedef-local_unknown_builtin_integral_type)  <br> |
| typedef typename detail::uint\_type\_helper&lt; std::numeric\_limits&lt; local\_unknown\_builtin\_integral\_type &gt;::is\_signed ? static\_cast&lt; size\_t &gt;(std::numeric\_limits&lt; local\_unknown\_builtin\_integral\_type &gt;::digits+1) :static\_cast&lt; size\_t &gt;(std::numeric\_limits&lt; local\_unknown\_builtin\_integral\_type &gt;::digits+0)&gt;::exact\_unsigned\_type | [**local\_unsigned\_conversion\_type**](#typedef-local_unsigned_conversion_type)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr unsigned\_fast\_type | [**value**](#variable-value)   = `/* multi line expression */`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**extract**](#function-extract) (InputIteratorLeft p\_limb, unsigned\_fast\_type limb\_count) <br> |


























## Public Types Documentation




### typedef local\_unknown\_builtin\_integral\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::digits_ratio< UnknownBuiltInIntegralType >::local_unknown_builtin_integral_type =  UnknownBuiltInIntegralType;
```




<hr>



### typedef local\_unsigned\_conversion\_type 

```C++
using SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::digits_ratio< UnknownBuiltInIntegralType >::local_unsigned_conversion_type =  typename detail::uint_type_helper< std::numeric_limits<local_unknown_builtin_integral_type>::is_signed ? static_cast<size_t>(std::numeric_limits<local_unknown_builtin_integral_type>::digits + 1) : static_cast<size_t>(std::numeric_limits<local_unknown_builtin_integral_type>::digits + 0)>::exact_unsigned_type;
```




<hr>
## Public Static Attributes Documentation




### variable value 

```C++
constexpr unsigned_fast_type SR_TYPES_NS::uintwide_t< Width2, LimbType, AllocatorType, IsSigned >::digits_ratio< UnknownBuiltInIntegralType >::value;
```




<hr>
## Public Static Functions Documentation




### function extract 

```C++
template<typename InputIteratorLeft>
static inline constexpr auto digits_ratio::extract (
    InputIteratorLeft p_limb,
    unsigned_fast_type limb_count
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/UintWide_t.h`

