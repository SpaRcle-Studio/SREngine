

# Class SR\_TYPES\_NS::uniform\_int\_distribution

**template &lt;const size\_t Width2, typename LimbType, typename AllocatorType, const bool IsSigned&gt;**



[**ClassList**](annotated.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**uniform\_int\_distribution**](classSR__TYPES__NS_1_1uniform__int__distribution.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**uintwide\_t**](classSR__TYPES__NS_1_1uintwide__t.md)&lt; Width2, LimbType, AllocatorType, IsSigned &gt; | [**result\_type**](#typedef-result_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD auto | [**a**](#function-a) () const<br> |
|  WIDE\_INTEGER\_NODISCARD auto | [**b**](#function-b) () const<br> |
|  [**result\_type**](classSR__TYPES__NS_1_1uintwide__t.md) | [**operator()**](#function-operator()-12) (GeneratorType & generator) <br> |
|  [**result\_type**](classSR__TYPES__NS_1_1uintwide__t.md) | [**operator()**](#function-operator()-22) (GeneratorType & input\_generator, const [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) & input\_params) <br> |
|  auto constexpr | [**operator=**](#function-operator) (const [**uniform\_int\_distribution**](classSR__TYPES__NS_1_1uniform__int__distribution.md) & other) <br> |
|  auto constexpr | [**operator=**](#function-operator_1) ([**uniform\_int\_distribution**](classSR__TYPES__NS_1_1uniform__int__distribution.md) && other) noexcept<br> |
|  auto constexpr | [**param**](#function-param-12) (const [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) & new\_params) <br> |
|  WIDE\_INTEGER\_NODISCARD auto | [**param**](#function-param-22) () const<br> |
|  constexpr | [**uniform\_int\_distribution**](#function-uniform_int_distribution-14) (const [**result\_type**](classSR__TYPES__NS_1_1uintwide__t.md) & p\_a=(std::numeric\_limits&lt; [**result\_type**](classSR__TYPES__NS_1_1uintwide__t.md) &gt;::min)(), const [**result\_type**](classSR__TYPES__NS_1_1uintwide__t.md) & p\_b=(std::numeric\_limits&lt; [**result\_type**](classSR__TYPES__NS_1_1uintwide__t.md) &gt;::max)()) <br> |
|  constexpr | [**uniform\_int\_distribution**](#function-uniform_int_distribution-24) (const [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) & other\_params) <br> |
|  constexpr | [**uniform\_int\_distribution**](#function-uniform_int_distribution-34) (const [**uniform\_int\_distribution**](classSR__TYPES__NS_1_1uniform__int__distribution.md) & other\_distribution) = delete<br> |
|  constexpr | [**uniform\_int\_distribution**](#function-uniform_int_distribution-44) ([**uniform\_int\_distribution**](classSR__TYPES__NS_1_1uniform__int__distribution.md) && other) noexcept<br> |
|   | [**~uniform\_int\_distribution**](#function-uniform_int_distribution) () = default<br> |




























## Public Types Documentation




### typedef result\_type 

```C++
using SR_TYPES_NS::uniform_int_distribution< Width2, LimbType, AllocatorType, IsSigned >::result_type =  uintwide_t<Width2, LimbType, AllocatorType, IsSigned>;
```




<hr>
## Public Functions Documentation




### function a 

```C++
inline WIDE_INTEGER_NODISCARD auto SR_TYPES_NS::uniform_int_distribution::a () const
```




<hr>



### function b 

```C++
inline WIDE_INTEGER_NODISCARD auto SR_TYPES_NS::uniform_int_distribution::b () const
```




<hr>



### function operator() [1/2]

```C++
template<typename GeneratorType, const int GeneratorResultBits>
inline result_type SR_TYPES_NS::uniform_int_distribution::operator() (
    GeneratorType & generator
) 
```




<hr>



### function operator() [2/2]

```C++
template<typename GeneratorType, const int GeneratorResultBits>
inline result_type SR_TYPES_NS::uniform_int_distribution::operator() (
    GeneratorType & input_generator,
    const param_type & input_params
) 
```




<hr>



### function operator= 

```C++
inline auto constexpr SR_TYPES_NS::uniform_int_distribution::operator= (
    const uniform_int_distribution & other
) 
```




<hr>



### function operator= 

```C++
inline auto constexpr SR_TYPES_NS::uniform_int_distribution::operator= (
    uniform_int_distribution && other
) noexcept
```




<hr>



### function param [1/2]

```C++
inline auto constexpr SR_TYPES_NS::uniform_int_distribution::param (
    const param_type & new_params
) 
```




<hr>



### function param [2/2]

```C++
inline WIDE_INTEGER_NODISCARD auto SR_TYPES_NS::uniform_int_distribution::param () const
```




<hr>



### function uniform\_int\_distribution [1/4]

```C++
inline explicit constexpr SR_TYPES_NS::uniform_int_distribution::uniform_int_distribution (
    const result_type & p_a=(std::numeric_limits< result_type >::min)(),
    const result_type & p_b=(std::numeric_limits< result_type >::max)()
) 
```




<hr>



### function uniform\_int\_distribution [2/4]

```C++
inline explicit constexpr SR_TYPES_NS::uniform_int_distribution::uniform_int_distribution (
    const param_type & other_params
) 
```




<hr>



### function uniform\_int\_distribution [3/4]

```C++
constexpr SR_TYPES_NS::uniform_int_distribution::uniform_int_distribution (
    const uniform_int_distribution & other_distribution
) = delete
```




<hr>



### function uniform\_int\_distribution [4/4]

```C++
inline constexpr SR_TYPES_NS::uniform_int_distribution::uniform_int_distribution (
    uniform_int_distribution && other
) noexcept
```




<hr>



### function ~uniform\_int\_distribution 

```C++
SR_TYPES_NS::uniform_int_distribution::~uniform_int_distribution () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

