

# Class SR\_GRAPH\_NS::ShaderReplacePredicate



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ShaderReplacePredicate**](classSR__GRAPH__NS_1_1ShaderReplacePredicate.md)










Inherited by the following classes: [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**SR\_GRAPH\_NS::ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) | [**ReplaceShader**](#function-replaceshader) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) const = 0<br> |
| virtual  | [**~ShaderReplacePredicate**](#function-shaderreplacepredicate) () = default<br> |




























## Public Functions Documentation




### function ReplaceShader 

```C++
virtual SR_NODISCARD SR_GRAPH_NS::ShaderUseInfo SR_GRAPH_NS::ShaderReplacePredicate::ReplaceShader (
    SR_GTYPES_NS::Shader * pShader
) const = 0
```




<hr>



### function ~ShaderReplacePredicate 

```C++
virtual SR_GRAPH_NS::ShaderReplacePredicate::~ShaderReplacePredicate () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderPredicates.h`

