

# Class SR\_TYPES\_NS::detail::array\_detail::array

**template &lt;typename T, std::size\_t N&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**array\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1array__detail.md) **>** [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef const\_pointer | [**const\_iterator**](#typedef-const_iterator)  <br> |
| typedef const T \* | [**const\_pointer**](#typedef-const_pointer)  <br> |
| typedef const T & | [**const\_reference**](#typedef-const_reference)  <br> |
| typedef [**iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; const\_iterator &gt; | [**const\_reverse\_iterator**](#typedef-const_reverse_iterator)  <br> |
| typedef std::ptrdiff\_t | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef pointer | [**iterator**](#typedef-iterator)  <br> |
| typedef T \* | [**pointer**](#typedef-pointer)  <br> |
| typedef T & | [**reference**](#typedef-reference)  <br> |
| typedef [**iterator\_detail::reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator &gt; | [**reverse\_iterator**](#typedef-reverse_iterator)  <br> |
| typedef std::size\_t | [**size\_type**](#typedef-size_type)  <br> |
| typedef T | [**value\_type**](#typedef-value_type)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  value\_type | [**elems**](#variable-elems)   = `{ }`<br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  size\_type | [**static\_size**](#variable-static_size)   = `N`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**assign**](#function-assign) (const value\_type & value) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**at**](#function-at-12) (const size\_type i) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**at**](#function-at-22) (const size\_type i) const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**back**](#function-back-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**back**](#function-back-22) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**begin**](#function-begin-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**begin**](#function-begin-22) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**c\_array**](#function-c_array) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**cbegin**](#function-cbegin) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**cend**](#function-cend) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**crbegin**](#function-crbegin) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**crend**](#function-crend) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**data**](#function-data-12) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**data**](#function-data-22) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**end**](#function-end-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**end**](#function-end-22) () const<br> |
|  void | [**fill**](#function-fill) (const value\_type & value) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**front**](#function-front-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**front**](#function-front-22) () const<br> |
|  [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md) & | [**operator=**](#function-operator) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T2, N &gt; & y) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**operator[]**](#function-operator_1) (const size\_type i) <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**operator[]**](#function-operator_2) (const size\_type i) const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rbegin**](#function-rbegin-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rbegin**](#function-rbegin-22) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rend**](#function-rend-12) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**rend**](#function-rend-22) () const<br> |
|  void | [**swap**](#function-swap) ([**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T2, N &gt; & y) noexcept<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**empty**](#function-empty) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**max\_size**](#function-max_size) () <br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**size**](#function-size) () <br> |


























## Public Types Documentation




### typedef const\_iterator 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::const_iterator =  const_pointer;
```




<hr>



### typedef const\_pointer 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::const_pointer =  const T*;
```




<hr>



### typedef const\_reference 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::const_reference =  const T&;
```




<hr>



### typedef const\_reverse\_iterator 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::const_reverse_iterator =  iterator_detail::reverse_iterator<const_iterator>;
```




<hr>



### typedef difference\_type 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::difference_type =  std::ptrdiff_t;
```




<hr>



### typedef iterator 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::iterator =  pointer;
```




<hr>



### typedef pointer 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::pointer =  T*;
```




<hr>



### typedef reference 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::reference =  T&;
```




<hr>



### typedef reverse\_iterator 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::reverse_iterator =  iterator_detail::reverse_iterator<iterator>;
```




<hr>



### typedef size\_type 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::size_type =  std::size_t;
```




<hr>



### typedef value\_type 

```C++
using SR_TYPES_NS::detail::array_detail::array< T, N >::value_type =  T;
```




<hr>
## Public Attributes Documentation




### variable elems 

```C++
value_type SR_TYPES_NS::detail::array_detail::array< T, N >::elems[N];
```




<hr>
## Public Static Attributes Documentation




### variable static\_size 

```C++
size_type SR_TYPES_NS::detail::array_detail::array< T, N >::static_size;
```




<hr>
## Public Functions Documentation




### function assign 

```C++
inline void SR_TYPES_NS::detail::array_detail::array::assign (
    const value_type & value
) 
```




<hr>



### function at [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::at (
    const size_type i
) 
```




<hr>



### function at [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::at (
    const size_type i
) const
```




<hr>



### function back [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::back () 
```




<hr>



### function back [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::back () const
```




<hr>



### function begin [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::begin () 
```




<hr>



### function begin [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::begin () const
```




<hr>



### function c\_array 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::c_array () 
```




<hr>



### function cbegin 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::cbegin () const
```




<hr>



### function cend 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::cend () const
```




<hr>



### function crbegin 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::crbegin () const
```




<hr>



### function crend 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::crend () const
```




<hr>



### function data [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::data () const
```




<hr>



### function data [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::data () 
```




<hr>



### function end [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::end () 
```




<hr>



### function end [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::end () const
```




<hr>



### function fill 

```C++
inline void SR_TYPES_NS::detail::array_detail::array::fill (
    const value_type & value
) 
```




<hr>



### function front [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::front () 
```




<hr>



### function front [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::front () const
```




<hr>



### function operator= 

```C++
template<typename T2>
inline array & SR_TYPES_NS::detail::array_detail::array::operator= (
    const array < T2, N > & y
) 
```




<hr>



### function operator[] 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::operator[] (
    const size_type i
) 
```




<hr>



### function operator[] 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::operator[] (
    const size_type i
) const
```




<hr>



### function rbegin [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::rbegin () 
```




<hr>



### function rbegin [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::rbegin () const
```




<hr>



### function rend [1/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::rend () 
```




<hr>



### function rend [2/2]

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::rend () const
```




<hr>



### function swap 

```C++
template<typename T2>
inline void SR_TYPES_NS::detail::array_detail::array::swap (
    array < T2, N > & y
) noexcept
```




<hr>
## Public Static Functions Documentation




### function empty 

```C++
static inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::empty () 
```




<hr>



### function max\_size 

```C++
static inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::max_size () 
```




<hr>



### function size 

```C++
static inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::array_detail::array::size () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

