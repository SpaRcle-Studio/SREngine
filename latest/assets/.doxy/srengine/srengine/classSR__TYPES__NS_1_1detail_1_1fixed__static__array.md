

# Class SR\_TYPES\_NS::detail::fixed\_static\_array

**template &lt;typename MyType, const size\_t MySize&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md)








Inherits the following classes: SR_TYPES_NS::detail::array_detail::array< MyType, static_cast< std::size_t >(MySize)>














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**allocator\_dummy\_unsafe**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md) | [**allocator\_type**](#typedef-allocator_type)  <br> |
| typedef size\_t | [**size\_type**](#typedef-size_type)  <br> |
| typedef typename base\_class\_type::value\_type | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-15) () = default<br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-25) (const size\_type size\_in, const value\_type & value\_in=value\_type(), [**allocator\_type**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md) alloc\_in=[**allocator\_type**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md)()) <br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-35) (const [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &) = default<br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-45) ([**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &&) noexcept<br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-55) (std::initializer\_list&lt; typename base\_class\_type::value\_type &gt; lst) <br> |
|  constexpr auto | [**operator=**](#function-operator) (const [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) & other\_array) <br> |
|  constexpr auto | [**operator=**](#function-operator_1) ([**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) && other\_array) noexcept<br> |
|  constexpr auto | [**operator[]**](#function-operator_2) (const size\_type i) <br> |
|  constexpr auto | [**operator[]**](#function-operator_3) (const size\_type i) const<br> |
|   | [**~fixed\_static\_array**](#function-fixed_static_array) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**static\_size**](#function-static_size) () <br> |


























## Public Types Documentation




### typedef allocator\_type 

```C++
using SR_TYPES_NS::detail::fixed_static_array< MyType, MySize >::allocator_type =  allocator_dummy_unsafe;
```




<hr>



### typedef size\_type 

```C++
using SR_TYPES_NS::detail::fixed_static_array< MyType, MySize >::size_type =  size_t;
```




<hr>



### typedef value\_type 

```C++
using SR_TYPES_NS::detail::fixed_static_array< MyType, MySize >::value_type =  typename base_class_type::value_type;
```




<hr>
## Public Functions Documentation




### function fixed\_static\_array [1/5]

```C++
constexpr SR_TYPES_NS::detail::fixed_static_array::fixed_static_array () = default
```




<hr>



### function fixed\_static\_array [2/5]

```C++
inline explicit constexpr SR_TYPES_NS::detail::fixed_static_array::fixed_static_array (
    const size_type size_in,
    const value_type & value_in=value_type(),
    allocator_type alloc_in=allocator_type ()
) 
```




<hr>



### function fixed\_static\_array [3/5]

```C++
constexpr SR_TYPES_NS::detail::fixed_static_array::fixed_static_array (
    const fixed_static_array &
) = default
```




<hr>



### function fixed\_static\_array [4/5]

```C++
constexpr SR_TYPES_NS::detail::fixed_static_array::fixed_static_array (
    fixed_static_array &&
) noexcept
```




<hr>



### function fixed\_static\_array [5/5]

```C++
inline constexpr SR_TYPES_NS::detail::fixed_static_array::fixed_static_array (
    std::initializer_list< typename base_class_type::value_type > lst
) 
```




<hr>



### function operator= 

```C++
constexpr auto SR_TYPES_NS::detail::fixed_static_array::operator= (
    const fixed_static_array & other_array
) 
```




<hr>



### function operator= 

```C++
constexpr auto SR_TYPES_NS::detail::fixed_static_array::operator= (
    fixed_static_array && other_array
) noexcept
```




<hr>



### function operator[] 

```C++
inline constexpr auto SR_TYPES_NS::detail::fixed_static_array::operator[] (
    const size_type i
) 
```




<hr>



### function operator[] 

```C++
inline constexpr auto SR_TYPES_NS::detail::fixed_static_array::operator[] (
    const size_type i
) const
```




<hr>



### function ~fixed\_static\_array 

```C++
SR_TYPES_NS::detail::fixed_static_array::~fixed_static_array () = default
```




<hr>
## Public Static Functions Documentation




### function static\_size 

```C++
static inline constexpr auto SR_TYPES_NS::detail::fixed_static_array::static_size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/UintWide_t.h`

