

# Struct SR\_GRAPH\_NS::DebugPass::ShaderInfo



[**ClassList**](annotated.md) **>** [**ShaderInfo**](structSR__GRAPH__NS_1_1DebugPass_1_1ShaderInfo.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**MemInfo**](structSR__GRAPH__NS_1_1DebugPass_1_1ShaderInfo_1_1MemInfo.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**MemInfo**](structSR__GRAPH__NS_1_1DebugPass_1_1ShaderInfo_1_1MemInfo.md) &gt; | [**UBOs**](#variable-ubos)  <br> |
|  std::vector&lt; std::vector&lt; [**DebugRenderer::DrawInfo**](structSR__GRAPH__NS_1_1DebugRenderer_1_1DrawInfo.md) &gt; &gt; | [**drawQueues**](#variable-drawqueues)  <br> |
|  SR\_GTYPES\_NS::Shader::Ptr | [**pShader**](#variable-pshader)  <br> |
|  uint32\_t | [**uboUsed**](#variable-uboused)   = `0`<br> |












































## Public Attributes Documentation




### variable UBOs 

```C++
std::vector<MemInfo> SR_GRAPH_NS::DebugPass::ShaderInfo::UBOs;
```




<hr>



### variable drawQueues 

```C++
std::vector<std::vector<DebugRenderer::DrawInfo> > SR_GRAPH_NS::DebugPass::ShaderInfo::drawQueues;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader::Ptr SR_GRAPH_NS::DebugPass::ShaderInfo::pShader;
```




<hr>



### variable uboUsed 

```C++
uint32_t SR_GRAPH_NS::DebugPass::ShaderInfo::uboUsed;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/DebugPass.h`

