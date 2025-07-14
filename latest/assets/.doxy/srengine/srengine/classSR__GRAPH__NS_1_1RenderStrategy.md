

# Class SR\_GRAPH\_NS::RenderStrategy



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md)



[More...](#detailed-description)

* `#include <RenderStrategy.h>`



Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddError**](#function-adderror) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) error) <br> |
|  void | [**AddProblemMesh**](#function-addproblemmesh) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh) <br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; ReturnType &gt; | [**BuildQueue**](#function-buildqueue-12) ([**MeshDrawerPass**](classSR__GRAPH__NS_1_1MeshDrawerPass.md) \* pDrawer) <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; ReturnType &gt; | [**BuildQueue**](#function-buildqueue-22) ([**MeshDrawerPass**](classSR__GRAPH__NS_1_1MeshDrawerPass.md) \* pDrawer) <br> |
|  void | [**ClearErrors**](#function-clearerrors) () <br> |
|  void | [**ForEachMesh**](#function-foreachmesh) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(MeshPtr)&gt; & callback) const<br> |
|  SR\_NODISCARD const std::set&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetErrors**](#function-geterrors) () noexcept const<br> |
|  SR\_NODISCARD const std::set&lt; [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* &gt; & | [**GetProblemMeshes**](#function-getproblemmeshes) () noexcept const<br> |
|  SR\_NODISCARD [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**GetRenderContext**](#function-getrendercontext) () const<br> |
|  SR\_NODISCARD [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD bool | [**IsDebugModeEnabled**](#function-isdebugmodeenabled) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsNeedCheckMeshActivity**](#function-isneedcheckmeshactivity) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsUniformsDirty**](#function-isuniformsdirty) () noexcept const<br> |
|  void | [**MarkUniformsDirty**](#function-markuniformsdirty) () <br> |
|  void | [**OnResourceReloaded**](#function-onresourcereloaded) (const SR\_UTILS\_NS::IResource::Ptr & pResource) const<br> |
|  void | [**Prepare**](#function-prepare) () <br> |
|  void | [**ReRegisterMesh**](#function-reregistermesh) (const [**MeshRegistrationInfo**](structSR__GRAPH__NS_1_1MeshRegistrationInfo.md) & info) <br> |
|  void | [**RegisterMesh**](#function-registermesh-12) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh) <br> |
|  void | [**RemoveQueue**](#function-removequeue) ([**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* pQueue) <br> |
|   | [**RenderStrategy**](#function-renderstrategy) ([**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* pRenderScene) <br> |
|  void | [**SetDebugMode**](#function-setdebugmode) (bool value) <br> |
|  bool | [**UnRegisterMesh**](#function-unregistermesh-12) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh) <br> |
|   | [**~RenderStrategy**](#function-renderstrategy) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Detailed Description




 build queue:


LayerRenderStage PriorityRenderStage MaterialRenderStage VBORenderStage MeshRenderStage


render queue:


for add/remove use lower\_bound to find shader


shader 0x0021 shader 0x2362 shader 0x1132


struct [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) { std::vector&lt;std::pair&lt;Shader\*, &gt; shaders; };
 


    
## Public Functions Documentation




### function AddError 

```C++
inline void SR_GRAPH_NS::RenderStrategy::AddError (
    SR_UTILS_NS::StringAtom error
) 
```




<hr>



### function AddProblemMesh 

```C++
inline void SR_GRAPH_NS::RenderStrategy::AddProblemMesh (
    SR_GTYPES_NS::Mesh * pMesh
) 
```




<hr>



### function BuildQueue [1/2]

```C++
template<class QueueType, class ReturnType>
SR_NODISCARD SR_HTYPES_NS::SharedPtr < ReturnType > SR_GRAPH_NS::RenderStrategy::BuildQueue (
    MeshDrawerPass * pDrawer
) 
```




<hr>



### function BuildQueue [2/2]

```C++
template<class QueueType, class ReturnType>
SR_HTYPES_NS::SharedPtr < ReturnType > SR_GRAPH_NS::RenderStrategy::BuildQueue (
    MeshDrawerPass * pDrawer
) 
```




<hr>



### function ClearErrors 

```C++
void SR_GRAPH_NS::RenderStrategy::ClearErrors () 
```




<hr>



### function ForEachMesh 

```C++
void SR_GRAPH_NS::RenderStrategy::ForEachMesh (
    const SR_HTYPES_NS::Function < void(MeshPtr)> & callback
) const
```




<hr>



### function GetErrors 

```C++
inline SR_NODISCARD const std::set< SR_UTILS_NS::StringAtom > & SR_GRAPH_NS::RenderStrategy::GetErrors () noexcept const
```




<hr>



### function GetProblemMeshes 

```C++
inline SR_NODISCARD const std::set< SR_GTYPES_NS::Mesh * > & SR_GRAPH_NS::RenderStrategy::GetProblemMeshes () noexcept const
```




<hr>



### function GetRenderContext 

```C++
SR_NODISCARD RenderContext * SR_GRAPH_NS::RenderStrategy::GetRenderContext () const
```




<hr>



### function GetRenderScene 

```C++
inline SR_NODISCARD RenderScene * SR_GRAPH_NS::RenderStrategy::GetRenderScene () const
```




<hr>



### function IsDebugModeEnabled 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::RenderStrategy::IsDebugModeEnabled () noexcept const
```




<hr>



### function IsNeedCheckMeshActivity 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::RenderStrategy::IsNeedCheckMeshActivity () noexcept const
```




<hr>



### function IsUniformsDirty 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::RenderStrategy::IsUniformsDirty () noexcept const
```




<hr>



### function MarkUniformsDirty 

```C++
inline void SR_GRAPH_NS::RenderStrategy::MarkUniformsDirty () 
```




<hr>



### function OnResourceReloaded 

```C++
void SR_GRAPH_NS::RenderStrategy::OnResourceReloaded (
    const SR_UTILS_NS::IResource::Ptr & pResource
) const
```




<hr>



### function Prepare 

```C++
void SR_GRAPH_NS::RenderStrategy::Prepare () 
```




<hr>



### function ReRegisterMesh 

```C++
void SR_GRAPH_NS::RenderStrategy::ReRegisterMesh (
    const MeshRegistrationInfo & info
) 
```




<hr>



### function RegisterMesh [1/2]

```C++
void SR_GRAPH_NS::RenderStrategy::RegisterMesh (
    SR_GTYPES_NS::Mesh * pMesh
) 
```




<hr>



### function RemoveQueue 

```C++
void SR_GRAPH_NS::RenderStrategy::RemoveQueue (
    RenderQueue * pQueue
) 
```




<hr>



### function RenderStrategy 

```C++
explicit SR_GRAPH_NS::RenderStrategy::RenderStrategy (
    RenderScene * pRenderScene
) 
```




<hr>



### function SetDebugMode 

```C++
void SR_GRAPH_NS::RenderStrategy::SetDebugMode (
    bool value
) 
```




<hr>



### function UnRegisterMesh [1/2]

```C++
bool SR_GRAPH_NS::RenderStrategy::UnRegisterMesh (
    SR_GTYPES_NS::Mesh * pMesh
) 
```




<hr>



### function ~RenderStrategy 

```C++
SR_GRAPH_NS::RenderStrategy::~RenderStrategy () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderStrategy.h`

