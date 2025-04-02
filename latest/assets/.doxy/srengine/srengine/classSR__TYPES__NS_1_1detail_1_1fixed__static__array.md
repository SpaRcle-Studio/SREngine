

# Class SR\_TYPES\_NS::detail::fixed\_static\_array

**template &lt;typename MyType, const size\_t MySize&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md)








Inherits the following classes: [SR\_TYPES\_NS::detail::array\_detail::array](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**allocator\_dummy\_unsafe**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md) | [**allocator\_type**](#typedef-allocator_type)  <br> |
| typedef size\_t | [**size\_type**](#typedef-size_type)  <br> |
| typedef typename base\_class\_type::value\_type | [**value\_type**](#typedef-value_type)  <br> |


## Public Types inherited from SR_TYPES_NS::detail::array_detail::array

See [SR\_TYPES\_NS::detail::array\_detail::array](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)

| Type | Name |
| ---: | :--- |
| typedef const\_pointer | [**const\_iterator**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-const_iterator)  <br> |
| typedef const T \* | [**const\_pointer**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-const_pointer)  <br> |
| typedef const T & | [**const\_reference**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-const_reference)  <br> |
| typedef [**iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; const\_iterator &gt; | [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-const_reverse_iterator)  <br> |
| typedef std::ptrdiff\_t | [**difference\_type**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-difference_type)  <br> |
| typedef pointer | [**iterator**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-iterator)  <br> |
| typedef T \* | [**pointer**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-pointer)  <br> |
| typedef T & | [**reference**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-reference)  <br> |
| typedef [**iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator &gt; | [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-reverse_iterator)  <br> |
| typedef std::size\_t | [**size\_type**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-size_type)  <br> |
| typedef T | [**value\_type**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#typedef-value_type)  <br> |








## Public Attributes inherited from SR_TYPES_NS::detail::array_detail::array

See [SR\_TYPES\_NS::detail::array\_detail::array](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)

| Type | Name |
| ---: | :--- |
|  value\_type | [**elems**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#variable-elems)   = `{ }`<br> |




## Public Static Attributes inherited from SR_TYPES_NS::detail::array_detail::array

See [SR\_TYPES\_NS::detail::array\_detail::array](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)

| Type | Name |
| ---: | :--- |
|  size\_type | [**static\_size**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#variable-static_size)   = `N`<br> |


























## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-15) () = default<br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-25) (const size\_type size\_in, const value\_type & value\_in=value\_type(), [**allocator\_type**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md) alloc\_in=[**allocator\_type**](structSR__TYPES__NS_1_1detail_1_1allocator__dummy__unsafe.md)()) <br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-35) (const [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &) = default<br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-45) ([**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &&) noexcept<br> |
|  constexpr | [**fixed\_static\_array**](#function-fixed_static_array-55) (std::initializer\_list&lt; typename base\_class\_type::value\_type &gt; lst) <br> |
|  [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &=default | [**operator=**](#function-operator) (const [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) & other\_array) <br> |
|  [**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) &=default | [**operator=**](#function-operator_1) ([**fixed\_static\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__static__array.md) && other\_array) noexcept<br> |
|  typename base\_class\_type::reference | [**operator[]**](#function-operator_2) (const size\_type i) <br> |
|  typename base\_class\_type::const\_reference | [**operator[]**](#function-operator_3) (const size\_type i) const<br> |
|   | [**~fixed\_static\_array**](#function-fixed_static_array) () = default<br> |


## Public Functions inherited from SR_TYPES_NS::detail::array_detail::array

See [SR\_TYPES\_NS::detail::array\_detail::array](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)

| Type | Name |
| ---: | :--- |
|  void | [**assign**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-assign) (const value\_type & value) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**at**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-at-12) (const size\_type i) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**at**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-at-22) (const size\_type i) const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**back**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-back-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**back**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-back-22) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**begin**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-begin-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**begin**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-begin-22) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**c\_array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-c_array) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**cbegin**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-cbegin) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**cend**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-cend) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**crbegin**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-crbegin) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**crend**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-crend) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**data**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-data-12) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**data**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-data-22) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**end**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-end-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**end**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-end-22) () const<br> |
|  void | [**fill**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-fill) (const value\_type & value) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**front**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-front-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**front**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-front-22) () const<br> |
|  [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md) & | [**operator=**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-operator) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T2, N &gt; & y) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**operator[]**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-operator_1) (const size\_type i) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**operator[]**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-operator_2) (const size\_type i) const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rbegin**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-rbegin-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rbegin**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-rbegin-22) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rend**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-rend-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rend**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-rend-22) () const<br> |
|  void | [**swap**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-swap) ([**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T2, N &gt; & y) noexcept<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  size\_type | [**static\_size**](#function-static_size) () <br> |


## Public Static Functions inherited from SR_TYPES_NS::detail::array_detail::array

See [SR\_TYPES\_NS::detail::array\_detail::array](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**empty**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-empty) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**max\_size**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-max_size) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**size**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md#function-size) () <br> |


















































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
fixed_static_array &=default SR_TYPES_NS::detail::fixed_static_array::operator= (
    const fixed_static_array & other_array
) 
```




<hr>



### function operator= 

```C++
fixed_static_array &=default SR_TYPES_NS::detail::fixed_static_array::operator= (
    fixed_static_array && other_array
) noexcept
```




<hr>



### function operator[] 

```C++
inline typename base_class_type::reference SR_TYPES_NS::detail::fixed_static_array::operator[] (
    const size_type i
) 
```




<hr>



### function operator[] 

```C++
inline typename base_class_type::const_reference SR_TYPES_NS::detail::fixed_static_array::operator[] (
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
static inline size_type SR_TYPES_NS::detail::fixed_static_array::static_size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

