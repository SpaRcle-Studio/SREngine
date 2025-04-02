

# Struct SR\_MATH\_NS::Vector6

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Vector6**](structSR__MATH__NS_1_1Vector6.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Vector6**](structSR__MATH__NS_1_1Vector6.md) | [**Vector6**](#variable-vector6)  <br> |
|  T | [**coord**](#variable-coord)   = `{ 0 }`<br> |
|  T | [**u**](#variable-u)  <br> |
|  T | [**v**](#variable-v)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**vec2d1**](#variable-vec2d1)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**vec2d2**](#variable-vec2d2)  <br> |
|  [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**vec2d3**](#variable-vec2d3)  <br> |
|  [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**vec3d1**](#variable-vec3d1)  <br> |
|  [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**vec3d2**](#variable-vec3d2)  <br> |
|  T | [**w**](#variable-w)  <br> |
|  T | [**x**](#variable-x)  <br> |
|  T | [**y**](#variable-y)  <br> |
|  T | [**z**](#variable-z)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_FAST\_CONSTRUCTOR | [**Vector6**](#function-vector6-16) () <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector6**](#function-vector6-26) ([**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; vec3d1, [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; vec3d2) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector6**](#function-vector6-36) (T scalar) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector6**](#function-vector6-46) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector6**](#function-vector6-56) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec1, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec2) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector6**](#function-vector6-66) (T \_x, T \_y, T \_z, T \_w, T \_v, T \_u) <br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator) (const [**Vector6**](structSR__MATH__NS_1_1Vector6.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_1) (const [**Vector6**](structSR__MATH__NS_1_1Vector6.md) & p\_v) const<br> |




























## Public Attributes Documentation




### variable Vector6 

```C++
union SR_MATH_NS::Vector6 SR_MATH_NS::Vector6< T >;
```




<hr>



### variable coord 

```C++
T SR_MATH_NS::Vector6< T >::coord[6];
```




<hr>



### variable u 

```C++
T SR_MATH_NS::Vector6< T >::u;
```




<hr>



### variable v 

```C++
T SR_MATH_NS::Vector6< T >::v;
```




<hr>



### variable vec2d1 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Vector6< T >::vec2d1;
```




<hr>



### variable vec2d2 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Vector6< T >::vec2d2;
```




<hr>



### variable vec2d3 

```C++
SR_MATH_NS::Vector2<T> SR_MATH_NS::Vector6< T >::vec2d3;
```




<hr>



### variable vec3d1 

```C++
SR_MATH_NS::Vector3<T> SR_MATH_NS::Vector6< T >::vec3d1;
```




<hr>



### variable vec3d2 

```C++
SR_MATH_NS::Vector3<T> SR_MATH_NS::Vector6< T >::vec3d2;
```




<hr>



### variable w 

```C++
T SR_MATH_NS::Vector6< T >::w;
```




<hr>



### variable x 

```C++
T SR_MATH_NS::Vector6< T >::x;
```




<hr>



### variable y 

```C++
T SR_MATH_NS::Vector6< T >::y;
```




<hr>



### variable z 

```C++
T SR_MATH_NS::Vector6< T >::z;
```




<hr>
## Public Functions Documentation




### function Vector6 [1/6]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector6::Vector6 () 
```




<hr>



### function Vector6 [2/6]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector6::Vector6 (
    SR_MATH_NS::Vector3 < T > vec3d1,
    SR_MATH_NS::Vector3 < T > vec3d2
) 
```




<hr>



### function Vector6 [3/6]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector6::Vector6 (
    T scalar
) 
```




<hr>



### function Vector6 [4/6]

```C++
template<typename U>
inline explicit SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector6::Vector6 (
    const Vector3 < U > & vec
) 
```




<hr>



### function Vector6 [5/6]

```C++
template<typename U>
inline explicit SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector6::Vector6 (
    const Vector3 < U > & vec1,
    const Vector3 < U > & vec2
) 
```




<hr>



### function Vector6 [6/6]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector6::Vector6 (
    T _x,
    T _y,
    T _z,
    T _w,
    T _v,
    T _u
) 
```




<hr>



### function operator!= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector6::operator!= (
    const Vector6 & p_v
) const
```




<hr>



### function operator== 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector6::operator== (
    const Vector6 & p_v
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector6.h`

