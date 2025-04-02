

# Struct SR\_MATH\_NS::Size2

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Size2**](structSR__MATH__NS_1_1Size2.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Size2**](structSR__MATH__NS_1_1Size2.md) | [**Size2**](#variable-size2)  <br> |
|  [**Size**](structSR__MATH__NS_1_1Size.md)&lt; T &gt; | [**h**](#variable-h)  <br> |
|  [**Size**](structSR__MATH__NS_1_1Size.md)&lt; T &gt; | [**height**](#variable-height)  <br> |
|  [**Size**](structSR__MATH__NS_1_1Size.md)&lt; T &gt; | [**w**](#variable-w)  <br> |
|  [**Size**](structSR__MATH__NS_1_1Size.md)&lt; T &gt; | [**width**](#variable-width)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**HasPercent**](#function-haspercent) () noexcept const<br> |
|  void | [**SetPixels**](#function-setpixels) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & size) noexcept<br> |
|   | [**Size2**](#function-size2) () noexcept<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**ToPixels**](#function-topixels-12) () noexcept const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**ToPixels**](#function-topixels-22) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & parentSize) noexcept const<br> |




























## Public Attributes Documentation




### variable Size2 

```C++
union SR_MATH_NS::Size2 SR_MATH_NS::Size2< T >;
```




<hr>



### variable h 

```C++
Size<T> SR_MATH_NS::Size2< T >::h;
```




<hr>



### variable height 

```C++
Size<T> SR_MATH_NS::Size2< T >::height;
```




<hr>



### variable w 

```C++
Size<T> SR_MATH_NS::Size2< T >::w;
```




<hr>



### variable width 

```C++
Size<T> SR_MATH_NS::Size2< T >::width;
```




<hr>
## Public Functions Documentation




### function HasPercent 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Size2::HasPercent () noexcept const
```




<hr>



### function SetPixels 

```C++
inline void SR_MATH_NS::Size2::SetPixels (
    const Vector2 < T > & size
) noexcept
```




<hr>



### function Size2 

```C++
inline SR_MATH_NS::Size2::Size2 () noexcept
```




<hr>



### function ToPixels [1/2]

```C++
inline SR_NODISCARD Vector2 < T > SR_MATH_NS::Size2::ToPixels () noexcept const
```




<hr>



### function ToPixels [2/2]

```C++
inline SR_NODISCARD Vector2 < T > SR_MATH_NS::Size2::ToPixels (
    const Vector2 < T > & parentSize
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Size.h`

