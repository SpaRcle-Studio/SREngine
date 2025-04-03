

# Struct SR\_MATH\_NS::Rect

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Rect**](structSR__MATH__NS_1_1Rect.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md) | [**Rect**](#variable-rect)  <br> |
|  T | [**h**](#variable-h)  <br> |
|  T | [**w**](#variable-w)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**wh**](#variable-wh)  <br> |
|  T | [**x**](#variable-x)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**xy**](#variable-xy)  <br> |
|  T | [**y**](#variable-y)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD constexpr T | [**Bottom**](#function-bottom) () noexcept const<br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains) (const [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & point) noexcept const<br> |
|  SR\_NODISCARD constexpr T | [**Height**](#function-height) () noexcept const<br> |
|  SR\_NODISCARD constexpr bool | [**IsInside**](#function-isinside) (const [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & point) noexcept const<br> |
|  SR\_NODISCARD constexpr T | [**Left**](#function-left) () noexcept const<br> |
|  constexpr | [**Rect**](#function-rect-15) (T \_x, T \_y, T \_w, T \_h) <br> |
|  constexpr | [**Rect**](#function-rect-25) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & position, const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & size) <br> |
|  constexpr | [**Rect**](#function-rect-35) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & position, T width, T height) <br> |
|  constexpr | [**Rect**](#function-rect-45) (T x, T y, const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & size) <br> |
|  constexpr | [**Rect**](#function-rect-55) () <br> |
|  SR\_NODISCARD constexpr T | [**Right**](#function-right) () noexcept const<br> |
|  constexpr void | [**SetBottom**](#function-setbottom) (const T & value) <br> |
|  constexpr void | [**SetLeft**](#function-setleft) (const T & value) <br> |
|  constexpr void | [**SetRight**](#function-setright) (const T & value) <br> |
|  constexpr void | [**SetTop**](#function-settop) (const T & value) <br> |
|  SR\_NODISCARD constexpr T | [**Top**](#function-top) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**WH**](#function-wh) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**WH0**](#function-wh0) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**WH1**](#function-wh1) () noexcept const<br> |
|  SR\_NODISCARD constexpr T | [**Width**](#function-width) () noexcept const<br> |
|  SR\_NODISCARD constexpr T | [**X**](#function-x) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**XY**](#function-xy) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XY0**](#function-xy0) () noexcept const<br> |
|  SR\_NODISCARD constexpr T | [**Y**](#function-y) () noexcept const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator) (const [**Rect**](structSR__MATH__NS_1_1Rect.md) & other) noexcept const<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator\***](#function-operator_1) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator\*=**](#function-operator_2) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator+**](#function-operator_3) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator+=**](#function-operator_4) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator-**](#function-operator_5) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator-=**](#function-operator_6) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator/**](#function-operator_7) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator/=**](#function-operator_8) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_9) (const [**Rect**](structSR__MATH__NS_1_1Rect.md) & other) noexcept const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md)&lt; Unit &gt; | [**FromTranslationAndScale**](#function-fromtranslationandscale) (const SR\_MATH\_NS::FVector2 & translation, const SR\_MATH\_NS::FVector2 & scale) <br> |


























## Public Attributes Documentation




### variable Rect 

```C++
union SR_MATH_NS::Rect SR_MATH_NS::Rect< T >;
```




<hr>



### variable h 

```C++
T SR_MATH_NS::Rect< T >::h;
```




<hr>



### variable w 

```C++
T SR_MATH_NS::Rect< T >::w;
```




<hr>



### variable wh 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Rect< T >::wh;
```




<hr>



### variable x 

```C++
T SR_MATH_NS::Rect< T >::x;
```




<hr>



### variable xy 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Rect< T >::xy;
```




<hr>



### variable y 

```C++
T SR_MATH_NS::Rect< T >::y;
```




<hr>
## Public Functions Documentation




### function Bottom 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Bottom () noexcept const
```




<hr>



### function Contains 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Rect::Contains (
    const SR_MATH_NS::Vector2 < T > & point
) noexcept const
```




<hr>



### function Height 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Height () noexcept const
```




<hr>



### function IsInside 

```C++
template<typename U>
inline SR_NODISCARD constexpr bool SR_MATH_NS::Rect::IsInside (
    const SR_MATH_NS::Vector2 < U > & point
) noexcept const
```




<hr>



### function Left 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Left () noexcept const
```




<hr>



### function Rect [1/5]

```C++
inline constexpr SR_MATH_NS::Rect::Rect (
    T _x,
    T _y,
    T _w,
    T _h
) 
```




<hr>



### function Rect [2/5]

```C++
inline constexpr SR_MATH_NS::Rect::Rect (
    const Vector2 < T > & position,
    const Vector2 < T > & size
) 
```




<hr>



### function Rect [3/5]

```C++
inline constexpr SR_MATH_NS::Rect::Rect (
    const Vector2 < T > & position,
    T width,
    T height
) 
```




<hr>



### function Rect [4/5]

```C++
inline constexpr SR_MATH_NS::Rect::Rect (
    T x,
    T y,
    const Vector2 < T > & size
) 
```




<hr>



### function Rect [5/5]

```C++
inline constexpr SR_MATH_NS::Rect::Rect () 
```




<hr>



### function Right 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Right () noexcept const
```




<hr>



### function SetBottom 

```C++
inline constexpr void SR_MATH_NS::Rect::SetBottom (
    const T & value
) 
```




<hr>



### function SetLeft 

```C++
inline constexpr void SR_MATH_NS::Rect::SetLeft (
    const T & value
) 
```




<hr>



### function SetRight 

```C++
inline constexpr void SR_MATH_NS::Rect::SetRight (
    const T & value
) 
```




<hr>



### function SetTop 

```C++
inline constexpr void SR_MATH_NS::Rect::SetTop (
    const T & value
) 
```




<hr>



### function Top 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Top () noexcept const
```




<hr>



### function WH 

```C++
inline SR_NODISCARD constexpr SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::WH () noexcept const
```




<hr>



### function WH0 

```C++
inline SR_NODISCARD constexpr SR_MATH_NS::Vector3 < T > SR_MATH_NS::Rect::WH0 () noexcept const
```




<hr>



### function WH1 

```C++
inline SR_NODISCARD constexpr SR_MATH_NS::Vector3 < T > SR_MATH_NS::Rect::WH1 () noexcept const
```




<hr>



### function Width 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Width () noexcept const
```




<hr>



### function X 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::X () noexcept const
```




<hr>



### function XY 

```C++
inline SR_NODISCARD constexpr SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::XY () noexcept const
```




<hr>



### function XY0 

```C++
inline SR_NODISCARD constexpr SR_MATH_NS::Vector3 < T > SR_MATH_NS::Rect::XY0 () noexcept const
```




<hr>



### function Y 

```C++
inline SR_NODISCARD constexpr T SR_MATH_NS::Rect::Y () noexcept const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Rect::operator!= (
    const Rect & other
) noexcept const
```




<hr>



### function operator\* 

```C++
inline SR_NODISCARD Rect SR_MATH_NS::Rect::operator* (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator\*= 

```C++
inline void SR_MATH_NS::Rect::operator*= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator+ 

```C++
inline SR_NODISCARD Rect SR_MATH_NS::Rect::operator+ (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator+= 

```C++
inline void SR_MATH_NS::Rect::operator+= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator- 

```C++
inline SR_NODISCARD Rect SR_MATH_NS::Rect::operator- (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator-= 

```C++
inline void SR_MATH_NS::Rect::operator-= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator/ 

```C++
inline SR_NODISCARD Rect SR_MATH_NS::Rect::operator/ (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator/= 

```C++
inline void SR_MATH_NS::Rect::operator/= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Rect::operator== (
    const Rect & other
) noexcept const
```




<hr>
## Public Static Functions Documentation




### function FromTranslationAndScale 

```C++
static SR_NODISCARD Rect < Unit > SR_MATH_NS::Rect::FromTranslationAndScale (
    const SR_MATH_NS::FVector2 & translation,
    const SR_MATH_NS::FVector2 & scale
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Rect.h`

