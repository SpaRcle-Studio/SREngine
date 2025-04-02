

# Class SR\_TYPES\_NS::detail::fixed\_dynamic\_array

**template &lt;typename MyType, const size\_t MySize, typename MyAlloc&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md)








Inherits the following classes: [util::dynamic\_array](classutil_1_1dynamic__array.md)
















## Public Types inherited from util::dynamic_array

See [util::dynamic\_array](classutil_1_1dynamic__array.md)

| Type | Name |
| ---: | :--- |
| typedef typename std::allocator\_traits&lt; AllocatorType &gt;::template rebind\_alloc&lt; ValueType &gt; | [**allocator\_type**](classutil_1_1dynamic__array.md#typedef-allocator_type)  <br> |
| typedef const value\_type \* | [**const\_iterator**](classutil_1_1dynamic__array.md#typedef-const_iterator)  <br> |
| typedef const value\_type \* | [**const\_pointer**](classutil_1_1dynamic__array.md#typedef-const_pointer)  <br> |
| typedef const value\_type & | [**const\_reference**](classutil_1_1dynamic__array.md#typedef-const_reference)  <br> |
| typedef [**SR\_TYPES\_NS::detail::iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; const value\_type \* &gt; | [**const\_reverse\_iterator**](classutil_1_1dynamic__array.md#typedef-const_reverse_iterator)  <br> |
| typedef DiffType | [**difference\_type**](classutil_1_1dynamic__array.md#typedef-difference_type)  <br> |
| typedef value\_type \* | [**iterator**](classutil_1_1dynamic__array.md#typedef-iterator)  <br> |
| typedef value\_type \* | [**pointer**](classutil_1_1dynamic__array.md#typedef-pointer)  <br> |
| typedef value\_type & | [**reference**](classutil_1_1dynamic__array.md#typedef-reference)  <br> |
| typedef [**SR\_TYPES\_NS::detail::iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; value\_type \* &gt; | [**reverse\_iterator**](classutil_1_1dynamic__array.md#typedef-reverse_iterator)  <br> |
| typedef SizeType | [**size\_type**](classutil_1_1dynamic__array.md#typedef-size_type)  <br> |
| typedef typename allocator\_type::value\_type | [**value\_type**](classutil_1_1dynamic__array.md#typedef-value_type)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-14) (const typename base\_class\_type::size\_type size\_in=MySize, const typename base\_class\_type::value\_type & value\_in=typename base\_class\_type::value\_type(), const typename base\_class\_type::allocator\_type & alloc\_in=typename base\_class\_type::allocator\_type()) <br> |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-24) (const [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) & other\_array) = default<br> |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-34) ([**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) && other\_array) noexcept<br> |
|  constexpr | [**fixed\_dynamic\_array**](#function-fixed_dynamic_array-44) (std::initializer\_list&lt; typename base\_class\_type::value\_type &gt; lst) <br> |
|  [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) &=default | [**operator=**](#function-operator) (const [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) & other\_array) <br> |
|  [**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) &=default | [**operator=**](#function-operator_1) ([**fixed\_dynamic\_array**](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md) && other\_array) noexcept<br> |


## Public Functions inherited from util::dynamic_array

See [util::dynamic\_array](classutil_1_1dynamic__array.md)

| Type | Name |
| ---: | :--- |
|  reference | [**at**](classutil_1_1dynamic__array.md#function-at-12) (const size\_type i) <br> |
|  const\_reference | [**at**](classutil_1_1dynamic__array.md#function-at-22) (const size\_type i) const<br> |
|  reference | [**back**](classutil_1_1dynamic__array.md#function-back-12) () <br> |
|  const\_reference | [**back**](classutil_1_1dynamic__array.md#function-back-22) () const<br> |
|  iterator | [**begin**](classutil_1_1dynamic__array.md#function-begin-12) () <br> |
|  const\_iterator | [**begin**](classutil_1_1dynamic__array.md#function-begin-22) () const<br> |
|  const\_iterator | [**cbegin**](classutil_1_1dynamic__array.md#function-cbegin) () const<br> |
|  const\_iterator | [**cend**](classutil_1_1dynamic__array.md#function-cend) () const<br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**crbegin**](classutil_1_1dynamic__array.md#function-crbegin) () const<br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**crend**](classutil_1_1dynamic__array.md#function-crend) () const<br> |
|  pointer | [**data**](classutil_1_1dynamic__array.md#function-data-12) () <br> |
|  const\_pointer | [**data**](classutil_1_1dynamic__array.md#function-data-22) () const<br> |
|  constexpr | [**dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array-16) () = delete<br> |
|  constexpr | [**dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array-26) (size\_type count\_in, const\_reference value\_in=value\_type(), const allocator\_type & alloc\_in=allocator\_type()) <br> |
|  constexpr | [**dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array-36) (const [**dynamic\_array**](classutil_1_1dynamic__array.md) & other) <br> |
|  constexpr | [**dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array-46) (input\_iterator first, input\_iterator last, const allocator\_type & alloc\_in=allocator\_type()) <br> |
|  constexpr | [**dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array-56) (std::initializer\_list&lt; value\_type &gt; lst, const allocator\_type & alloc\_in=allocator\_type()) <br> |
|  constexpr | [**dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array-66) ([**dynamic\_array**](classutil_1_1dynamic__array.md) && other) noexcept<br> |
|  bool | [**empty**](classutil_1_1dynamic__array.md#function-empty) () const<br> |
|  iterator | [**end**](classutil_1_1dynamic__array.md#function-end-12) () <br> |
|  const\_iterator | [**end**](classutil_1_1dynamic__array.md#function-end-22) () const<br> |
|  void | [**fill**](classutil_1_1dynamic__array.md#function-fill) (const value\_type & value\_in) <br> |
|  reference | [**front**](classutil_1_1dynamic__array.md#function-front-12) () <br> |
|  const\_reference | [**front**](classutil_1_1dynamic__array.md#function-front-22) () const<br> |
|  size\_type | [**max\_size**](classutil_1_1dynamic__array.md#function-max_size) () const<br> |
|  [**dynamic\_array**](classutil_1_1dynamic__array.md) & | [**operator=**](classutil_1_1dynamic__array.md#function-operator) (const [**dynamic\_array**](classutil_1_1dynamic__array.md) & other) <br> |
|  [**dynamic\_array**](classutil_1_1dynamic__array.md) & | [**operator=**](classutil_1_1dynamic__array.md#function-operator_1) ([**dynamic\_array**](classutil_1_1dynamic__array.md) && other) noexcept<br> |
|  reference | [**operator[]**](classutil_1_1dynamic__array.md#function-operator_2) (const size\_type i) <br> |
|  const\_reference | [**operator[]**](classutil_1_1dynamic__array.md#function-operator_3) (const size\_type i) const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rbegin**](classutil_1_1dynamic__array.md#function-rbegin-12) () <br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rbegin**](classutil_1_1dynamic__array.md#function-rbegin-22) () const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rend**](classutil_1_1dynamic__array.md#function-rend-12) () <br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rend**](classutil_1_1dynamic__array.md#function-rend-22) () const<br> |
|  size\_type | [**size**](classutil_1_1dynamic__array.md#function-size) () const<br> |
|  void | [**swap**](classutil_1_1dynamic__array.md#function-swap-12) ([**dynamic\_array**](classutil_1_1dynamic__array.md) & other) noexcept<br> |
|  void | [**swap**](classutil_1_1dynamic__array.md#function-swap-22) ([**dynamic\_array**](classutil_1_1dynamic__array.md) && other) noexcept<br> |
| virtual  | [**~dynamic\_array**](classutil_1_1dynamic__array.md#function-dynamic_array) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  typename base\_class\_type::size\_type | [**static\_size**](#function-static_size) () <br> |




















































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
fixed_dynamic_array &=default SR_TYPES_NS::detail::fixed_dynamic_array::operator= (
    const fixed_dynamic_array & other_array
) 
```




<hr>



### function operator= 

```C++
fixed_dynamic_array &=default SR_TYPES_NS::detail::fixed_dynamic_array::operator= (
    fixed_dynamic_array && other_array
) noexcept
```




<hr>
## Public Static Functions Documentation




### function static\_size 

```C++
static inline typename base_class_type::size_type SR_TYPES_NS::detail::fixed_dynamic_array::static_size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

