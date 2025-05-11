

# Struct SR\_GRAPH\_NS::SRFrameBufferCreateInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SRFrameBufferCreateInfo**](structSR__GRAPH__NS_1_1SRFrameBufferCreateInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**ColorLayer**](structSR__GRAPH__NS_1_1ColorLayer.md) &gt; \* | [**colors**](#variable-colors)   = `nullptr`<br> |
|  [**FrameBufferFeatures**](structSR__GRAPH__NS_1_1FrameBufferFeatures.md) | [**features**](#variable-features)  <br> |
|  uint32\_t | [**layersCount**](#variable-layerscount)   = `0`<br> |
|  [**DepthLayer**](structSR__GRAPH__NS_1_1DepthLayer.md) \* | [**pDepth**](#variable-pdepth)   = `nullptr`<br> |
|  int32\_t \* | [**pFBO**](#variable-pfbo)   = `nullptr`<br> |
|  uint8\_t | [**sampleCount**](#variable-samplecount)   = `0`<br> |
|  SR\_MATH\_NS::IVector2 | [**size**](#variable-size)  <br> |












































## Public Attributes Documentation




### variable colors 

```C++
std::vector<ColorLayer>* SR_GRAPH_NS::SRFrameBufferCreateInfo::colors;
```




<hr>



### variable features 

```C++
FrameBufferFeatures SR_GRAPH_NS::SRFrameBufferCreateInfo::features;
```




<hr>



### variable layersCount 

```C++
uint32_t SR_GRAPH_NS::SRFrameBufferCreateInfo::layersCount;
```




<hr>



### variable pDepth 

```C++
DepthLayer* SR_GRAPH_NS::SRFrameBufferCreateInfo::pDepth;
```




<hr>



### variable pFBO 

```C++
int32_t* SR_GRAPH_NS::SRFrameBufferCreateInfo::pFBO;
```




<hr>



### variable sampleCount 

```C++
uint8_t SR_GRAPH_NS::SRFrameBufferCreateInfo::sampleCount;
```




<hr>



### variable size 

```C++
SR_MATH_NS::IVector2 SR_GRAPH_NS::SRFrameBufferCreateInfo::size;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/PipelineState.h`

