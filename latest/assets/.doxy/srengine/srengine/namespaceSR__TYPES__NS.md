

# Namespace SR\_TYPES\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**detail**](namespaceSR__TYPES__NS_1_1detail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**is\_integral**](structSR__TYPES__NS_1_1is__integral.md) &lt;class T&gt;<br> |
| struct | [**is\_integral&lt; SR\_TYPES\_NS::uintwide\_t&lt; Width2, LimbType, AllocatorType, IsSigned &gt; &gt;**](structSR__TYPES__NS_1_1is__integral_3_01SR__TYPES__NS_1_1uintwide__t_3_01Width2_00_01LimbType_00fc01edcfaa0e24ac94a4ffb2aaad7198.md) &lt;Width2, typename LimbType, typename AllocatorType, IsSigned&gt;<br> |








## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr int | [**digits**](#variable-digits)   = `/* multi line expression */`<br> |
|  constexpr int | [**digits10**](#variable-digits10)   = `static\_cast&lt;int&gt;((static\_cast&lt;std::uintmax\_t&gt;(digits) \* UINTMAX\_C(75257499)) / UINTMAX\_C(250000000))`<br> |
|  constexpr int | [**max\_digits10**](#variable-max_digits10)   = `digits10`<br> |
|  constexpr int | [**max\_exponent**](#variable-max_exponent)   = `digits`<br> |
|  constexpr int | [**max\_exponent10**](#variable-max_exponent10)   = `static\_cast&lt;int&gt;((static\_cast&lt;std::uintmax\_t&gt;(max\_exponent) \* UINTMAX\_C(75257499)) / UINTMAX\_C(250000000))`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**pow**](#function-pow) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, IsSigned &gt; & b, const OtherIntegralTypeP & p) <br> |
|  constexpr auto | [**powm**](#function-powm) (const uintwide\_t&lt; Width2, LimbType, AllocatorType, IsSigned &gt; & b, const OtherIntegralTypeP & p, const OtherIntegralTypeM & m) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**lowest**](#function-lowest) () <br> |
|  constexpr auto() | [**max**](#function-max) () <br> |
|  constexpr auto() | [**min**](#function-min) () <br> |


























## Public Static Attributes Documentation




### variable digits 

```C++
constexpr int SR_TYPES_NS::digits;
```




<hr>



### variable digits10 

```C++
constexpr int SR_TYPES_NS::digits10;
```




<hr>



### variable max\_digits10 

```C++
constexpr int SR_TYPES_NS::max_digits10;
```




<hr>



### variable max\_exponent 

```C++
constexpr int SR_TYPES_NS::max_exponent;
```




<hr>



### variable max\_exponent10 

```C++
constexpr int SR_TYPES_NS::max_exponent10;
```




<hr>
## Public Functions Documentation




### function pow 

```C++
template<typename OtherIntegralTypeP, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
constexpr auto SR_TYPES_NS::pow (
    const uintwide_t< Width2, LimbType, AllocatorType, IsSigned > & b,
    const OtherIntegralTypeP & p
) 
```




<hr>



### function powm 

```C++
template<typename OtherIntegralTypeP, typename OtherIntegralTypeM, const size_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned>
constexpr auto SR_TYPES_NS::powm (
    const uintwide_t< Width2, LimbType, AllocatorType, IsSigned > & b,
    const OtherIntegralTypeP & p,
    const OtherIntegralTypeM & m
) 
```




<hr>
## Public Static Functions Documentation




### function lowest 

```C++
static constexpr auto SR_TYPES_NS::lowest () 
```




<hr>



### function max 

```C++
static constexpr auto() SR_TYPES_NS::max () 
```




<hr>



### function min 

```C++
static constexpr auto() SR_TYPES_NS::min () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

