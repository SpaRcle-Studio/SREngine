

# File Chunk.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**World**](dir_646ea3957657c91e40c16f5ff19dad51.md) **>** [**Chunk.h**](Chunk_8h.md)

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
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/Chunk.h`

