

# Class SR\_GRAPH\_NS::FrameBufferPassData



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FrameBufferPassData**](classSR__GRAPH__NS_1_1FrameBufferPassData.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &gt; | [**ClearColors**](#typedef-clearcolors)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; | [**FBRenderCallback**](#typedef-fbrendercallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void()&gt; | [**FBUpdateCallback**](#typedef-fbupdatecallback)  <br> |


## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FrameBufferPassData**](#function-framebufferpassdata) () <br> |
|  SR\_NODISCARD const ClearColors & | [**GetClearColors**](#function-getclearcolors) () noexcept const<br> |
|  SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetClearDepth**](#function-getcleardepth) () noexcept const<br> |
|  SR\_NODISCARD const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) &gt; & | [**GetFramebuffer**](#function-getframebuffer) () noexcept const<br> |
|  SR\_NODISCARD uint8\_t | [**GetLayersCount**](#function-getlayerscount) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFrameBufferRendered**](#function-isframebufferrendered) () noexcept const<br> |
|  bool | [**RenderFrameBuffer**](#function-renderframebuffer-12) (const FBRenderCallback & callback) <br> |
|  void | [**SetRenderTechnique**](#function-setrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pRenderTechnique) noexcept<br> |
|  void | [**UpdateFrameBuffer**](#function-updateframebuffer) (const FBUpdateCallback & callback) <br> |


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










































































## Public Types Documentation




### typedef ClearColors 

```C++
using SR_GRAPH_NS::FrameBufferPassData::ClearColors =  std::vector<SR_MATH_NS::FColor>;
```




<hr>



### typedef FBRenderCallback 

```C++
using SR_GRAPH_NS::FrameBufferPassData::FBRenderCallback =  SR_HTYPES_NS::Function<bool()>;
```




<hr>



### typedef FBUpdateCallback 

```C++
using SR_GRAPH_NS::FrameBufferPassData::FBUpdateCallback =  SR_HTYPES_NS::Function<void()>;
```




<hr>
## Public Functions Documentation




### function FrameBufferPassData 

```C++
SR_GRAPH_NS::FrameBufferPassData::FrameBufferPassData () 
```




<hr>



### function GetClearColors 

```C++
inline SR_NODISCARD const ClearColors & SR_GRAPH_NS::FrameBufferPassData::GetClearColors () noexcept const
```




<hr>



### function GetClearDepth 

```C++
inline SR_NODISCARD std::optional< float_t > SR_GRAPH_NS::FrameBufferPassData::GetClearDepth () noexcept const
```




<hr>



### function GetFramebuffer 

```C++
SR_NODISCARD const SR_HTYPES_NS::SharedPtr < SR_GTYPES_NS::Framebuffer > & SR_GRAPH_NS::FrameBufferPassData::GetFramebuffer () noexcept const
```




<hr>



### function GetLayersCount 

```C++
SR_NODISCARD uint8_t SR_GRAPH_NS::FrameBufferPassData::GetLayersCount () noexcept const
```




<hr>



### function IsFrameBufferRendered 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::FrameBufferPassData::IsFrameBufferRendered () noexcept const
```




<hr>



### function RenderFrameBuffer [1/2]

```C++
bool SR_GRAPH_NS::FrameBufferPassData::RenderFrameBuffer (
    const FBRenderCallback & callback
) 
```




<hr>



### function SetRenderTechnique 

```C++
inline void SR_GRAPH_NS::FrameBufferPassData::SetRenderTechnique (
    IRenderTechnique * pRenderTechnique
) noexcept
```




<hr>



### function UpdateFrameBuffer 

```C++
void SR_GRAPH_NS::FrameBufferPassData::UpdateFrameBuffer (
    const FBUpdateCallback & callback
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/Data/FrameBufferPassData.h`

