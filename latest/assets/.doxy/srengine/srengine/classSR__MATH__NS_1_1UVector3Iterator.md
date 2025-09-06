

# Class SR\_MATH\_NS::UVector3Iterator



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::ptrdiff\_t | [**difference\_type**](#typedef-difference_type)  <br> |
| typedef std::random\_access\_iterator\_tag | [**iterator\_category**](#typedef-iterator_category)  <br> |
| typedef SR\_MATH\_NS::UVector3 \* | [**pointer**](#typedef-pointer)  <br> |
| typedef SR\_MATH\_NS::UVector3 | [**reference**](#typedef-reference)  <br> |
| typedef SR\_MATH\_NS::UVector3 | [**value\_type**](#typedef-value_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**UVector3Iterator**](#function-uvector3iterator-12) () <br> |
|   | [**UVector3Iterator**](#function-uvector3iterator-22) (SR\_MATH\_NS::UVector3 max, std::size\_t index) <br> |
|  bool | [**operator!=**](#function-operator) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  SR\_MATH\_NS::UVector3 | [**operator\***](#function-operator_1) () const<br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) | [**operator+**](#function-operator_2) (difference\_type n) const<br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & | [**operator++**](#function-operator_3) () <br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) | [**operator++**](#function-operator_4) (int) <br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & | [**operator+=**](#function-operator_5) (difference\_type n) <br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) | [**operator-**](#function-operator-) (difference\_type n) const<br> |
|  difference\_type | [**operator-**](#function-operator-_1) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & | [**operator--**](#function-operator-) () <br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) | [**operator--**](#function-operator-_1) (int) <br> |
|  [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & | [**operator-=**](#function-operator-_2) (difference\_type n) <br> |
|  bool | [**operator&lt;**](#function-operator_6) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  bool | [**operator&lt;=**](#function-operator_7) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  bool | [**operator==**](#function-operator_8) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  bool | [**operator&gt;**](#function-operator_9) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  bool | [**operator&gt;=**](#function-operator_10) (const [**UVector3Iterator**](classSR__MATH__NS_1_1UVector3Iterator.md) & other) const<br> |
|  SR\_MATH\_NS::UVector3 | [**operator[]**](#function-operator_11) (difference\_type n) const<br> |




























## Public Types Documentation




### typedef difference\_type 

```C++
using SR_MATH_NS::UVector3Iterator::difference_type =  std::ptrdiff_t;
```




<hr>



### typedef iterator\_category 

```C++
using SR_MATH_NS::UVector3Iterator::iterator_category =  std::random_access_iterator_tag;
```




<hr>



### typedef pointer 

```C++
using SR_MATH_NS::UVector3Iterator::pointer =  SR_MATH_NS::UVector3 *;
```




<hr>



### typedef reference 

```C++
using SR_MATH_NS::UVector3Iterator::reference =  SR_MATH_NS::UVector3;
```




<hr>



### typedef value\_type 

```C++
using SR_MATH_NS::UVector3Iterator::value_type =  SR_MATH_NS::UVector3;
```




<hr>
## Public Functions Documentation




### function UVector3Iterator [1/2]

```C++
inline SR_MATH_NS::UVector3Iterator::UVector3Iterator () 
```




<hr>



### function UVector3Iterator [2/2]

```C++
inline SR_MATH_NS::UVector3Iterator::UVector3Iterator (
    SR_MATH_NS::UVector3 max,
    std::size_t index
) 
```




<hr>



### function operator!= 

```C++
inline bool SR_MATH_NS::UVector3Iterator::operator!= (
    const UVector3Iterator & other
) const
```




<hr>



### function operator\* 

```C++
inline SR_MATH_NS::UVector3 SR_MATH_NS::UVector3Iterator::operator* () const
```




<hr>



### function operator+ 

```C++
inline UVector3Iterator SR_MATH_NS::UVector3Iterator::operator+ (
    difference_type n
) const
```




<hr>



### function operator++ 

```C++
inline UVector3Iterator & SR_MATH_NS::UVector3Iterator::operator++ () 
```




<hr>



### function operator++ 

```C++
inline UVector3Iterator SR_MATH_NS::UVector3Iterator::operator++ (
    int
) 
```




<hr>



### function operator+= 

```C++
inline UVector3Iterator & SR_MATH_NS::UVector3Iterator::operator+= (
    difference_type n
) 
```




<hr>



### function operator- 

```C++
inline UVector3Iterator SR_MATH_NS::UVector3Iterator::operator- (
    difference_type n
) const
```




<hr>



### function operator- 

```C++
inline difference_type SR_MATH_NS::UVector3Iterator::operator- (
    const UVector3Iterator & other
) const
```




<hr>



### function operator-- 

```C++
inline UVector3Iterator & SR_MATH_NS::UVector3Iterator::operator-- () 
```




<hr>



### function operator-- 

```C++
inline UVector3Iterator SR_MATH_NS::UVector3Iterator::operator-- (
    int
) 
```




<hr>



### function operator-= 

```C++
inline UVector3Iterator & SR_MATH_NS::UVector3Iterator::operator-= (
    difference_type n
) 
```




<hr>



### function operator&lt; 

```C++
inline bool SR_MATH_NS::UVector3Iterator::operator< (
    const UVector3Iterator & other
) const
```




<hr>



### function operator&lt;= 

```C++
inline bool SR_MATH_NS::UVector3Iterator::operator<= (
    const UVector3Iterator & other
) const
```




<hr>



### function operator== 

```C++
inline bool SR_MATH_NS::UVector3Iterator::operator== (
    const UVector3Iterator & other
) const
```




<hr>



### function operator&gt; 

```C++
inline bool SR_MATH_NS::UVector3Iterator::operator> (
    const UVector3Iterator & other
) const
```




<hr>



### function operator&gt;= 

```C++
inline bool SR_MATH_NS::UVector3Iterator::operator>= (
    const UVector3Iterator & other
) const
```




<hr>



### function operator[] 

```C++
inline SR_MATH_NS::UVector3 SR_MATH_NS::UVector3Iterator::operator[] (
    difference_type n
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Math/VectorRanges.h`

