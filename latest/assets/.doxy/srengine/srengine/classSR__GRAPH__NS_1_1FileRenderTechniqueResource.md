

# Class SR\_GRAPH\_NS::FileRenderTechniqueResource



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FileRenderTechniqueResource**](classSR__GRAPH__NS_1_1FileRenderTechniqueResource.md)








Inherits the following classes: SR_UTILS_NS::Settings














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileRenderTechniqueResource**](classSR__GRAPH__NS_1_1FileRenderTechniqueResource.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FileRenderTechniqueResource**](#function-filerendertechniqueresource) () = default<br> |
|  SR\_NODISCARD bool | [**IsAllowedMultiInstance**](#function-isallowedmultiinstance) () override const<br> |
|  void | [**RegisterRenderTechnique**](#function-registerrendertechnique) (const FileRenderTechnique::Ptr & renderTechnique) <br> |
|  void | [**UnregisterRenderTechnique**](#function-unregisterrendertechnique) (const FileRenderTechnique::Ptr & renderTechnique) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  FileRenderTechniqueResource::Ptr | [**Load**](#function-load-12) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::set&lt; FileRenderTechnique::Ptr &gt; | [**m\_renderTechniques**](#variable-m_rendertechniques)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Load**](#function-load-22) () override<br> |
|  bool | [**Unload**](#function-unload) () override<br> |




## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::FileRenderTechniqueResource::Ptr =  SR_HTYPES_NS::SharedPtr<FileRenderTechniqueResource>;
```




<hr>
## Public Functions Documentation




### function FileRenderTechniqueResource 

```C++
SR_GRAPH_NS::FileRenderTechniqueResource::FileRenderTechniqueResource () = default
```




<hr>



### function IsAllowedMultiInstance 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::FileRenderTechniqueResource::IsAllowedMultiInstance () override const
```




<hr>



### function RegisterRenderTechnique 

```C++
inline void SR_GRAPH_NS::FileRenderTechniqueResource::RegisterRenderTechnique (
    const FileRenderTechnique::Ptr & renderTechnique
) 
```




<hr>



### function UnregisterRenderTechnique 

```C++
inline void SR_GRAPH_NS::FileRenderTechniqueResource::UnregisterRenderTechnique (
    const FileRenderTechnique::Ptr & renderTechnique
) 
```




<hr>
## Public Static Functions Documentation




### function Load [1/2]

```C++
static FileRenderTechniqueResource::Ptr SR_GRAPH_NS::FileRenderTechniqueResource::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_renderTechniques 

```C++
std::set<FileRenderTechnique::Ptr> SR_GRAPH_NS::FileRenderTechniqueResource::m_renderTechniques;
```




<hr>
## Protected Functions Documentation




### function Load [2/2]

```C++
bool SR_GRAPH_NS::FileRenderTechniqueResource::Load () override
```




<hr>



### function Unload 

```C++
bool SR_GRAPH_NS::FileRenderTechniqueResource::Unload () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderTechnique.h`

