

# File BasePass.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**BasePass.h**](BasePass_8h.md)

[Go to the source code of this file](BasePass_8h_source.md)



* `#include <Utils/Common/NonCopyable.h>`
* `#include <Utils/Math/Vector2.h>`
* `#include <Utils/Types/Function.h>`
* `#include <Utils/Types/SafePointer.h>`
* `#include <Utils/Types/Time.h>`
* `#include <Utils/Resources/Xml.h>`
* `#include <Utils/Resources/ResourceContainer.h>`
* `#include <Utils/SRLM/LogicalNode.h>`
* `#include <Utils/SRLM/LogicalNodeManager.h>`
* `#include <Utils/SRLM/DataType.h>`
* `#include <Utils/SRLM/Utils.h>`
* `#include <Graphics/Memory/UBOManager.h>`
* `#include <Graphics/Memory/DescriptorManager.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) <br> |
| namespace | [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) <br> |
| class | [**StartPassNode**](classSR__GRAPH__NS_1_1StartPassNode.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_ALLOCATE\_RENDER\_PASS**](BasePass_8h.md#define-sr_allocate_render_pass) (passNode, pTechnique) `/* multi line expression */`<br> |
| define  | [**SR\_REGISTER\_RENDER\_PASS**](BasePass_8h.md#define-sr_register_render_pass) (name) `/* multi line expression */`<br>_TODO: переделать на встраивание в объявление класса_  |

## Macro Definition Documentation





### define SR\_ALLOCATE\_RENDER\_PASS 

```C++
#define SR_ALLOCATE_RENDER_PASS (
    passNode,
    pTechnique
) `/* multi line expression */`
```




<hr>



### define SR\_REGISTER\_RENDER\_PASS 

_TODO: переделать на встраивание в объявление класса_ 
```C++
#define SR_REGISTER_RENDER_PASS (
    name
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/BasePass.h`

