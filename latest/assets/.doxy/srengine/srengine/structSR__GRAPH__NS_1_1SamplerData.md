

# Struct SR\_GRAPH\_NS::SamplerData



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**fboName**](#variable-fboname)  <br> |
|  bool | [**global**](#variable-global)   = `false`<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**id**](#variable-id)  <br> |
|  uint64\_t | [**index**](#variable-index)   = `0`<br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) &gt; | [**pTexture**](#variable-ptexture)  <br> |
|  std::vector&lt; uint32\_t &gt; | [**textureId**](#variable-textureid)  <br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**texturePath**](#variable-texturepath)  <br> |
|  SamplerDataUsageType | [**usageType**](#variable-usagetype)   = `SamplerDataUsageType::Texture`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD uint32\_t | [**GetTextureId**](#function-gettextureid) (uint8\_t frame) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFrameBufferColorUsage**](#function-isframebuffercolorusage) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFrameBufferDepthUsage**](#function-isframebufferdepthusage) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFrameBufferUsage**](#function-isframebufferusage) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsTextureUsage**](#function-istextureusage) () noexcept const<br> |
| virtual void | [**OnPostLoad**](#function-onpostload) () override<br> |
|   | [**SamplerData**](#function-samplerdata-13) () = default<br> |
|   | [**SamplerData**](#function-samplerdata-23) ([**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md) && other) noexcept<br> |
|   | [**SamplerData**](#function-samplerdata-33) (const [**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md) & other) <br> |
|  [**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md) & | [**operator=**](#function-operator) ([**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md) && other) noexcept<br> |
|  [**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md) & | [**operator=**](#function-operator_1) (const [**SamplerData**](structSR__GRAPH__NS_1_1SamplerData.md) & other) <br> |
|   | [**~SamplerData**](#function-samplerdata) () override<br> |


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




### variable fboName 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::SamplerData::fboName;
```




<hr>



### variable global 

```C++
bool SR_GRAPH_NS::SamplerData::global;
```




<hr>



### variable id 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::SamplerData::id;
```




<hr>



### variable index 

```C++
uint64_t SR_GRAPH_NS::SamplerData::index;
```




<hr>



### variable pTexture 

```C++
SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture> SR_GRAPH_NS::SamplerData::pTexture;
```




<hr>



### variable textureId 

```C++
std::vector<uint32_t> SR_GRAPH_NS::SamplerData::textureId;
```




<hr>



### variable texturePath 

```C++
SR_UTILS_NS::Path SR_GRAPH_NS::SamplerData::texturePath;
```




<hr>



### variable usageType 

```C++
SamplerDataUsageType SR_GRAPH_NS::SamplerData::usageType;
```




<hr>
## Public Functions Documentation




### function GetTextureId 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::SamplerData::GetTextureId (
    uint8_t frame
) noexcept const
```




<hr>



### function IsFrameBufferColorUsage 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::SamplerData::IsFrameBufferColorUsage () noexcept const
```




<hr>



### function IsFrameBufferDepthUsage 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::SamplerData::IsFrameBufferDepthUsage () noexcept const
```




<hr>



### function IsFrameBufferUsage 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::SamplerData::IsFrameBufferUsage () noexcept const
```




<hr>



### function IsTextureUsage 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::SamplerData::IsTextureUsage () noexcept const
```




<hr>



### function OnPostLoad 

```C++
virtual void SR_GRAPH_NS::SamplerData::OnPostLoad () override
```



Implements [*SR\_UTILS\_NS::Serializable::OnPostLoad*](classSR__UTILS__NS_1_1Serializable.md#function-onpostload)


<hr>



### function SamplerData [1/3]

```C++
SR_GRAPH_NS::SamplerData::SamplerData () = default
```




<hr>



### function SamplerData [2/3]

```C++
SR_GRAPH_NS::SamplerData::SamplerData (
    SamplerData && other
) noexcept
```




<hr>



### function SamplerData [3/3]

```C++
SR_GRAPH_NS::SamplerData::SamplerData (
    const SamplerData & other
) 
```




<hr>



### function operator= 

```C++
SamplerData & SR_GRAPH_NS::SamplerData::operator= (
    SamplerData && other
) noexcept
```




<hr>



### function operator= 

```C++
SamplerData & SR_GRAPH_NS::SamplerData::operator= (
    const SamplerData & other
) 
```




<hr>



### function ~SamplerData 

```C++
SR_GRAPH_NS::SamplerData::~SamplerData () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/Data/SamplersPassData.h`

