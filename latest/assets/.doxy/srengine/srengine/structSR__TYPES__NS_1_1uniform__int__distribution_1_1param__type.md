

# Struct SR\_TYPES\_NS::uniform\_int\_distribution::param\_type



[**ClassList**](annotated.md) **>** [**uniform\_int\_distribution**](classSR__TYPES__NS_1_1uniform__int__distribution.md) **>** [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**get\_a**](#function-get_a) () const<br> |
|  WIDE\_INTEGER\_NODISCARD constexpr auto | [**get\_b**](#function-get_b) () const<br> |
|  constexpr auto | [**operator=**](#function-operator) (const [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) & other) <br> |
|  constexpr auto | [**operator=**](#function-operator_1) ([**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) && other) noexcept<br> |
|  constexpr | [**param\_type**](#function-param_type-13) (const result\_type & p\_a=(std::numeric\_limits&lt; result\_type &gt;::min)(), const result\_type & p\_b=(std::numeric\_limits&lt; result\_type &gt;::max)()) <br> |
|  constexpr | [**param\_type**](#function-param_type-23) (const [**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) & other) <br> |
|  constexpr | [**param\_type**](#function-param_type-33) ([**param\_type**](structSR__TYPES__NS_1_1uniform__int__distribution_1_1param__type.md) && other) noexcept<br> |
|  constexpr auto | [**set\_a**](#function-set_a) (const result\_type & p\_a) <br> |
|  constexpr auto | [**set\_b**](#function-set_b) (const result\_type & p\_b) <br> |
|   | [**~param\_type**](#function-param_type) () = default<br> |




























## Public Functions Documentation




### function get\_a 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto uniform_int_distribution::param_type::get_a () const
```




<hr>



### function get\_b 

```C++
inline WIDE_INTEGER_NODISCARD constexpr auto uniform_int_distribution::param_type::get_b () const
```




<hr>



### function operator= 

```C++
inline constexpr auto uniform_int_distribution::param_type::operator= (
    const param_type & other
) 
```




<hr>



### function operator= 

```C++
inline constexpr auto uniform_int_distribution::param_type::operator= (
    param_type && other
) noexcept
```




<hr>



### function param\_type [1/3]

```C++
inline explicit constexpr uniform_int_distribution::param_type::param_type (
    const result_type & p_a=(std::numeric_limits< result_type >::min)(),
    const result_type & p_b=(std::numeric_limits< result_type >::max)()
) 
```




<hr>



### function param\_type [2/3]

```C++
inline constexpr uniform_int_distribution::param_type::param_type (
    const param_type & other
) 
```




<hr>



### function param\_type [3/3]

```C++
inline constexpr uniform_int_distribution::param_type::param_type (
    param_type && other
) noexcept
```




<hr>



### function set\_a 

```C++
inline constexpr auto uniform_int_distribution::param_type::set_a (
    const result_type & p_a
) 
```




<hr>



### function set\_b 

```C++
inline constexpr auto uniform_int_distribution::param_type::set_b (
    const result_type & p_b
) 
```




<hr>



### function ~param\_type 

```C++
uniform_int_distribution::param_type::~param_type () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/UintWide_t.h`

