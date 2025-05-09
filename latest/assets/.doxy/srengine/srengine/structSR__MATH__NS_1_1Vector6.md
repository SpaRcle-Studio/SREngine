

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
|   | [**Vector6**](#function-vector6-17) () <br> |
|   | [**Vector6**](#function-vector6-27) (T \_x, T \_y, T \_z, T \_w, T \_v, T \_u) <br> |
|   | [**Vector6**](#function-vector6-37) (const [**Vector6**](structSR__MATH__NS_1_1Vector6.md) & p\_v) <br> |
|   | [**Vector6**](#function-vector6-47) ([**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; vec3d1, [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; vec3d2) <br> |
|   | [**Vector6**](#function-vector6-57) (T scalar) <br> |
|   | [**Vector6**](#function-vector6-67) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec) <br> |
|   | [**Vector6**](#function-vector6-77) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec1, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec2) <br> |
|  bool | [**operator!=**](#function-operator) (const [**Vector6**](structSR__MATH__NS_1_1Vector6.md) & p\_v) const<br> |
|  bool | [**operator==**](#function-operator_1) (const [**Vector6**](structSR__MATH__NS_1_1Vector6.md) & p\_v) const<br> |




























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




### function Vector6 [1/7]

```C++
SR_MATH_NS::Vector6::Vector6 () 
```




<hr>



### function Vector6 [2/7]

```C++
SR_MATH_NS::Vector6::Vector6 (
    T _x,
    T _y,
    T _z,
    T _w,
    T _v,
    T _u
) 
```




<hr>



### function Vector6 [3/7]

```C++
SR_MATH_NS::Vector6::Vector6 (
    const Vector6 & p_v
) 
```




<hr>



### function Vector6 [4/7]

```C++
SR_MATH_NS::Vector6::Vector6 (
    SR_MATH_NS::Vector3 < T > vec3d1,
    SR_MATH_NS::Vector3 < T > vec3d2
) 
```




<hr>



### function Vector6 [5/7]

```C++
SR_MATH_NS::Vector6::Vector6 (
    T scalar
) 
```




<hr>



### function Vector6 [6/7]

```C++
template<typename U>
explicit SR_MATH_NS::Vector6::Vector6 (
    const Vector3 < U > & vec
) 
```




<hr>



### function Vector6 [7/7]

```C++
template<typename U>
explicit SR_MATH_NS::Vector6::Vector6 (
    const Vector3 < U > & vec1,
    const Vector3 < U > & vec2
) 
```




<hr>



### function operator!= 

```C++
bool SR_MATH_NS::Vector6::operator!= (
    const Vector6 & p_v
) const
```




<hr>



### function operator== 

```C++
bool SR_MATH_NS::Vector6::operator== (
    const Vector6 & p_v
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector6.h`

