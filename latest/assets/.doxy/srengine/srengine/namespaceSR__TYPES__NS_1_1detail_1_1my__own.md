

# Namespace SR\_TYPES\_NS::detail::my\_own



[**Namespace List**](namespaces.md) **>** [**SR\_TYPES\_NS**](namespaceSR__TYPES__NS.md) **>** [**detail**](namespaceSR__TYPES__NS_1_1detail.md) **>** [**my\_own**](namespaceSR__TYPES__NS_1_1detail_1_1my__own.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::enable\_if\_t&lt;(std::is\_floating\_point&lt; FloatingPointType &gt;::value &&std::numeric\_limits&lt; FloatingPointType &gt;::is\_iec559), FloatingPointType &gt; | [**frexp**](#function-frexp) (FloatingPointType x, int \* expptr) <br> |
|  std::enable\_if\_t&lt;(std::is\_floating\_point&lt; FloatingPointType &gt;::value &&std::numeric\_limits&lt; FloatingPointType &gt;::is\_iec559), bool &gt; | [**isfinite**](#function-isfinite) (FloatingPointType x) <br> |




























## Public Functions Documentation




### function frexp 

```C++
template<typename FloatingPointType>
std::enable_if_t<(std::is_floating_point< FloatingPointType >::value &&std::numeric_limits< FloatingPointType >::is_iec559), FloatingPointType > SR_TYPES_NS::detail::my_own::frexp (
    FloatingPointType x,
    int * expptr
) 
```




<hr>



### function isfinite 

```C++
template<typename FloatingPointType>
std::enable_if_t<(std::is_floating_point< FloatingPointType >::value &&std::numeric_limits< FloatingPointType >::is_iec559), bool > SR_TYPES_NS::detail::my_own::isfinite (
    FloatingPointType x
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UintWide_t.h`

