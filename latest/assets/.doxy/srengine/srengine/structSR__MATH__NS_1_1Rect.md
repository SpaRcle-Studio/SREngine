

# Struct SR\_MATH\_NS::Rect

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Rect**](structSR__MATH__NS_1_1Rect.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md) | [**Rect**](#variable-rect)  <br> |
|  T | [**bottom**](#variable-bottom)  <br> |
|  T | [**h**](#variable-h)  <br> |
|  T | [**left**](#variable-left)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**position**](#variable-position)  <br> |
|  T | [**right**](#variable-right)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**size**](#variable-size)  <br> |
|  T | [**top**](#variable-top)  <br> |
|  T | [**w**](#variable-w)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**wh**](#variable-wh)  <br> |
|  T | [**x**](#variable-x)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**xy**](#variable-xy)  <br> |
|  T | [**y**](#variable-y)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD T | [**Bottom**](#function-bottom) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**Center**](#function-center) () noexcept const<br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains) (const [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & point) noexcept const<br> |
|  SR\_NODISCARD T | [**Height**](#function-height) () noexcept const<br> |
|  SR\_NODISCARD T | [**Horizontal**](#function-horizontal) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsInside**](#function-isinside) (const [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & point) noexcept const<br> |
|  SR\_NODISCARD T | [**Left**](#function-left) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**LeftRight**](#function-leftright) () noexcept const<br> |
|   | [**Rect**](#function-rect-15) (T \_x, T \_y, T \_w, T \_h) <br>_left, top, right, bottom_  |
|   | [**Rect**](#function-rect-25) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & position, const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & size) <br> |
|   | [**Rect**](#function-rect-35) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & position, T width, T height) <br> |
|   | [**Rect**](#function-rect-45) (T x, T y, const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; & size) <br> |
|   | [**Rect**](#function-rect-55) () <br> |
|  SR\_NODISCARD T | [**Right**](#function-right) () noexcept const<br> |
|  void | [**SetBottom**](#function-setbottom) (const T & value) <br> |
|  void | [**SetLeft**](#function-setleft) (const T & value) <br>_============================================== Rect&lt;T&gt; =========================================================_  |
|  void | [**SetRight**](#function-setright) (const T & value) <br> |
|  void | [**SetTop**](#function-settop) (const T & value) <br> |
|  void | [**Shrink**](#function-shrink-12) (const [**Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & margin) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; | [**Shrink**](#function-shrink-22) (const [**Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & margin) noexcept const<br> |
|  SR\_NODISCARD T | [**Top**](#function-top) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**TopBottom**](#function-topbottom) () noexcept const<br> |
|  SR\_NODISCARD T | [**Vertical**](#function-vertical) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**WH**](#function-wh) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**WH0**](#function-wh0) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**WH1**](#function-wh1) () noexcept const<br> |
|  SR\_NODISCARD T | [**Width**](#function-width) () noexcept const<br> |
|  SR\_NODISCARD T | [**X**](#function-x) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**XY**](#function-xy) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XY0**](#function-xy0) () noexcept const<br> |
|  SR\_NODISCARD T | [**Y**](#function-y) () noexcept const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator) (const [**Rect**](structSR__MATH__NS_1_1Rect.md) & other) noexcept const<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator\***](#function-operator_1) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator\*=**](#function-operator_2) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator+**](#function-operator_3) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator+=**](#function-operator_4) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator-**](#function-operator-) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator-=**](#function-operator-_1) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD [**Rect**](structSR__MATH__NS_1_1Rect.md) | [**operator/**](#function-operator_5) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept const<br> |
|  void | [**operator/=**](#function-operator_6) (const [**SR\_MATH\_NS::Rect**](structSR__MATH__NS_1_1Rect.md)&lt; T &gt; & other) noexcept<br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_7) (const [**Rect**](structSR__MATH__NS_1_1Rect.md) & other) noexcept const<br> |


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



### variable bottom 

```C++
T SR_MATH_NS::Rect< T >::bottom;
```




<hr>



### variable h 

```C++
T SR_MATH_NS::Rect< T >::h;
```




<hr>



### variable left 

```C++
T SR_MATH_NS::Rect< T >::left;
```




<hr>



### variable position 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Rect< T >::position;
```




<hr>



### variable right 

```C++
T SR_MATH_NS::Rect< T >::right;
```




<hr>



### variable size 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Rect< T >::size;
```




<hr>



### variable top 

```C++
T SR_MATH_NS::Rect< T >::top;
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
SR_NODISCARD T SR_MATH_NS::Rect::Bottom () noexcept const
```




<hr>



### function Center 

```C++
SR_NODISCARD SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::Center () noexcept const
```




<hr>



### function Contains 

```C++
SR_NODISCARD bool SR_MATH_NS::Rect::Contains (
    const SR_MATH_NS::Vector2 < T > & point
) noexcept const
```




<hr>



### function Height 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Height () noexcept const
```




<hr>



### function Horizontal 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Horizontal () noexcept const
```




<hr>



### function IsInside 

```C++
template<typename U>
SR_NODISCARD bool SR_MATH_NS::Rect::IsInside (
    const SR_MATH_NS::Vector2 < U > & point
) noexcept const
```




<hr>



### function Left 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Left () noexcept const
```




<hr>



### function LeftRight 

```C++
SR_NODISCARD SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::LeftRight () noexcept const
```




<hr>



### function Rect [1/5]

_left, top, right, bottom_ 
```C++
SR_MATH_NS::Rect::Rect (
    T _x,
    T _y,
    T _w,
    T _h
) 
```




<hr>



### function Rect [2/5]

```C++
SR_MATH_NS::Rect::Rect (
    const Vector2 < T > & position,
    const Vector2 < T > & size
) 
```




<hr>



### function Rect [3/5]

```C++
SR_MATH_NS::Rect::Rect (
    const Vector2 < T > & position,
    T width,
    T height
) 
```




<hr>



### function Rect [4/5]

```C++
SR_MATH_NS::Rect::Rect (
    T x,
    T y,
    const Vector2 < T > & size
) 
```




<hr>



### function Rect [5/5]

```C++
SR_MATH_NS::Rect::Rect () 
```




<hr>



### function Right 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Right () noexcept const
```




<hr>



### function SetBottom 

```C++
void SR_MATH_NS::Rect::SetBottom (
    const T & value
) 
```




<hr>



### function SetLeft 

_============================================== Rect&lt;T&gt; =========================================================_ 
```C++
void SR_MATH_NS::Rect::SetLeft (
    const T & value
) 
```




<hr>



### function SetRight 

```C++
void SR_MATH_NS::Rect::SetRight (
    const T & value
) 
```




<hr>



### function SetTop 

```C++
void SR_MATH_NS::Rect::SetTop (
    const T & value
) 
```




<hr>



### function Shrink [1/2]

```C++
void SR_MATH_NS::Rect::Shrink (
    const Rect < T > & margin
) noexcept
```




<hr>



### function Shrink [2/2]

```C++
SR_NODISCARD Rect < T > SR_MATH_NS::Rect::Shrink (
    const Rect < T > & margin
) noexcept const
```




<hr>



### function Top 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Top () noexcept const
```




<hr>



### function TopBottom 

```C++
SR_NODISCARD SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::TopBottom () noexcept const
```




<hr>



### function Vertical 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Vertical () noexcept const
```




<hr>



### function WH 

```C++
SR_NODISCARD SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::WH () noexcept const
```




<hr>



### function WH0 

```C++
SR_NODISCARD SR_MATH_NS::Vector3 < T > SR_MATH_NS::Rect::WH0 () noexcept const
```




<hr>



### function WH1 

```C++
SR_NODISCARD SR_MATH_NS::Vector3 < T > SR_MATH_NS::Rect::WH1 () noexcept const
```




<hr>



### function Width 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Width () noexcept const
```




<hr>



### function X 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::X () noexcept const
```




<hr>



### function XY 

```C++
SR_NODISCARD SR_MATH_NS::Vector2 < T > SR_MATH_NS::Rect::XY () noexcept const
```




<hr>



### function XY0 

```C++
SR_NODISCARD SR_MATH_NS::Vector3 < T > SR_MATH_NS::Rect::XY0 () noexcept const
```




<hr>



### function Y 

```C++
SR_NODISCARD T SR_MATH_NS::Rect::Y () noexcept const
```




<hr>



### function operator!= 

```C++
SR_NODISCARD bool SR_MATH_NS::Rect::operator!= (
    const Rect & other
) noexcept const
```




<hr>



### function operator\* 

```C++
SR_NODISCARD Rect SR_MATH_NS::Rect::operator* (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator\*= 

```C++
void SR_MATH_NS::Rect::operator*= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator+ 

```C++
SR_NODISCARD Rect SR_MATH_NS::Rect::operator+ (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator+= 

```C++
void SR_MATH_NS::Rect::operator+= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator- 

```C++
SR_NODISCARD Rect SR_MATH_NS::Rect::operator- (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator-= 

```C++
void SR_MATH_NS::Rect::operator-= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator/ 

```C++
SR_NODISCARD Rect SR_MATH_NS::Rect::operator/ (
    const SR_MATH_NS::Rect < T > & other
) noexcept const
```




<hr>



### function operator/= 

```C++
void SR_MATH_NS::Rect::operator/= (
    const SR_MATH_NS::Rect < T > & other
) noexcept
```




<hr>



### function operator== 

```C++
SR_NODISCARD bool SR_MATH_NS::Rect::operator== (
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
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Math/Rect.h`

