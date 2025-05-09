

# Class SR\_MATH\_NS::FColor



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**FColor**](classSR__MATH__NS_1_1FColor.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**FColor**](#variable-fcolor)  <br> |
|  Unit | [**a**](#variable-a)  <br> |
|  Unit | [**b**](#variable-b)  <br> |
|  Unit | [**coord**](#variable-coord)   = `{ 0 }`<br> |
|  Unit | [**g**](#variable-g)  <br> |
|  Unit | [**r**](#variable-r)  <br> |
|  Unit | [**w**](#variable-w)  <br> |
|  Unit | [**x**](#variable-x)  <br> |
|  Unit | [**y**](#variable-y)  <br> |
|  Unit | [**z**](#variable-z)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FColor**](#function-fcolor-19) () <br> |
|   | [**FColor**](#function-fcolor-29) (Unit scalar) <br> |
|   | [**FColor**](#function-fcolor-39) (const glm::vec4 & vec4) <br> |
|   | [**FColor**](#function-fcolor-49) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; Unit &gt; & v) <br> |
|   | [**FColor**](#function-fcolor-59) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|   | [**FColor**](#function-fcolor-69) ([**FColor**](classSR__MATH__NS_1_1FColor.md) && color) <br> |
|   | [**FColor**](#function-fcolor-79) (double\_t \_x, double\_t \_y, double\_t \_z, double\_t \_w) <br> |
|   | [**FColor**](#function-fcolor-89) (float\_t \_x, float\_t \_y, float\_t \_z, float\_t \_w) <br> |
|   | [**FColor**](#function-fcolor-99) (int32\_t \_x, int32\_t \_y, int32\_t \_z, int32\_t \_w) <br> |
|  bool | [**operator!=**](#function-operator) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & v) const<br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator%=**](#function-operator_1) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & p\_v) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**operator\***](#function-operator_2) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & p\_v) const<br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator\*=**](#function-operator_3) (Unit p\_scalar) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator\*=**](#function-operator_4) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & p\_v) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**operator+**](#function-operator_5) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & v) const<br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**operator-**](#function-operator_6) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & p\_v) const<br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**operator/**](#function-operator_7) (const Unit & v) const<br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator/=**](#function-operator_8) (Unit p\_scalar) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator/=**](#function-operator_9) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & p\_v) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator=**](#function-operator_10) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator=**](#function-operator_11) ([**FColor**](classSR__MATH__NS_1_1FColor.md) && color) <br> |
|  bool | [**operator==**](#function-operator_12) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & v) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Alpha**](#function-alpha) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Black**](#function-black) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Blue**](#function-blue) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Cyan**](#function-cyan) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Green**](#function-green) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Magenta**](#function-magenta) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Red**](#function-red) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**White**](#function-white) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Yellow**](#function-yellow) () <br> |


























## Public Attributes Documentation




### variable FColor 

```C++
union SR_MATH_NS::FColor SR_MATH_NS::FColor;
```




<hr>



### variable a 

```C++
Unit SR_MATH_NS::FColor::a;
```




<hr>



### variable b 

```C++
Unit SR_MATH_NS::FColor::b;
```




<hr>



### variable coord 

```C++
Unit SR_MATH_NS::FColor::coord[4];
```




<hr>



### variable g 

```C++
Unit SR_MATH_NS::FColor::g;
```




<hr>



### variable r 

```C++
Unit SR_MATH_NS::FColor::r;
```




<hr>



### variable w 

```C++
Unit SR_MATH_NS::FColor::w;
```




<hr>



### variable x 

```C++
Unit SR_MATH_NS::FColor::x;
```




<hr>



### variable y 

```C++
Unit SR_MATH_NS::FColor::y;
```




<hr>



### variable z 

```C++
Unit SR_MATH_NS::FColor::z;
```




<hr>
## Public Functions Documentation




### function FColor [1/9]

```C++
SR_MATH_NS::FColor::FColor () 
```




<hr>



### function FColor [2/9]

```C++
SR_MATH_NS::FColor::FColor (
    Unit scalar
) 
```




<hr>



### function FColor [3/9]

```C++
SR_MATH_NS::FColor::FColor (
    const glm::vec4 & vec4
) 
```




<hr>



### function FColor [4/9]

```C++
SR_MATH_NS::FColor::FColor (
    const Vector4 < Unit > & v
) 
```




<hr>



### function FColor [5/9]

```C++
SR_MATH_NS::FColor::FColor (
    const FColor & color
) 
```




<hr>



### function FColor [6/9]

```C++
SR_MATH_NS::FColor::FColor (
    FColor && color
) 
```




<hr>



### function FColor [7/9]

```C++
SR_MATH_NS::FColor::FColor (
    double_t _x,
    double_t _y,
    double_t _z,
    double_t _w
) 
```




<hr>



### function FColor [8/9]

```C++
SR_MATH_NS::FColor::FColor (
    float_t _x,
    float_t _y,
    float_t _z,
    float_t _w
) 
```




<hr>



### function FColor [9/9]

```C++
SR_MATH_NS::FColor::FColor (
    int32_t _x,
    int32_t _y,
    int32_t _z,
    int32_t _w
) 
```




<hr>



### function operator!= 

```C++
bool SR_MATH_NS::FColor::operator!= (
    const FColor & v
) const
```




<hr>



### function operator%= 

```C++
FColor & SR_MATH_NS::FColor::operator%= (
    const FColor & p_v
) 
```




<hr>



### function operator\* 

```C++
FColor SR_MATH_NS::FColor::operator* (
    const FColor & p_v
) const
```




<hr>



### function operator\*= 

```C++
FColor & SR_MATH_NS::FColor::operator*= (
    Unit p_scalar
) 
```




<hr>



### function operator\*= 

```C++
FColor & SR_MATH_NS::FColor::operator*= (
    const FColor & p_v
) 
```




<hr>



### function operator+ 

```C++
FColor SR_MATH_NS::FColor::operator+ (
    const FColor & v
) const
```




<hr>



### function operator- 

```C++
FColor SR_MATH_NS::FColor::operator- (
    const FColor & p_v
) const
```




<hr>



### function operator/ 

```C++
FColor SR_MATH_NS::FColor::operator/ (
    const Unit & v
) const
```




<hr>



### function operator/= 

```C++
FColor & SR_MATH_NS::FColor::operator/= (
    Unit p_scalar
) 
```




<hr>



### function operator/= 

```C++
FColor & SR_MATH_NS::FColor::operator/= (
    const FColor & p_v
) 
```




<hr>



### function operator= 

```C++
FColor & SR_MATH_NS::FColor::operator= (
    const FColor & color
) 
```




<hr>



### function operator= 

```C++
FColor & SR_MATH_NS::FColor::operator= (
    FColor && color
) 
```




<hr>



### function operator== 

```C++
bool SR_MATH_NS::FColor::operator== (
    const FColor & v
) const
```




<hr>
## Public Static Functions Documentation




### function Alpha 

```C++
static FColor SR_MATH_NS::FColor::Alpha () 
```




<hr>



### function Black 

```C++
static FColor SR_MATH_NS::FColor::Black () 
```




<hr>



### function Blue 

```C++
static FColor SR_MATH_NS::FColor::Blue () 
```




<hr>



### function Cyan 

```C++
static FColor SR_MATH_NS::FColor::Cyan () 
```




<hr>



### function Green 

```C++
static FColor SR_MATH_NS::FColor::Green () 
```




<hr>



### function Magenta 

```C++
static FColor SR_MATH_NS::FColor::Magenta () 
```




<hr>



### function Red 

```C++
static FColor SR_MATH_NS::FColor::Red () 
```




<hr>



### function White 

```C++
static FColor SR_MATH_NS::FColor::White () 
```




<hr>



### function Yellow 

```C++
static FColor SR_MATH_NS::FColor::Yellow () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector4.h`

