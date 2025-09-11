

# Struct SR\_GRAPH\_NS::DebugPassShaderInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**DebugPassShaderInfo**](structSR__GRAPH__NS_1_1DebugPassShaderInfo.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**MemInfo**](structSR__GRAPH__NS_1_1DebugPassShaderInfo_1_1MemInfo.md) <br> |




## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**MemInfo**](structSR__GRAPH__NS_1_1DebugPassShaderInfo_1_1MemInfo.md) &gt; | [**UBOs**](#variable-ubos)  <br> |
|  std::vector&lt; std::vector&lt; [**DebugRenderer::DrawInfo**](structSR__GRAPH__NS_1_1DebugRenderer_1_1DrawInfo.md) &gt; &gt; | [**drawQueues**](#variable-drawqueues)  <br> |
|  SR\_GTYPES\_NS::Shader::Ptr | [**pShader**](#variable-pshader)  <br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**shaderPath**](#variable-shaderpath)  <br> |
|  uint32\_t | [**uboUsed**](#variable-uboused)   = `0`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DebugPassShaderInfo**](#function-debugpassshaderinfo) () = default<br> |
|  void | [**LoadShader**](#function-loadshader) () <br> |
|  void | [**SetShader**](#function-setshader) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|   | [**~DebugPassShaderInfo**](#function-debugpassshaderinfo) () override<br> |


## Public Functions inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-addserializationflags) (SerializationFlags flags) noexcept<br> |
|  SR\_NODISCARD bool | [**HasSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-hasserializationflags) (SerializationFlags flags) noexcept const<br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1Serializable.md#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) <br> |
| virtual void | [**OnPostLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpostload) () <br> |
| virtual void | [**OnPostSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpostsave) () <br> |
| virtual void | [**OnPreLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpreload) () <br> |
| virtual void | [**OnPreSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpresave) () <br> |
|  void | [**RemoveSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-removeserializationflags) (SerializationFlags flags) noexcept<br> |
| virtual void | [**Save**](classSR__UTILS__NS_1_1Serializable.md#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) const<br> |
| virtual void | [**VerifyAfterLoad**](classSR__UTILS__NS_1_1Serializable.md#function-verifyafterload) (SerializableVerifyContext & context) noexcept const<br> |


## Public Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |






## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |










































































## Public Attributes Documentation




### variable UBOs 

```C++
std::vector<MemInfo> SR_GRAPH_NS::DebugPassShaderInfo::UBOs;
```




<hr>



### variable drawQueues 

```C++
std::vector<std::vector<DebugRenderer::DrawInfo> > SR_GRAPH_NS::DebugPassShaderInfo::drawQueues;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader::Ptr SR_GRAPH_NS::DebugPassShaderInfo::pShader;
```




<hr>



### variable shaderPath 

```C++
SR_UTILS_NS::Path SR_GRAPH_NS::DebugPassShaderInfo::shaderPath;
```




<hr>



### variable uboUsed 

```C++
uint32_t SR_GRAPH_NS::DebugPassShaderInfo::uboUsed;
```




<hr>
## Public Functions Documentation




### function DebugPassShaderInfo 

```C++
SR_GRAPH_NS::DebugPassShaderInfo::DebugPassShaderInfo () = default
```




<hr>



### function LoadShader 

```C++
void SR_GRAPH_NS::DebugPassShaderInfo::LoadShader () 
```




<hr>



### function SetShader 

```C++
void SR_GRAPH_NS::DebugPassShaderInfo::SetShader (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function ~DebugPassShaderInfo 

```C++
SR_GRAPH_NS::DebugPassShaderInfo::~DebugPassShaderInfo () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/DebugPass.h`

