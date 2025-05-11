

# Class SR\_UTILS\_NS::Web::CSSOptionalEnumContainer

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md)










Inherited by the following classes: [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md),  [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  T | [**value**](#variable-value)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CSSOptionalEnumContainer**](#function-cssoptionalenumcontainer-15) () = default<br> |
|   | [**CSSOptionalEnumContainer**](#function-cssoptionalenumcontainer-25) (const T & value) <br> |
|   | [**CSSOptionalEnumContainer**](#function-cssoptionalenumcontainer-35) (const T && value) <br> |
|   | [**CSSOptionalEnumContainer**](#function-cssoptionalenumcontainer-45) (const [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) & other) <br> |
|   | [**CSSOptionalEnumContainer**](#function-cssoptionalenumcontainer-55) ([**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) && other) noexcept<br> |
| virtual void | [**OnChanged**](#function-onchanged) () <br> |
|  [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) & | [**operator=**](#function-operator) (const [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) & other) <br> |
|  [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) & | [**operator=**](#function-operator_1) ([**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) && other) noexcept<br> |
|  [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) & | [**operator=**](#function-operator_2) (const T & value) <br> |
|  [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) & | [**operator=**](#function-operator_3) (const T && value) <br> |
| virtual  | [**~CSSOptionalEnumContainer**](#function-cssoptionalenumcontainer) () = default<br> |




























## Public Attributes Documentation




### variable value 

```C++
T SR_UTILS_NS::Web::CSSOptionalEnumContainer< T >::value;
```




<hr>
## Public Functions Documentation




### function CSSOptionalEnumContainer [1/5]

```C++
SR_UTILS_NS::Web::CSSOptionalEnumContainer::CSSOptionalEnumContainer () = default
```




<hr>



### function CSSOptionalEnumContainer [2/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnumContainer::CSSOptionalEnumContainer (
    const T & value
) 
```




<hr>



### function CSSOptionalEnumContainer [3/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnumContainer::CSSOptionalEnumContainer (
    const T && value
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function CSSOptionalEnumContainer [4/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnumContainer::CSSOptionalEnumContainer (
    const CSSOptionalEnumContainer & other
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function CSSOptionalEnumContainer [5/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnumContainer::CSSOptionalEnumContainer (
    CSSOptionalEnumContainer && other
) noexcept
```




<hr>



### function OnChanged 

```C++
inline virtual void SR_UTILS_NS::Web::CSSOptionalEnumContainer::OnChanged () 
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnumContainer & SR_UTILS_NS::Web::CSSOptionalEnumContainer::operator= (
    const CSSOptionalEnumContainer & other
) 
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnumContainer & SR_UTILS_NS::Web::CSSOptionalEnumContainer::operator= (
    CSSOptionalEnumContainer && other
) noexcept
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnumContainer & SR_UTILS_NS::Web::CSSOptionalEnumContainer::operator= (
    const T & value
) 
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnumContainer & SR_UTILS_NS::Web::CSSOptionalEnumContainer::operator= (
    const T && value
) 
```




<hr>



### function ~CSSOptionalEnumContainer 

```C++
virtual SR_UTILS_NS::Web::CSSOptionalEnumContainer::~CSSOptionalEnumContainer () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Web/CSS/CSSOptional.h`

