

# File MD5Hash.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Tools**](dir_04907cd073aeacf0a44a00b3a87fc81c.md) **>** [**MD5Hash.h**](MD5Hash_8h.md)

[Go to the source code of this file](MD5Hash_8h_source.md)



* `#include <Utils/stdInclude.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**EvoScript**](namespaceEvoScript.md) <br> |
| namespace | [**Tools**](namespaceEvoScript_1_1Tools.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**MD5**](classEvoScript_1_1Tools_1_1MD5.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**F**](MD5Hash_8h.md#define-f) (x, y, z) `(((x) & (y)) \| ((~x) & (z)))`<br> |
| define  | [**FF**](MD5Hash_8h.md#define-ff) (a, b, c, d, x, s, ac) `/* multi line expression */`<br> |
| define  | [**G**](MD5Hash_8h.md#define-g) (x, y, z) `(((x) & (z)) \| ((y) & (~z)))`<br> |
| define  | [**GG**](MD5Hash_8h.md#define-gg) (a, b, c, d, x, s, ac) `/* multi line expression */`<br> |
| define  | [**H**](MD5Hash_8h.md#define-h) (x, y, z) `((x) ^ (y) ^ (z))`<br> |
| define  | [**HH**](MD5Hash_8h.md#define-hh) (a, b, c, d, x, s, ac) `/* multi line expression */`<br> |
| define  | [**I**](MD5Hash_8h.md#define-i) (x, y, z) `((y) ^ ((x) \| (~z)))`<br> |
| define  | [**II**](MD5Hash_8h.md#define-ii) (a, b, c, d, x, s, ac) `/* multi line expression */`<br> |
| define  | [**ROTATE\_LEFT**](MD5Hash_8h.md#define-rotate_left) (x, n) `(((x) &lt;&lt; (n)) \| ((x) &gt;&gt; (32-(n))))`<br> |
| define  | [**S11**](MD5Hash_8h.md#define-s11)  `7`<br> |
| define  | [**S12**](MD5Hash_8h.md#define-s12)  `12`<br> |
| define  | [**S13**](MD5Hash_8h.md#define-s13)  `17`<br> |
| define  | [**S14**](MD5Hash_8h.md#define-s14)  `22`<br> |
| define  | [**S21**](MD5Hash_8h.md#define-s21)  `5`<br> |
| define  | [**S22**](MD5Hash_8h.md#define-s22)  `9`<br> |
| define  | [**S23**](MD5Hash_8h.md#define-s23)  `14`<br> |
| define  | [**S24**](MD5Hash_8h.md#define-s24)  `20`<br> |
| define  | [**S31**](MD5Hash_8h.md#define-s31)  `4`<br> |
| define  | [**S32**](MD5Hash_8h.md#define-s32)  `11`<br> |
| define  | [**S33**](MD5Hash_8h.md#define-s33)  `16`<br> |
| define  | [**S34**](MD5Hash_8h.md#define-s34)  `23`<br> |
| define  | [**S41**](MD5Hash_8h.md#define-s41)  `6`<br> |
| define  | [**S42**](MD5Hash_8h.md#define-s42)  `10`<br> |
| define  | [**S43**](MD5Hash_8h.md#define-s43)  `15`<br> |
| define  | [**S44**](MD5Hash_8h.md#define-s44)  `21`<br> |

## Macro Definition Documentation





### define F 

```C++
#define F (
    x,
    y,
    z
) `(((x) & (y)) | ((~x) & (z)))`
```




<hr>



### define FF 

```C++
#define FF (
    a,
    b,
    c,
    d,
    x,
    s,
    ac
) `/* multi line expression */`
```




<hr>



### define G 

```C++
#define G (
    x,
    y,
    z
) `(((x) & (z)) | ((y) & (~z)))`
```




<hr>



### define GG 

```C++
#define GG (
    a,
    b,
    c,
    d,
    x,
    s,
    ac
) `/* multi line expression */`
```




<hr>



### define H 

```C++
#define H (
    x,
    y,
    z
) `((x) ^ (y) ^ (z))`
```




<hr>



### define HH 

```C++
#define HH (
    a,
    b,
    c,
    d,
    x,
    s,
    ac
) `/* multi line expression */`
```




<hr>



### define I 

```C++
#define I (
    x,
    y,
    z
) `((y) ^ ((x) | (~z)))`
```




<hr>



### define II 

```C++
#define II (
    a,
    b,
    c,
    d,
    x,
    s,
    ac
) `/* multi line expression */`
```




<hr>



### define ROTATE\_LEFT 

```C++
#define ROTATE_LEFT (
    x,
    n
) `(((x) << (n)) | ((x) >> (32-(n))))`
```




<hr>



### define S11 

```C++
#define S11 `7`
```




<hr>



### define S12 

```C++
#define S12 `12`
```




<hr>



### define S13 

```C++
#define S13 `17`
```




<hr>



### define S14 

```C++
#define S14 `22`
```




<hr>



### define S21 

```C++
#define S21 `5`
```




<hr>



### define S22 

```C++
#define S22 `9`
```




<hr>



### define S23 

```C++
#define S23 `14`
```




<hr>



### define S24 

```C++
#define S24 `20`
```




<hr>



### define S31 

```C++
#define S31 `4`
```




<hr>



### define S32 

```C++
#define S32 `11`
```




<hr>



### define S33 

```C++
#define S33 `16`
```




<hr>



### define S34 

```C++
#define S34 `23`
```




<hr>



### define S41 

```C++
#define S41 `6`
```




<hr>



### define S42 

```C++
#define S42 `10`
```




<hr>



### define S43 

```C++
#define S43 `15`
```




<hr>



### define S44 

```C++
#define S44 `21`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Old/Tools/MD5Hash.h`

