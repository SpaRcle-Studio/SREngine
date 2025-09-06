

# Struct SR\_GRAPH\_NS::FrameBufferFeatures



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FrameBufferFeatures**](structSR__GRAPH__NS_1_1FrameBufferFeatures.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**colorLoad**](#variable-colorload)   = `false`<br> |
|  bool | [**colorShaderRead**](#variable-colorshaderread)   = `true`<br> |
|  bool | [**colorTransferDst**](#variable-colortransferdst)   = `false`<br> |
|  bool | [**colorTransferSrc**](#variable-colortransfersrc)   = `false`<br> |
|  bool | [**depthLoad**](#variable-depthload)   = `false`<br> |
|  bool | [**depthShaderRead**](#variable-depthshaderread)   = `false`<br> |
|  bool | [**depthTransferDst**](#variable-depthtransferdst)   = `false`<br> |
|  bool | [**depthTransferSrc**](#variable-depthtransfersrc)   = `false`<br> |


















































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
|  void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
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




### variable colorLoad 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::colorLoad;
```




<hr>



### variable colorShaderRead 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::colorShaderRead;
```




<hr>



### variable colorTransferDst 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::colorTransferDst;
```




<hr>



### variable colorTransferSrc 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::colorTransferSrc;
```




<hr>



### variable depthLoad 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::depthLoad;
```




<hr>



### variable depthShaderRead 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::depthShaderRead;
```




<hr>



### variable depthTransferDst 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::depthTransferDst;
```




<hr>



### variable depthTransferSrc 

```C++
bool SR_GRAPH_NS::FrameBufferFeatures::depthTransferSrc;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/FrameBufferFeatures.h`

