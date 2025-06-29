

# Class SR\_SRSL\_NS::SRSLShader



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLShader**](classSR__SRSL__NS_1_1SRSLShader.md)



[More...](#detailed-description)

* `#include <Shader.h>`



Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**Export**](#function-export) (ShaderLanguage shaderLanguage) const<br> |
|  SR\_NODISCARD const [**SRSLUniformBlock::Field**](structSR__SRSL__NS_1_1SRSLUniformBlock_1_1Field.md) \* | [**FindField**](#function-findfield) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD const [**SRSLStructureStatement**](classSR__SRSL__NS_1_1SRSLStructureStatement.md) \* | [**FindStructure**](#function-findstructure) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD const [**SRSLUniformBlock**](structSR__SRSL__NS_1_1SRSLUniformBlock.md) \* | [**FindUniformBlock**](#function-finduniformblock) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD const SRSLAnalyzedTree::Ptr | [**GetAnalyzedTree**](#function-getanalyzedtree) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::UVector3 & | [**GetComputeWorkGroupSize**](#function-getcomputeworkgroupsize) () const<br> |
|  SR\_NODISCARD const std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) \* &gt; & | [**GetConstants**](#function-getconstants) () const<br> |
|  SR\_NODISCARD const SRShaderCreateInfo & | [**GetCreateInfo**](#function-getcreateinfo) () const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetIncludes**](#function-getincludes) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetPath**](#function-getpath) () const<br> |
|  SR\_NODISCARD const [**SRSLUniformBlock**](structSR__SRSL__NS_1_1SRSLUniformBlock.md) & | [**GetPushConstants**](#function-getpushconstants) () const<br> |
|  SR\_NODISCARD const UniformBlocks & | [**GetSSBOBlocks**](#function-getssboblocks) () const<br> |
|  SR\_NODISCARD const SRSLSamplers & | [**GetSamplers**](#function-getsamplers) () const<br> |
|  SR\_NODISCARD const std::vector&lt; std::pair&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) \* &gt; &gt; & | [**GetShared**](#function-getshared) () const<br> |
|  SR\_NODISCARD SR\_SRSL\_NS::ShaderType | [**GetType**](#function-gettype) () const<br> |
|  SR\_NODISCARD const UniformBlocks & | [**GetUniformBlocks**](#function-getuniformblocks) () const<br> |
|  SR\_NODISCARD const SRSLUseStack::Ptr | [**GetUseStack**](#function-getusestack) () const<br> |
|  SR\_NODISCARD Vertices::VertexType | [**GetVertexType**](#function-getvertextype) () const<br> |
|  SR\_NODISCARD bool | [**IsCacheActual**](#function-iscacheactual-12) () const<br> |
|  SR\_NODISCARD bool | [**IsCacheActual**](#function-iscacheactual-22) (ShaderLanguage shaderLanguage) const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) (ShaderLanguage shaderLanguage) const<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearShadersCache**](#function-clearshaderscache) () <br> |
|  SR\_NODISCARD SRSLShader::Ptr | [**Load**](#function-load) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) path) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Detailed Description


Это не шейдер в привычном понимании, это набор всех данных для генерирования любого шейдерного кода и для последующей его экспортации. 


    
## Public Functions Documentation




### function Export 

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLShader::Export (
    ShaderLanguage shaderLanguage
) const
```




<hr>



### function FindField 

```C++
SR_NODISCARD const SRSLUniformBlock::Field * SR_SRSL_NS::SRSLShader::FindField (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function FindStructure 

```C++
SR_NODISCARD const SRSLStructureStatement * SR_SRSL_NS::SRSLShader::FindStructure (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function FindUniformBlock 

```C++
SR_NODISCARD const SRSLUniformBlock * SR_SRSL_NS::SRSLShader::FindUniformBlock (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function GetAnalyzedTree 

```C++
SR_NODISCARD const SRSLAnalyzedTree::Ptr SR_SRSL_NS::SRSLShader::GetAnalyzedTree () const
```




<hr>



### function GetComputeWorkGroupSize 

```C++
inline SR_NODISCARD const SR_MATH_NS::UVector3 & SR_SRSL_NS::SRSLShader::GetComputeWorkGroupSize () const
```




<hr>



### function GetConstants 

```C++
inline SR_NODISCARD const std::map< SR_UTILS_NS::StringAtom , SRSLVariable * > & SR_SRSL_NS::SRSLShader::GetConstants () const
```




<hr>



### function GetCreateInfo 

```C++
inline SR_NODISCARD const SRShaderCreateInfo & SR_SRSL_NS::SRSLShader::GetCreateInfo () const
```




<hr>



### function GetIncludes 

```C++
inline SR_NODISCARD const std::vector< SR_UTILS_NS::StringAtom > & SR_SRSL_NS::SRSLShader::GetIncludes () const
```




<hr>



### function GetPath 

```C++
inline SR_NODISCARD SR_UTILS_NS::Path SR_SRSL_NS::SRSLShader::GetPath () const
```




<hr>



### function GetPushConstants 

```C++
inline SR_NODISCARD const SRSLUniformBlock & SR_SRSL_NS::SRSLShader::GetPushConstants () const
```




<hr>



### function GetSSBOBlocks 

```C++
inline SR_NODISCARD const UniformBlocks & SR_SRSL_NS::SRSLShader::GetSSBOBlocks () const
```




<hr>



### function GetSamplers 

```C++
inline SR_NODISCARD const SRSLSamplers & SR_SRSL_NS::SRSLShader::GetSamplers () const
```




<hr>



### function GetShared 

```C++
inline SR_NODISCARD const std::vector< std::pair< SR_UTILS_NS::StringAtom , SRSLVariable * > > & SR_SRSL_NS::SRSLShader::GetShared () const
```




<hr>



### function GetType 

```C++
SR_NODISCARD SR_SRSL_NS::ShaderType SR_SRSL_NS::SRSLShader::GetType () const
```




<hr>



### function GetUniformBlocks 

```C++
inline SR_NODISCARD const UniformBlocks & SR_SRSL_NS::SRSLShader::GetUniformBlocks () const
```




<hr>



### function GetUseStack 

```C++
SR_NODISCARD const SRSLUseStack::Ptr SR_SRSL_NS::SRSLShader::GetUseStack () const
```




<hr>



### function GetVertexType 

```C++
SR_NODISCARD Vertices::VertexType SR_SRSL_NS::SRSLShader::GetVertexType () const
```




<hr>



### function IsCacheActual [1/2]

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLShader::IsCacheActual () const
```




<hr>



### function IsCacheActual [2/2]

```C++
SR_NODISCARD bool SR_SRSL_NS::SRSLShader::IsCacheActual (
    ShaderLanguage shaderLanguage
) const
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_SRSL_NS::SRSLShader::ToString (
    ShaderLanguage shaderLanguage
) const
```




<hr>
## Public Static Functions Documentation




### function ClearShadersCache 

```C++
static void SR_SRSL_NS::SRSLShader::ClearShadersCache () 
```




<hr>



### function Load 

```C++
static SR_NODISCARD SRSLShader::Ptr SR_SRSL_NS::SRSLShader::Load (
    SR_UTILS_NS::Path path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/Shader.h`

