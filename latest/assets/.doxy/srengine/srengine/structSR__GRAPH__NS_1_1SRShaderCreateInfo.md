

# Struct SR\_GRAPH\_NS::SRShaderCreateInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**blendEnabled**](#variable-blendenabled)   = `false`<br> |
|  CullMode | [**cullMode**](#variable-cullmode)   = `CullMode::Unknown`<br> |
|  DepthCompare | [**depthCompare**](#variable-depthcompare)   = `DepthCompare::Unknown`<br> |
|  bool | [**depthTest**](#variable-depthtest)   = `false`<br> |
|  bool | [**depthWrite**](#variable-depthwrite)   = `false`<br> |
|  PolygonMode | [**polygonMode**](#variable-polygonmode)   = `PolygonMode::Unknown`<br> |
|  PrimitiveTopology | [**primitiveTopology**](#variable-primitivetopology)   = `PrimitiveTopology::Unknown`<br> |
|  std::map&lt; ShaderStage, [**SRShaderStageInfo**](structSR__GRAPH__NS_1_1SRShaderStageInfo.md) &gt; | [**stages**](#variable-stages)  <br> |
|  UBOInfo | [**uniforms**](#variable-uniforms)  <br> |
|  VertexAttributes | [**vertexAttributes**](#variable-vertexattributes)  <br> |
|  VertexDescriptions | [**vertexDescriptions**](#variable-vertexdescriptions)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**Validate**](#function-validate) () noexcept const<br> |




























## Public Attributes Documentation




### variable blendEnabled 

```C++
bool SR_GRAPH_NS::SRShaderCreateInfo::blendEnabled;
```




<hr>



### variable cullMode 

```C++
CullMode SR_GRAPH_NS::SRShaderCreateInfo::cullMode;
```




<hr>



### variable depthCompare 

```C++
DepthCompare SR_GRAPH_NS::SRShaderCreateInfo::depthCompare;
```




<hr>



### variable depthTest 

```C++
bool SR_GRAPH_NS::SRShaderCreateInfo::depthTest;
```




<hr>



### variable depthWrite 

```C++
bool SR_GRAPH_NS::SRShaderCreateInfo::depthWrite;
```




<hr>



### variable polygonMode 

```C++
PolygonMode SR_GRAPH_NS::SRShaderCreateInfo::polygonMode;
```




<hr>



### variable primitiveTopology 

```C++
PrimitiveTopology SR_GRAPH_NS::SRShaderCreateInfo::primitiveTopology;
```




<hr>



### variable stages 

```C++
std::map<ShaderStage, SRShaderStageInfo> SR_GRAPH_NS::SRShaderCreateInfo::stages;
```




<hr>



### variable uniforms 

```C++
UBOInfo SR_GRAPH_NS::SRShaderCreateInfo::uniforms;
```




<hr>



### variable vertexAttributes 

```C++
VertexAttributes SR_GRAPH_NS::SRShaderCreateInfo::vertexAttributes;
```




<hr>



### variable vertexDescriptions 

```C++
VertexDescriptions SR_GRAPH_NS::SRShaderCreateInfo::vertexDescriptions;
```




<hr>
## Public Functions Documentation




### function Validate 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::SRShaderCreateInfo::Validate () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/IShaderProgram.h`

