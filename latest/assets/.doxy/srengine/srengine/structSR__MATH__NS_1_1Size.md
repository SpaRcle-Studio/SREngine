

# Struct SR\_MATH\_NS::Size

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Size**](structSR__MATH__NS_1_1Size.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Size**](structSR__MATH__NS_1_1Size.md) | [**Size**](#variable-size)  <br> |
|  SizeMetric | [**metric**](#variable-metric)   = `SizeMetric::Px`<br> |
|  T | [**v**](#variable-v)  <br> |
|  T | [**value**](#variable-value)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**IsPercent**](#function-ispercent) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsPixel**](#function-ispixel) () noexcept const<br> |
|   | [**Size**](#function-size-12) () noexcept<br> |
|   | [**Size**](#function-size-22) (T value, SizeMetric metric) noexcept<br> |
|  SR\_NODISCARD T | [**ToPixels**](#function-topixels-12) () noexcept const<br> |
|  SR\_NODISCARD T | [**ToPixels**](#function-topixels-22) (const T & parentSize) noexcept const<br> |




























## Public Attributes Documentation




### variable Size 

```C++
union SR_MATH_NS::Size SR_MATH_NS::Size< T >;
```




<hr>



### variable metric 

```C++
SizeMetric SR_MATH_NS::Size< T >::metric;
```




<hr>



### variable v 

```C++
T SR_MATH_NS::Size< T >::v;
```




<hr>



### variable value 

```C++
T SR_MATH_NS::Size< T >::value;
```




<hr>
## Public Functions Documentation




### function IsPercent 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Size::IsPercent () noexcept const
```




<hr>



### function IsPixel 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Size::IsPixel () noexcept const
```




<hr>



### function Size [1/2]

```C++
inline SR_MATH_NS::Size::Size () noexcept
```




<hr>



### function Size [2/2]

```C++
inline SR_MATH_NS::Size::Size (
    T value,
    SizeMetric metric
) noexcept
```




<hr>



### function ToPixels [1/2]

```C++
inline SR_NODISCARD T SR_MATH_NS::Size::ToPixels () noexcept const
```




<hr>



### function ToPixels [2/2]

```C++
inline SR_NODISCARD T SR_MATH_NS::Size::ToPixels (
    const T & parentSize
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Size.h`

