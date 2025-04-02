

# File BasePass.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**BasePass.h**](BasePass_8h.md)

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
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pass/BasePass.h`

