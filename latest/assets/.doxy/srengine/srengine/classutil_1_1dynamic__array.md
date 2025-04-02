

# Class util::dynamic\_array

**template &lt;typename ValueType, typename AllocatorType, typename SizeType, typename DiffType&gt;**



[**ClassList**](annotated.md) **>** [**util**](namespaceutil.md) **>** [**dynamic\_array**](classutil_1_1dynamic__array.md)










Inherited by the following classes: [SR\_TYPES\_NS::detail::fixed\_dynamic\_array](classSR__TYPES__NS_1_1detail_1_1fixed__dynamic__array.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename std::allocator\_traits&lt; AllocatorType &gt;::template rebind\_alloc&lt; ValueType &gt; | [**allocator\_type**](#typedef-allocator_type)  <br> |
| typedef const value\_type \* | [**const\_iterator**](#typedef-const_iterator)  <br> |
| typedef const value\_type \* | [**const\_pointer**](#typedef-const_pointer)  <br> |
| typedef const value\_type & | [**const\_reference**](#typedef-const_reference)  <br> |
| typedef [**SR\_TYPES\_NS::detail::iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; const value\_type \* &gt; | [**const\_reverse\_iterator**](#typedef-const_reverse_iterator)  <br> |
| typedef DiffType | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef value\_type \* | [**iterator**](#typedef-iterator)  <br> |
| typedef value\_type \* | [**pointer**](#typedef-pointer)  <br> |
| typedef value\_type & | [**reference**](#typedef-reference)  <br> |
| typedef [**SR\_TYPES\_NS::detail::iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; value\_type \* &gt; | [**reverse\_iterator**](#typedef-reverse_iterator)  <br> |
| typedef SizeType | [**size\_type**](#typedef-size_type)  <br> |
| typedef typename allocator\_type::value\_type | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  reference | [**at**](#function-at-12) (const size\_type i) <br> |
|  const\_reference | [**at**](#function-at-22) (const size\_type i) const<br> |
|  reference | [**back**](#function-back-12) () <br> |
|  const\_reference | [**back**](#function-back-22) () const<br> |
|  iterator | [**begin**](#function-begin-12) () <br> |
|  const\_iterator | [**begin**](#function-begin-22) () const<br> |
|  const\_iterator | [**cbegin**](#function-cbegin) () const<br> |
|  const\_iterator | [**cend**](#function-cend) () const<br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**crbegin**](#function-crbegin) () const<br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**crend**](#function-crend) () const<br> |
|  pointer | [**data**](#function-data-12) () <br> |
|  const\_pointer | [**data**](#function-data-22) () const<br> |
|  constexpr | [**dynamic\_array**](#function-dynamic_array-16) () = delete<br> |
|  constexpr | [**dynamic\_array**](#function-dynamic_array-26) (size\_type count\_in, const\_reference value\_in=value\_type(), const allocator\_type & alloc\_in=allocator\_type()) <br> |
|  constexpr | [**dynamic\_array**](#function-dynamic_array-36) (const [**dynamic\_array**](classutil_1_1dynamic__array.md) & other) <br> |
|  constexpr | [**dynamic\_array**](#function-dynamic_array-46) (input\_iterator first, input\_iterator last, const allocator\_type & alloc\_in=allocator\_type()) <br> |
|  constexpr | [**dynamic\_array**](#function-dynamic_array-56) (std::initializer\_list&lt; value\_type &gt; lst, const allocator\_type & alloc\_in=allocator\_type()) <br> |
|  constexpr | [**dynamic\_array**](#function-dynamic_array-66) ([**dynamic\_array**](classutil_1_1dynamic__array.md) && other) noexcept<br> |
|  bool | [**empty**](#function-empty) () const<br> |
|  iterator | [**end**](#function-end-12) () <br> |
|  const\_iterator | [**end**](#function-end-22) () const<br> |
|  void | [**fill**](#function-fill) (const value\_type & value\_in) <br> |
|  reference | [**front**](#function-front-12) () <br> |
|  const\_reference | [**front**](#function-front-22) () const<br> |
|  size\_type | [**max\_size**](#function-max_size) () const<br> |
|  [**dynamic\_array**](classutil_1_1dynamic__array.md) & | [**operator=**](#function-operator) (const [**dynamic\_array**](classutil_1_1dynamic__array.md) & other) <br> |
|  [**dynamic\_array**](classutil_1_1dynamic__array.md) & | [**operator=**](#function-operator_1) ([**dynamic\_array**](classutil_1_1dynamic__array.md) && other) noexcept<br> |
|  reference | [**operator[]**](#function-operator_2) (const size\_type i) <br> |
|  const\_reference | [**operator[]**](#function-operator_3) (const size\_type i) const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rbegin**](#function-rbegin-12) () <br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rbegin**](#function-rbegin-22) () const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rend**](#function-rend-12) () <br> |
|  [**const\_reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**rend**](#function-rend-22) () const<br> |
|  size\_type | [**size**](#function-size) () const<br> |
|  void | [**swap**](#function-swap-12) ([**dynamic\_array**](classutil_1_1dynamic__array.md) & other) noexcept<br> |
|  void | [**swap**](#function-swap-22) ([**dynamic\_array**](classutil_1_1dynamic__array.md) && other) noexcept<br> |
| virtual  | [**~dynamic\_array**](#function-dynamic_array) () <br> |




























## Public Types Documentation




### typedef allocator\_type 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::allocator_type =  typename std::allocator_traits<AllocatorType>::template rebind_alloc<ValueType>;
```




<hr>



### typedef const\_iterator 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::const_iterator =  const value_type*;
```




<hr>



### typedef const\_pointer 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::const_pointer =  const value_type*;
```




<hr>



### typedef const\_reference 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::const_reference =  const value_type&;
```




<hr>



### typedef const\_reverse\_iterator 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::const_reverse_iterator =  SR_TYPES_NS::detail::iterator_detail::reverse_iterator<const value_type*>;
```




<hr>



### typedef difference\_type 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::difference_type =  DiffType;
```




<hr>



### typedef iterator 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::iterator =  value_type*;
```




<hr>



### typedef pointer 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::pointer =  value_type*;
```




<hr>



### typedef reference 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::reference =  value_type&;
```




<hr>



### typedef reverse\_iterator 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::reverse_iterator =  SR_TYPES_NS::detail::iterator_detail::reverse_iterator<      value_type*>;
```




<hr>



### typedef size\_type 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::size_type =  SizeType;
```




<hr>



### typedef value\_type 

```C++
using util::dynamic_array< ValueType, AllocatorType, SizeType, DiffType >::value_type =  typename allocator_type::value_type;
```




<hr>
## Public Functions Documentation




### function at [1/2]

```C++
inline reference util::dynamic_array::at (
    const size_type i
) 
```




<hr>



### function at [2/2]

```C++
inline const_reference util::dynamic_array::at (
    const size_type i
) const
```




<hr>



### function back [1/2]

```C++
inline reference util::dynamic_array::back () 
```




<hr>



### function back [2/2]

```C++
inline const_reference util::dynamic_array::back () const
```




<hr>



### function begin [1/2]

```C++
inline iterator util::dynamic_array::begin () 
```




<hr>



### function begin [2/2]

```C++
inline const_iterator util::dynamic_array::begin () const
```




<hr>



### function cbegin 

```C++
inline const_iterator util::dynamic_array::cbegin () const
```




<hr>



### function cend 

```C++
inline const_iterator util::dynamic_array::cend () const
```




<hr>



### function crbegin 

```C++
inline const_reverse_iterator util::dynamic_array::crbegin () const
```




<hr>



### function crend 

```C++
inline const_reverse_iterator util::dynamic_array::crend () const
```




<hr>



### function data [1/2]

```C++
inline pointer util::dynamic_array::data () 
```




<hr>



### function data [2/2]

```C++
inline const_pointer util::dynamic_array::data () const
```




<hr>



### function dynamic\_array [1/6]

```C++
constexpr util::dynamic_array::dynamic_array () = delete
```




<hr>



### function dynamic\_array [2/6]

```C++
inline explicit constexpr util::dynamic_array::dynamic_array (
    size_type count_in,
    const_reference value_in=value_type(),
    const allocator_type & alloc_in=allocator_type()
) 
```




<hr>



### function dynamic\_array [3/6]

```C++
inline constexpr util::dynamic_array::dynamic_array (
    const dynamic_array & other
) 
```




<hr>



### function dynamic\_array [4/6]

```C++
template<typename input_iterator>
inline constexpr util::dynamic_array::dynamic_array (
    input_iterator first,
    input_iterator last,
    const allocator_type & alloc_in=allocator_type()
) 
```




<hr>



### function dynamic\_array [5/6]

```C++
inline constexpr util::dynamic_array::dynamic_array (
    std::initializer_list< value_type > lst,
    const allocator_type & alloc_in=allocator_type()
) 
```




<hr>



### function dynamic\_array [6/6]

```C++
inline constexpr util::dynamic_array::dynamic_array (
    dynamic_array && other
) noexcept
```




<hr>



### function empty 

```C++
inline bool util::dynamic_array::empty () const
```




<hr>



### function end [1/2]

```C++
inline iterator util::dynamic_array::end () 
```




<hr>



### function end [2/2]

```C++
inline const_iterator util::dynamic_array::end () const
```




<hr>



### function fill 

```C++
inline void util::dynamic_array::fill (
    const value_type & value_in
) 
```




<hr>



### function front [1/2]

```C++
inline reference util::dynamic_array::front () 
```




<hr>



### function front [2/2]

```C++
inline const_reference util::dynamic_array::front () const
```




<hr>



### function max\_size 

```C++
inline size_type util::dynamic_array::max_size () const
```




<hr>



### function operator= 

```C++
inline dynamic_array & util::dynamic_array::operator= (
    const dynamic_array & other
) 
```




<hr>



### function operator= 

```C++
inline dynamic_array & util::dynamic_array::operator= (
    dynamic_array && other
) noexcept
```




<hr>



### function operator[] 

```C++
inline reference util::dynamic_array::operator[] (
    const size_type i
) 
```




<hr>



### function operator[] 

```C++
inline const_reference util::dynamic_array::operator[] (
    const size_type i
) const
```




<hr>



### function rbegin [1/2]

```C++
inline reverse_iterator util::dynamic_array::rbegin () 
```




<hr>



### function rbegin [2/2]

```C++
inline const_reverse_iterator util::dynamic_array::rbegin () const
```




<hr>



### function rend [1/2]

```C++
inline reverse_iterator util::dynamic_array::rend () 
```




<hr>



### function rend [2/2]

```C++
inline const_reverse_iterator util::dynamic_array::rend () const
```




<hr>



### function size 

```C++
inline size_type util::dynamic_array::size () const
```




<hr>



### function swap [1/2]

```C++
inline void util::dynamic_array::swap (
    dynamic_array & other
) noexcept
```




<hr>



### function swap [2/2]

```C++
inline void util::dynamic_array::swap (
    dynamic_array && other
) noexcept
```




<hr>



### function ~dynamic\_array 

```C++
inline virtual util::dynamic_array::~dynamic_array () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

