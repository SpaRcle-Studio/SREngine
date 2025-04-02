

# File Region.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**Region.h**](Region_8h.md)

[Go to the source code of this file](Region_8h_source.md)



* `#include <Utils/Math/Vector3.h>`
* `#include <Utils/World/Observer.h>`
* `#include <Utils/Resources/Xml.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Region**](classSR__WORLD__NS_1_1Region.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SRRegionAllocArgs**](Region_8h.md#define-srregionallocargs)  `[**SR\_WORLD\_NS::Observer**](classSR__WORLD__NS_1_1Observer.md)\* observer, uint32\_t width, const SR\_MATH\_NS::IVector2& chunkSize, const SR\_MATH\_NS::IVector3& position`<br> |
| define  | [**SRRegionAllocVArgs**](Region_8h.md#define-srregionallocvargs)  `observer, width, chunkSize, position`<br> |

## Macro Definition Documentation





### define SRRegionAllocArgs 

```C++
#define SRRegionAllocArgs `SR_WORLD_NS::Observer * observer, uint32_t width, const SR_MATH_NS::IVector2& chunkSize, const SR_MATH_NS::IVector3& position`
```




<hr>



### define SRRegionAllocVArgs 

```C++
#define SRRegionAllocVArgs `observer, width, chunkSize, position`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/Region.h`

