

# Struct SR\_GRAPH\_NS::SRSL::SRSLUnit



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SRSL**](namespaceSR__GRAPH__NS_1_1SRSL.md) **>** [**SRSLUnit**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; std::string, [**SRSLVariable**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLVariable.md) &gt; | [**bindings**](#variable-bindings)  <br> |
|  [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) | [**createInfo**](#variable-createinfo)   = `{}`<br> |
|  std::string | [**path**](#variable-path)  <br> |
|  SRSLStages | [**stages**](#variable-stages)  <br> |
|  SR\_SRSL\_NS::ShaderType | [**type**](#variable-type)   = `SR\_SRSL\_NS::ShaderType::Unknown`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::map&lt; std::string, [**SRSLVariable**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLVariable.md) &gt; | [**GetSamplers**](#function-getsamplers) () const<br> |
|  SR\_NODISCARD std::list&lt; std::pair&lt; std::string, [**SRSLVariable**](structSR__GRAPH__NS_1_1SRSL_1_1SRSLVariable.md) &gt; &gt; | [**GetUniformBlock**](#function-getuniformblock) () const<br> |
|  SR\_NODISCARD std::map&lt; uint32\_t, uint32\_t &gt; | [**GetUniformSizes**](#function-getuniformsizes) () const<br> |




























## Public Attributes Documentation




### variable bindings 

```C++
std::map<std::string, SRSLVariable> SR_GRAPH_NS::SRSL::SRSLUnit::bindings;
```




<hr>



### variable createInfo 

```C++
SRShaderCreateInfo SR_GRAPH_NS::SRSL::SRSLUnit::createInfo;
```




<hr>



### variable path 

```C++
std::string SR_GRAPH_NS::SRSL::SRSLUnit::path;
```




<hr>



### variable stages 

```C++
SRSLStages SR_GRAPH_NS::SRSL::SRSLUnit::stages;
```




<hr>



### variable type 

```C++
SR_SRSL_NS::ShaderType SR_GRAPH_NS::SRSL::SRSLUnit::type;
```




<hr>
## Public Functions Documentation




### function GetSamplers 

```C++
SR_NODISCARD std::map< std::string, SRSLVariable > SR_GRAPH_NS::SRSL::SRSLUnit::GetSamplers () const
```




<hr>



### function GetUniformBlock 

```C++
SR_NODISCARD std::list< std::pair< std::string, SRSLVariable > > SR_GRAPH_NS::SRSL::SRSLUnit::GetUniformBlock () const
```




<hr>



### function GetUniformSizes 

```C++
SR_NODISCARD std::map< uint32_t, uint32_t > SR_GRAPH_NS::SRSL::SRSLUnit::GetUniformSizes () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Loaders/SRSL.h`

