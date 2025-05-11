

# Struct SR\_GRAPH\_NS::MeshRegistrationInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MeshRegistrationInfo**](structSR__GRAPH__NS_1_1MeshRegistrationInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::optional&lt; int32\_t &gt; | [**VBO**](#variable-vbo)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**layer**](#variable-layer)  <br> |
|  const [**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md) \* | [**pMaterial**](#variable-pmaterial)   = `nullptr`<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**pMesh**](#variable-pmesh)   = `nullptr`<br> |
|  [**SR\_GRAPH\_NS::RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* | [**pScene**](#variable-pscene)   = `nullptr`<br> |
|  [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**pShader**](#variable-pshader)   = `nullptr`<br> |
|  uint32\_t | [**poolId**](#variable-poolid)   = `static\_cast&lt;uint32\_t&gt;(SR\_ID\_INVALID)`<br> |
|  std::optional&lt; int64\_t &gt; | [**priority**](#variable-priority)  <br> |












































## Public Attributes Documentation




### variable VBO 

```C++
std::optional<int32_t> SR_GRAPH_NS::MeshRegistrationInfo::VBO;
```




<hr>



### variable layer 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::MeshRegistrationInfo::layer;
```




<hr>



### variable pMaterial 

```C++
const BaseMaterial* SR_GRAPH_NS::MeshRegistrationInfo::pMaterial;
```




<hr>



### variable pMesh 

```C++
SR_GTYPES_NS::Mesh* SR_GRAPH_NS::MeshRegistrationInfo::pMesh;
```




<hr>



### variable pScene 

```C++
SR_GRAPH_NS::RenderScene* SR_GRAPH_NS::MeshRegistrationInfo::pScene;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader* SR_GRAPH_NS::MeshRegistrationInfo::pShader;
```




<hr>



### variable poolId 

```C++
uint32_t SR_GRAPH_NS::MeshRegistrationInfo::poolId;
```




<hr>



### variable priority 

```C++
std::optional<int64_t> SR_GRAPH_NS::MeshRegistrationInfo::priority;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Utils/MeshUtils.h`

