

# Class SR\_TYPES\_NS::detail::fixed\_dynamic\_array

**template &lt;typename MyType, const size\_t MySize, typename MyAlloc&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md)








Inherits the following classes: util::dynamic_array< MyType, MyAlloc, size_t, ptrdiff_t >


































## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-14) (const typename base\_class\_type::size\_type size\_in=MySize, const typename base\_class\_type::value\_type & value\_in=typename base\_class\_type::value\_type(), const typename base\_class\_type::allocator\_type & alloc\_in=typename base\_class\_type::allocator\_type()) <br> |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-24) (const [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) & other\_array) = default<br> |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-34) ([**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) && other\_array) noexcept<br> |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-44) (std::initializer\_list&lt; typename base\_class\_type::value\_type &gt; lst) <br> |
|  constexpr auto | [**operator=**](#function-operator) (const [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) & other\_array) <br> |
|  constexpr auto | [**operator=**](#function-operator_1) ([**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) && other\_array) noexcept<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**static\_size**](#function-static_size) () <br> |


























## Public Functions Documentation




### function fixed\_dynamic\_array [1/4]

```C++
inline explicit constexpr SR_TYPES_NS::detail::fixed_dynamic_array::fixed_dynamic_array (
    const typename base_class_type::size_type size_in=MySize,
    const typename base_class_type::value_type & value_in=typename base_class_type::value_type(),
    const typename base_class_type::allocator_type & alloc_in=typename base_class_type::allocator_type()
) 
```




<hr>



### function fixed\_dynamic\_array [2/4]

```C++
constexpr SR_TYPES_NS::detail::fixed_dynamic_array::fixed_dynamic_array (
    const fixed_dynamic_array & other_array
) = default
```




<hr>



### function fixed\_dynamic\_array [3/4]

```C++
constexpr SR_TYPES_NS::detail::fixed_dynamic_array::fixed_dynamic_array (
    fixed_dynamic_array && other_array
) noexcept
```




<hr>



### function fixed\_dynamic\_array [4/4]

```C++
inline constexpr SR_TYPES_NS::detail::fixed_dynamic_array::fixed_dynamic_array (
    std::initializer_list< typename base_class_type::value_type > lst
) 
```




<hr>



### function operator= 

```C++
constexpr auto SR_TYPES_NS::detail::fixed_dynamic_array::operator= (
    const fixed_dynamic_array & other_array
) 
```




<hr>



### function operator= 

```C++
constexpr auto SR_TYPES_NS::detail::fixed_dynamic_array::operator= (
    fixed_dynamic_array && other_array
) noexcept
```




<hr>
## Public Static Functions Documentation




### function static\_size 

```C++
static inline constexpr auto SR_TYPES_NS::detail::fixed_dynamic_array::static_size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/UintWide_t.h`

