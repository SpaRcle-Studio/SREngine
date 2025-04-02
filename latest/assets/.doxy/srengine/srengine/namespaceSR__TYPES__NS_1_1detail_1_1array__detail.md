

# Namespace SR\_TYPES\_NS::detail::array\_detail



[**Namespace List**](namespaces.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**array\_detail**](namespaceSR__TYPES__NS_1_1detail_1_1array__detail.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md) &lt;typename T, N&gt;<br> |
| class | [**tuple\_element**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1tuple__element.md) &lt;N, typename T&gt;<br> |
| class | [**tuple\_element&lt; I, array&lt; T, N &gt; &gt;**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1tuple__element_3_01I_00_01array_3_01T_00_01N_01_4_01_4.md) &lt;I, typename T, N&gt;<br> |
| class | [**tuple\_size**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1tuple__size.md) &lt;typename T&gt;<br> |
| class | [**tuple\_size&lt; array&lt; T, N &gt; &gt;**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1tuple__size_3_01array_3_01T_00_01N_01_4_01_4.md) &lt;typename T, N&gt;<br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator!=**](#function-operator) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & left, const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & right) <br> |
|  bool | [**operator&lt;**](#function-operator_1) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & left, const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & right) <br> |
|  bool | [**operator&lt;=**](#function-operator_2) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & left, const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & right) <br> |
|  bool | [**operator==**](#function-operator_3) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & left, const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & right) <br> |
|  bool | [**operator&gt;**](#function-operator_4) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & left, const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & right) <br> |
|  bool | [**operator&gt;=**](#function-operator_5) (const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & left, const [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & right) <br> |
|  void | [**swap**](#function-swap) ([**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & x, [**array**](classSR__TYPES__NS_1_1detail_1_1array__detail_1_1array.md)&lt; T, N &gt; & y) noexcept<br> |




























## Public Functions Documentation




### function operator!= 

```C++
template<typename T, size_t N>
bool SR_TYPES_NS::detail::array_detail::operator!= (
    const array < T, N > & left,
    const array < T, N > & right
) 
```




<hr>



### function operator&lt; 

```C++
template<typename T, size_t N>
bool SR_TYPES_NS::detail::array_detail::operator< (
    const array < T, N > & left,
    const array < T, N > & right
) 
```




<hr>



### function operator&lt;= 

```C++
template<typename T, size_t N>
bool SR_TYPES_NS::detail::array_detail::operator<= (
    const array < T, N > & left,
    const array < T, N > & right
) 
```




<hr>



### function operator== 

```C++
template<typename T, size_t N>
bool SR_TYPES_NS::detail::array_detail::operator== (
    const array < T, N > & left,
    const array < T, N > & right
) 
```




<hr>



### function operator&gt; 

```C++
template<typename T, size_t N>
bool SR_TYPES_NS::detail::array_detail::operator> (
    const array < T, N > & left,
    const array < T, N > & right
) 
```




<hr>



### function operator&gt;= 

```C++
template<typename T, size_t N>
bool SR_TYPES_NS::detail::array_detail::operator>= (
    const array < T, N > & left,
    const array < T, N > & right
) 
```




<hr>



### function swap 

```C++
template<typename T, size_t N>
void SR_TYPES_NS::detail::array_detail::swap (
    array < T, N > & x,
    array < T, N > & y
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

