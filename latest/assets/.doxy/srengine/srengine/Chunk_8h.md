

# File Chunk.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**Chunk.h**](Chunk_8h.md)

[Go to the source code of this file](Chunk_8h_source.md)



* `#include <Utils/Math/Vector2.h>`
* `#include <Utils/Types/SharedPtr.h>`
* `#include <Utils/Types/DataStorage.h>`
* `#include <Utils/Types/Marshal.h>`
* `#include <Utils/World/Observer.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SRChunkAllocArgs**](Chunk_8h.md#define-srchunkallocargs)  `[**SR\_WORLD\_NS::Observer**](classSR__WORLD__NS_1_1Observer.md)\* observer, [**SR\_WORLD\_NS::Region**](classSR__WORLD__NS_1_1Region.md)\* region, const SR\_MATH\_NS::IVector3& position, const SR\_MATH\_NS::IVector2& size`<br> |
| define  | [**SRChunkAllocVArgs**](Chunk_8h.md#define-srchunkallocvargs)  `observer, region, position, size`<br> |

## Macro Definition Documentation





### define SRChunkAllocArgs 

```C++
#define SRChunkAllocArgs `SR_WORLD_NS::Observer * observer, SR_WORLD_NS::Region * region, const SR_MATH_NS::IVector3& position, const SR_MATH_NS::IVector2& size`
```




<hr>



### define SRChunkAllocVArgs 

```C++
#define SRChunkAllocVArgs `observer, region, position, size`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/World/Chunk.h`

