

# File RenderScene.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderScene.h**](RenderScene_8h.md)

[Go to the source code of this file](RenderScene_8h_source.md)



* `#include <Graphics/macros.h>`
* `#include <Utils/Common/NonCopyable.h>`
* `#include <Utils/Types/SafePointer.h>`
* `#include <Utils/Types/SafeVariable.h>`
* `#include <Graphics/Render/MeshCluster.h>`
* `#include <Graphics/Render/RenderStrategy.h>`
* `#include <Graphics/Render/FlatCluster.h>`
* `#include <Graphics/Render/SortedMeshQueue.h>`
* `#include <Graphics/GUI/WidgetManager.h>`
* `#include <Graphics/Pass/RenderTechniqueQueue.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) <br> |
| namespace | [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) <br> |
| namespace | [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) <br> |
| namespace | [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) <br> |
| struct | [**CameraInfo**](structSR__GRAPH__NS_1_1RenderScene_1_1CameraInfo.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_RENDER\_TECHNIQUES\_CALL**](RenderScene_8h.md#define-sr_render_techniques_call) (FunctionName, ...) `/* multi line expression */`<br> |
| define  | [**SR\_RENDER\_TECHNIQUES\_RETURN\_CALL**](RenderScene_8h.md#define-sr_render_techniques_return_call) (FunctionName, ...) `/* multi line expression */`<br> |

## Macro Definition Documentation





### define SR\_RENDER\_TECHNIQUES\_CALL 

```C++
#define SR_RENDER_TECHNIQUES_CALL (
    FunctionName,
    ...
) `/* multi line expression */`
```




<hr>



### define SR\_RENDER\_TECHNIQUES\_RETURN\_CALL 

```C++
#define SR_RENDER_TECHNIQUES_RETURN_CALL (
    FunctionName,
    ...
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderScene.h`

