

# File Region.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**Region.h**](Region_8h.md)

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
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/World/Region.h`

