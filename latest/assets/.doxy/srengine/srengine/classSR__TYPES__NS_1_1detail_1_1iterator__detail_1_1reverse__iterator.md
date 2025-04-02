

# Class SR\_TYPES\_NS::detail::iterator\_detail::reverse\_iterator

**template &lt;typename iterator\_type&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**iterator\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1iterator__detail.md) **>** [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)








Inherits the following classes: [SR\_TYPES\_NS::detail::iterator\_detail::my\_iterator](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename [**iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md)&lt; iterator\_type &gt;::difference\_type | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef typename [**iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md)&lt; iterator\_type &gt;::iterator\_category | [**iterator\_category**](#typedef-iterator_category)  <br> |
| typedef typename [**iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md)&lt; iterator\_type &gt;::pointer | [**pointer**](#typedef-pointer)  <br> |
| typedef typename [**iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md)&lt; iterator\_type &gt;::reference | [**reference**](#typedef-reference)  <br> |
| typedef typename [**iterator\_traits**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1iterator__traits.md)&lt; iterator\_type &gt;::value\_type | [**value\_type**](#typedef-value_type)  <br> |


## Public Types inherited from SR_TYPES_NS::detail::iterator_detail::my_iterator

See [SR\_TYPES\_NS::detail::iterator\_detail::my\_iterator](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md)

| Type | Name |
| ---: | :--- |
| typedef my\_difference\_type | [**difference\_type**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md#typedef-difference_type)  <br> |
| typedef my\_category | [**iterator\_category**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md#typedef-iterator_category)  <br> |
| typedef my\_pointer\_type | [**pointer**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md#typedef-pointer)  <br> |
| typedef my\_reference\_type | [**reference**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md#typedef-reference)  <br> |
| typedef my\_value\_type | [**value\_type**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md#typedef-value_type)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**base**](#function-base) () const<br> |
|  reference | [**operator\***](#function-operator) () const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**operator+**](#function-operator_1) (typename [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator\_type &gt;::difference\_type n) const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) & | [**operator++**](#function-operator_2) () <br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**operator++**](#function-operator_3) (int) <br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) & | [**operator+=**](#function-operator_4) (typename [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator\_type &gt;::difference\_type n) <br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**operator-**](#function-operator_5) (typename [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator\_type &gt;::difference\_type n) const<br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) & | [**operator--**](#function-operator_6) () <br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) | [**operator--**](#function-operator_7) (int) <br> |
|  [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md) & | [**operator-=**](#function-operator_8) (typename [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator\_type &gt;::difference\_type n) <br> |
|  pointer | [**operator-&gt;**](#function-operator_9) () const<br> |
|  reference | [**operator[]**](#function-operator_10) (typename [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; iterator\_type &gt;::difference\_type n) const<br> |
|  constexpr | [**reverse\_iterator**](#function-reverse_iterator-13) () = default<br> |
|  constexpr | [**reverse\_iterator**](#function-reverse_iterator-23) (iterator\_type x) <br> |
|  constexpr | [**reverse\_iterator**](#function-reverse_iterator-33) (const [**reverse\_iterator**](classSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1reverse__iterator.md)&lt; other &gt; & u) <br> |


## Public Functions inherited from SR_TYPES_NS::detail::iterator_detail::my_iterator

See [SR\_TYPES\_NS::detail::iterator\_detail::my\_iterator](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**my\_iterator**](structSR__TYPES__NS_1_1detail_1_1iterator__detail_1_1my__iterator.md#function-my_iterator) () = default<br> |






















































## Public Types Documentation




### typedef difference\_type 

```C++
using SR_TYPES_NS::detail::iterator_detail::reverse_iterator< iterator_type >::difference_type =  typename iterator_traits<iterator_type>::difference_type;
```




<hr>



### typedef iterator\_category 

```C++
using SR_TYPES_NS::detail::iterator_detail::reverse_iterator< iterator_type >::iterator_category =  typename iterator_traits<iterator_type>::iterator_category;
```




<hr>



### typedef pointer 

```C++
using SR_TYPES_NS::detail::iterator_detail::reverse_iterator< iterator_type >::pointer =  typename iterator_traits<iterator_type>::pointer;
```




<hr>



### typedef reference 

```C++
using SR_TYPES_NS::detail::iterator_detail::reverse_iterator< iterator_type >::reference =  typename iterator_traits<iterator_type>::reference;
```




<hr>



### typedef value\_type 

```C++
using SR_TYPES_NS::detail::iterator_detail::reverse_iterator< iterator_type >::value_type =  typename iterator_traits<iterator_type>::value_type;
```




<hr>
## Public Functions Documentation




### function base 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto SR_TYPES_NS::detail::iterator_detail::reverse_iterator::base () const
```




<hr>



### function operator\* 

```C++
inline reference SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator* () const
```




<hr>



### function operator+ 

```C++
inline reverse_iterator SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator+ (
    typename reverse_iterator < iterator_type >::difference_type n
) const
```




<hr>



### function operator++ 

```C++
inline reverse_iterator & SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator++ () 
```




<hr>



### function operator++ 

```C++
inline reverse_iterator SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator++ (
    int
) 
```




<hr>



### function operator+= 

```C++
inline reverse_iterator & SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator+= (
    typename reverse_iterator < iterator_type >::difference_type n
) 
```




<hr>



### function operator- 

```C++
inline reverse_iterator SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator- (
    typename reverse_iterator < iterator_type >::difference_type n
) const
```




<hr>



### function operator-- 

```C++
inline reverse_iterator & SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator-- () 
```




<hr>



### function operator-- 

```C++
inline reverse_iterator SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator-- (
    int
) 
```




<hr>



### function operator-= 

```C++
inline reverse_iterator & SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator-= (
    typename reverse_iterator < iterator_type >::difference_type n
) 
```




<hr>



### function operator-&gt; 

```C++
inline pointer SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator-> () const
```




<hr>



### function operator[] 

```C++
inline reference SR_TYPES_NS::detail::iterator_detail::reverse_iterator::operator[] (
    typename reverse_iterator < iterator_type >::difference_type n
) const
```




<hr>



### function reverse\_iterator [1/3]

```C++
constexpr SR_TYPES_NS::detail::iterator_detail::reverse_iterator::reverse_iterator () = default
```




<hr>



### function reverse\_iterator [2/3]

```C++
inline explicit constexpr SR_TYPES_NS::detail::iterator_detail::reverse_iterator::reverse_iterator (
    iterator_type x
) 
```




<hr>



### function reverse\_iterator [3/3]

```C++
template<typename other>
inline constexpr SR_TYPES_NS::detail::iterator_detail::reverse_iterator::reverse_iterator (
    const reverse_iterator < other > & u
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

