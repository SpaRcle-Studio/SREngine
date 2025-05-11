

# Struct SR\_GRAPH\_NS::ShaderUseInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**ignoreReplace**](#variable-ignorereplace)  <br> |
|  [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**pShader**](#variable-pshader)  <br> |
|  bool | [**useMaterialSamplers**](#variable-usematerialsamplers)  <br> |
|  bool | [**useMaterialUniforms**](#variable-usematerialuniforms)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ShaderUseInfo**](#function-shaderuseinfo-12) () = default<br> |
|  SR\_CONSTEXPR | [**ShaderUseInfo**](#function-shaderuseinfo-22) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |




























## Public Attributes Documentation




### variable ignoreReplace 

```C++
bool SR_GRAPH_NS::ShaderUseInfo::ignoreReplace;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader* SR_GRAPH_NS::ShaderUseInfo::pShader;
```




<hr>



### variable useMaterialSamplers 

```C++
bool SR_GRAPH_NS::ShaderUseInfo::useMaterialSamplers;
```




<hr>



### variable useMaterialUniforms 

```C++
bool SR_GRAPH_NS::ShaderUseInfo::useMaterialUniforms;
```




<hr>
## Public Functions Documentation




### function ShaderUseInfo [1/2]

```C++
SR_GRAPH_NS::ShaderUseInfo::ShaderUseInfo () = default
```




<hr>



### function ShaderUseInfo [2/2]

```C++
inline explicit SR_CONSTEXPR SR_GRAPH_NS::ShaderUseInfo::ShaderUseInfo (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/IShaderProgram.h`

