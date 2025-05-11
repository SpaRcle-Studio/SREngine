

# Class SR\_GTYPES\_NS::Framebuffer



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md)



[More...](#detailed-description)

* `#include <Framebuffer.h>`



Inherits the following classes: [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md),  Memory::IGraphicsResource














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &gt; | [**ClearColors**](#typedef-clearcolors)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; Pipeline &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef [**Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) | [**Super**](#typedef-super)  <br> |


## Public Types inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**LoadState**](classSR__UTILS__NS_1_1IResource.md#enum-loadstate)  <br> |
| typedef [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**Ptr**](classSR__UTILS__NS_1_1IResource.md#typedef-ptr)  <br> |
| enum uint8\_t | [**RemoveUPResult**](classSR__UTILS__NS_1_1IResource.md#enum-removeupresult)  <br> |




















## Public Attributes inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**RELOAD\_BEGIN\_EVENT**](classSR__UTILS__NS_1_1IResource.md#variable-reload_begin_event)   = `"ReloadBegin"`<br> |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**RELOAD\_DONE\_EVENT**](classSR__UTILS__NS_1_1IResource.md#variable-reload_done_event)   = `"ReloadDone"`<br> |














































































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**BeginCmdBuffer**](#function-begincmdbuffer-13) () <br> |
|  bool | [**BeginCmdBuffer**](#function-begincmdbuffer-23) (const ClearColors & clearColors, std::optional&lt; float\_t &gt; depth) <br> |
|  bool | [**BeginCmdBuffer**](#function-begincmdbuffer-33) (const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & clearColor, float\_t depth) <br> |
|  bool | [**BeginRender**](#function-beginrender) () <br> |
|  bool | [**Bind**](#function-bind) () <br> |
|  void | [**EndCmdBuffer**](#function-endcmdbuffer) () <br> |
|  void | [**EndRender**](#function-endrender) () <br> |
|  void | [**FreeVideoMemory**](#function-freevideomemory) () override<br> |
|  SR\_NODISCARD uint32\_t | [**GetColorLayersCount**](#function-getcolorlayerscount) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetColorTexture**](#function-getcolortexture) (uint32\_t layer) <br> |
|  SR\_NODISCARD ImageAspect | [**GetDepthAspect**](#function-getdepthaspect) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetDepthTexture**](#function-getdepthtexture) (int32\_t layer=-1) <br> |
|  SR\_NODISCARD const FrameBufferFeatures & | [**GetFeatures**](#function-getfeatures) () const<br> |
| virtual uint64\_t | [**GetFileHash**](#function-getfilehash) () override const<br> |
|  SR\_NODISCARD uint32\_t | [**GetHeight**](#function-getheight) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetId**](#function-getid) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetLayersCount**](#function-getlayerscount) () noexcept const<br> |
|  SR\_NODISCARD uint8\_t | [**GetSamplesCount**](#function-getsamplescount) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetSize**](#function-getsize) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetWidth**](#function-getwidth) () const<br> |
|  SR\_NODISCARD bool | [**IsDepthEnabled**](#function-isdepthenabled) () const<br> |
|  SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () const<br> |
| virtual SR\_NODISCARD bool | [**IsFileResource**](#function-isfileresource) () noexcept override const<br>_является ли ресурс файловым_  |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
|  void | [**SetDepthAspect**](#function-setdepthaspect) (ImageAspect depthAspect) <br> |
|  void | [**SetDepthEnabled**](#function-setdepthenabled) (bool depthEnabled) <br> |
|  void | [**SetDirty**](#function-setdirty) () <br> |
|  void | [**SetFeatures**](#function-setfeatures) (const FrameBufferFeatures & features) <br> |
|  void | [**SetLayersCount**](#function-setlayerscount) (uint32\_t layersCount) <br> |
|  void | [**SetSampleCount**](#function-setsamplecount) (uint8\_t samples) <br> |
|  void | [**SetSize**](#function-setsize) (const SR\_MATH\_NS::IVector2 & size) <br> |
|  void | [**SetViewportScissor**](#function-setviewportscissor) () <br> |
|  bool | [**Update**](#function-update) () <br> |


## Public Functions inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddUsePoint**](classSR__UTILS__NS_1_1IResource.md#function-addusepoint) () <br> |
| virtual void | [**CheckResourceUsage**](classSR__UTILS__NS_1_1IResource.md#function-checkresourceusage) () <br> |
| virtual SR\_NODISCARD [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**CopyResource**](classSR__UTILS__NS_1_1IResource.md#function-copyresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* destination) const<br> |
| virtual void | [**DeleteResource**](classSR__UTILS__NS_1_1IResource.md#function-deleteresource) () <br> |
| virtual bool | [**Destroy**](classSR__UTILS__NS_1_1IResource.md#function-destroy) () <br> |
|  bool | [**Execute**](classSR__UTILS__NS_1_1IResource.md#function-execute) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; & fun) const<br> |
|  bool | [**ForceDestroy**](classSR__UTILS__NS_1_1IResource.md#function-forcedestroy) () <br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetAssociatedPath**](classSR__UTILS__NS_1_1IResource.md#function-getassociatedpath) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetCountUses**](classSR__UTILS__NS_1_1IResource.md#function-getcountuses) () noexcept const<br> |
| virtual SR\_NODISCARD uint64\_t | [**GetFileHash**](classSR__UTILS__NS_1_1IResource.md#function-getfilehash) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetLifetime**](classSR__UTILS__NS_1_1IResource.md#function-getlifetime) () noexcept const<br> |
|  SR\_NODISCARD uint16\_t | [**GetReloadCount**](classSR__UTILS__NS_1_1IResource.md#function-getreloadcount) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetResourceHash**](classSR__UTILS__NS_1_1IResource.md#function-getresourcehash) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetResourceHashName**](classSR__UTILS__NS_1_1IResource.md#function-getresourcehashname) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourceId**](classSR__UTILS__NS_1_1IResource.md#function-getresourceid) () noexcept const<br> |
|  SR\_NODISCARD ResourceInfoWeakPtr | [**GetResourceInfo**](classSR__UTILS__NS_1_1IResource.md#function-getresourceinfo) () noexcept const<br> |
|  SR\_NODISCARD LoadState | [**GetResourceLoadState**](classSR__UTILS__NS_1_1IResource.md#function-getresourceloadstate) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetResourceName**](classSR__UTILS__NS_1_1IResource.md#function-getresourcename) () const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourcePath**](classSR__UTILS__NS_1_1IResource.md#function-getresourcepath) () const<br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**InitializeResourcePath**](classSR__UTILS__NS_1_1IResource.md#function-initializeresourcepath) () const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](classSR__UTILS__NS_1_1IResource.md#function-isalive) () const<br> |
| virtual SR\_NODISCARD bool | [**IsAllowedToRevive**](classSR__UTILS__NS_1_1IResource.md#function-isallowedtorevive) () const<br> |
|  SR\_NODISCARD bool | [**IsDestroyed**](classSR__UTILS__NS_1_1IResource.md#function-isdestroyed) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFileResource**](classSR__UTILS__NS_1_1IResource.md#function-isfileresource) () noexcept const<br>_является ли ресурс файловым_  |
|  SR\_NODISCARD bool | [**IsForceDestroyed**](classSR__UTILS__NS_1_1IResource.md#function-isforcedestroyed) () const<br> |
|  SR\_NODISCARD bool | [**IsLoaded**](classSR__UTILS__NS_1_1IResource.md#function-isloaded) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](classSR__UTILS__NS_1_1IResource.md#function-isregistered) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceFromMemory**](classSR__UTILS__NS_1_1IResource.md#function-isresourcefrommemory) () noexcept const<br> |
|  bool | [**IsResourceType**](classSR__UTILS__NS_1_1IResource.md#function-isresourcetype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceWillBeDeleted**](classSR__UTILS__NS_1_1IResource.md#function-isresourcewillbedeleted) () const<br> |
|  bool | [**Kill**](classSR__UTILS__NS_1_1IResource.md#function-kill) () <br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1IResource.md#function-load) () <br> |
| virtual void | [**OnReloadDone**](classSR__UTILS__NS_1_1IResource.md#function-onreloaddone) () <br> |
| virtual void | [**OnResourceRegistered**](classSR__UTILS__NS_1_1IResource.md#function-onresourceregistered) () <br> |
| virtual bool | [**Reload**](classSR__UTILS__NS_1_1IResource.md#function-reload) () <br> |
| virtual RemoveUPResult | [**RemoveUsePoint**](classSR__UTILS__NS_1_1IResource.md#function-removeusepoint) () <br> |
| virtual void | [**ReviveResource**](classSR__UTILS__NS_1_1IResource.md#function-reviveresource) () <br> |
|  void | [**SetId**](classSR__UTILS__NS_1_1IResource.md#function-setid) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, bool autoRegister=true) <br> |
|  void | [**SetLifetime**](classSR__UTILS__NS_1_1IResource.md#function-setlifetime) (int64\_t lifeTime) <br> |
|  void | [**SetResourceHash**](classSR__UTILS__NS_1_1IResource.md#function-setresourcehash) (uint64\_t hash) <br> |
|  void | [**SignalWatch**](classSR__UTILS__NS_1_1IResource.md#function-signalwatch) () <br> |
| virtual void | [**StartWatch**](classSR__UTILS__NS_1_1IResource.md#function-startwatch) () <br> |
| virtual void | [**StopWatch**](classSR__UTILS__NS_1_1IResource.md#function-stopwatch) () <br> |
| virtual bool | [**Unload**](classSR__UTILS__NS_1_1IResource.md#function-unload) () <br> |
|  void | [**UpdateResourceLifeTime**](classSR__UTILS__NS_1_1IResource.md#function-updateresourcelifetime) () <br> |


## Public Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-adddependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |
|  SR\_NODISCARD const std::unordered\_set&lt; [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* &gt; & | [**GetContainerParents**](classSR__UTILS__NS_1_1ResourceContainer.md#function-getcontainerparents) () const<br> |
|  void | [**RemoveDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-removedependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_UTILS_NS::SubscriptionHolder

See [SR\_UTILS\_NS::SubscriptionHolder](classSR__UTILS__NS_1_1SubscriptionHolder.md)

| Type | Name |
| ---: | :--- |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-12) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) <br> |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-22) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) & message) <br> |
|  SR\_NODISCARD bool | [**HasSubscriptions**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-hassubscriptions) () noexcept const<br> |
|  SR\_NODISCARD [**Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**Subscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscribe) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; && callback) <br> |
|   | [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder-13) () <br> |
|   | [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder-23) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & other) = delete<br> |
|   | [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder-33) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) && other) = delete<br> |
|  void | [**Unsubscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-unsubscribe) (const [**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md) \* pSubscription) <br> |
|  [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & | [**operator=**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-operator) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & other) = delete<br> |
|  [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & | [**operator=**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-operator_1) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) && other) = delete<br> |
| virtual  | [**~SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Ptr**](classSR__GTYPES__NS_1_1Framebuffer.md) | [**Create**](#function-create-16) (uint32\_t images, const SR\_MATH\_NS::IVector2 & size) <br> |
|  [**Ptr**](classSR__GTYPES__NS_1_1Framebuffer.md) | [**Create**](#function-create-26) (const std::list&lt; ImageFormat &gt; & colors, ImageFormat depth) <br> |
|  [**Ptr**](classSR__GTYPES__NS_1_1Framebuffer.md) | [**Create**](#function-create-36) (const std::list&lt; ImageFormat &gt; & colors, ImageFormat depth, const SR\_MATH\_NS::IVector2 & size) <br> |
|  [**Ptr**](classSR__GTYPES__NS_1_1Framebuffer.md) | [**Create**](#function-create-46) (const std::list&lt; ImageFormat &gt; & colors, ImageFormat depth, const SR\_MATH\_NS::IVector2 & size, uint8\_t samples) <br> |
|  [**Ptr**](classSR__GTYPES__NS_1_1Framebuffer.md) | [**Create**](#function-create-56) (const std::list&lt; ImageFormat &gt; & colors, ImageFormat depth, const SR\_MATH\_NS::IVector2 & size, uint8\_t samples, uint32\_t layersCount) <br> |
|  [**Ptr**](classSR__GTYPES__NS_1_1Framebuffer.md) | [**Create**](#function-create-66) (const std::list&lt; ImageFormat &gt; & colors, ImageFormat depth, const SR\_MATH\_NS::IVector2 & size, uint8\_t samples, uint32\_t layersCount, ImageAspect depthAspect) <br> |
































## Protected Attributes inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|  std::atomic&lt; uint16\_t &gt; | [**m\_countUses**](classSR__UTILS__NS_1_1IResource.md#variable-m_countuses)   = `0`<br>_не рекомендуется вручную обращаться к счетчику при наследовании_  |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUnUseStackTraces**](classSR__UTILS__NS_1_1IResource.md#variable-m_debugunusestacktraces)  <br> |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUseStackTraces**](classSR__UTILS__NS_1_1IResource.md#variable-m_debugusestacktraces)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_isFromMemory**](classSR__UTILS__NS_1_1IResource.md#variable-m_isfrommemory)   = `false`<br> |
|  std::atomic&lt; LoadState &gt; | [**m\_loadState**](classSR__UTILS__NS_1_1IResource.md#variable-m_loadstate)   = `LoadState::Unknown`<br> |
|  const uint64\_t | [**m\_resourceHashName**](classSR__UTILS__NS_1_1IResource.md#variable-m_resourcehashname)   = `0`<br> |
|  std::list&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileWatcher**](classSR__UTILS__NS_1_1FileWatcher.md) &gt; &gt; | [**m\_watchers**](classSR__UTILS__NS_1_1IResource.md#variable-m_watchers)  <br> |
















































































## Protected Functions inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|   | [**IResource**](classSR__UTILS__NS_1_1IResource.md#function-iresource) (uint64\_t hashName) <br> |
|   | [**~IResource**](classSR__UTILS__NS_1_1IResource.md#function-iresource) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnResourceUpdated**](classSR__UTILS__NS_1_1ResourceContainer.md#function-onresourceupdated) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer, int32\_t depth) <br> |
|  void | [**UpdateResources**](classSR__UTILS__NS_1_1ResourceContainer.md#function-updateresources) (int32\_t depth=0) <br> |
|   | [**~ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |














## Detailed Description


\Usage Bing -&gt; BeginRenderBuffer -&gt; BeginRender -&gt; EndRender -&gt; EndRenderBuffer 


    
## Public Types Documentation




### typedef ClearColors 

```C++
using SR_GTYPES_NS::Framebuffer::ClearColors =  std::vector<SR_MATH_NS::FColor>;
```




<hr>



### typedef PipelinePtr 

```C++
using SR_GTYPES_NS::Framebuffer::PipelinePtr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef Ptr 

```C++
using SR_GTYPES_NS::Framebuffer::Ptr =  Framebuffer*;
```




<hr>



### typedef Super 

```C++
using SR_GTYPES_NS::Framebuffer::Super =  SR_UTILS_NS::IResource;
```




<hr>
## Public Functions Documentation




### function BeginCmdBuffer [1/3]

```C++
bool SR_GTYPES_NS::Framebuffer::BeginCmdBuffer () 
```




<hr>



### function BeginCmdBuffer [2/3]

```C++
bool SR_GTYPES_NS::Framebuffer::BeginCmdBuffer (
    const ClearColors & clearColors,
    std::optional< float_t > depth
) 
```




<hr>



### function BeginCmdBuffer [3/3]

```C++
bool SR_GTYPES_NS::Framebuffer::BeginCmdBuffer (
    const SR_MATH_NS::FColor & clearColor,
    float_t depth
) 
```




<hr>



### function BeginRender 

```C++
bool SR_GTYPES_NS::Framebuffer::BeginRender () 
```




<hr>



### function Bind 

```C++
bool SR_GTYPES_NS::Framebuffer::Bind () 
```




<hr>



### function EndCmdBuffer 

```C++
void SR_GTYPES_NS::Framebuffer::EndCmdBuffer () 
```




<hr>



### function EndRender 

```C++
void SR_GTYPES_NS::Framebuffer::EndRender () 
```




<hr>



### function FreeVideoMemory 

```C++
void SR_GTYPES_NS::Framebuffer::FreeVideoMemory () override
```




<hr>



### function GetColorLayersCount 

```C++
inline SR_NODISCARD uint32_t SR_GTYPES_NS::Framebuffer::GetColorLayersCount () noexcept const
```




<hr>



### function GetColorTexture 

```C++
SR_NODISCARD int32_t SR_GTYPES_NS::Framebuffer::GetColorTexture (
    uint32_t layer
) 
```




<hr>



### function GetDepthAspect 

```C++
inline SR_NODISCARD ImageAspect SR_GTYPES_NS::Framebuffer::GetDepthAspect () noexcept const
```




<hr>



### function GetDepthTexture 

```C++
SR_NODISCARD int32_t SR_GTYPES_NS::Framebuffer::GetDepthTexture (
    int32_t layer=-1
) 
```




<hr>



### function GetFeatures 

```C++
inline SR_NODISCARD const FrameBufferFeatures & SR_GTYPES_NS::Framebuffer::GetFeatures () const
```




<hr>



### function GetFileHash 

```C++
virtual uint64_t SR_GTYPES_NS::Framebuffer::GetFileHash () override const
```



Implements [*SR\_UTILS\_NS::IResource::GetFileHash*](classSR__UTILS__NS_1_1IResource.md#function-getfilehash)


<hr>



### function GetHeight 

```C++
SR_NODISCARD uint32_t SR_GTYPES_NS::Framebuffer::GetHeight () const
```




<hr>



### function GetId 

```C++
SR_NODISCARD int32_t SR_GTYPES_NS::Framebuffer::GetId () const
```




<hr>



### function GetLayersCount 

```C++
inline SR_NODISCARD uint32_t SR_GTYPES_NS::Framebuffer::GetLayersCount () noexcept const
```




<hr>



### function GetSamplesCount 

```C++
SR_NODISCARD uint8_t SR_GTYPES_NS::Framebuffer::GetSamplesCount () const
```




<hr>



### function GetSize 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector2 SR_GTYPES_NS::Framebuffer::GetSize () const
```




<hr>



### function GetWidth 

```C++
SR_NODISCARD uint32_t SR_GTYPES_NS::Framebuffer::GetWidth () const
```




<hr>



### function IsDepthEnabled 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Framebuffer::IsDepthEnabled () const
```




<hr>



### function IsDirty 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Framebuffer::IsDirty () const
```




<hr>



### function IsFileResource 

_является ли ресурс файловым_ 
```C++
inline virtual SR_NODISCARD bool SR_GTYPES_NS::Framebuffer::IsFileResource () noexcept override const
```



Implements [*SR\_UTILS\_NS::IResource::IsFileResource*](classSR__UTILS__NS_1_1IResource.md#function-isfileresource)


<hr>



### function IsValid 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Framebuffer::IsValid () const
```




<hr>



### function SetDepthAspect 

```C++
void SR_GTYPES_NS::Framebuffer::SetDepthAspect (
    ImageAspect depthAspect
) 
```




<hr>



### function SetDepthEnabled 

```C++
void SR_GTYPES_NS::Framebuffer::SetDepthEnabled (
    bool depthEnabled
) 
```




<hr>



### function SetDirty 

```C++
void SR_GTYPES_NS::Framebuffer::SetDirty () 
```




<hr>



### function SetFeatures 

```C++
void SR_GTYPES_NS::Framebuffer::SetFeatures (
    const FrameBufferFeatures & features
) 
```




<hr>



### function SetLayersCount 

```C++
void SR_GTYPES_NS::Framebuffer::SetLayersCount (
    uint32_t layersCount
) 
```




<hr>



### function SetSampleCount 

```C++
void SR_GTYPES_NS::Framebuffer::SetSampleCount (
    uint8_t samples
) 
```




<hr>



### function SetSize 

```C++
void SR_GTYPES_NS::Framebuffer::SetSize (
    const SR_MATH_NS::IVector2 & size
) 
```




<hr>



### function SetViewportScissor 

```C++
void SR_GTYPES_NS::Framebuffer::SetViewportScissor () 
```




<hr>



### function Update 

```C++
bool SR_GTYPES_NS::Framebuffer::Update () 
```




<hr>
## Public Static Functions Documentation




### function Create [1/6]

```C++
static Ptr SR_GTYPES_NS::Framebuffer::Create (
    uint32_t images,
    const SR_MATH_NS::IVector2 & size
) 
```




<hr>



### function Create [2/6]

```C++
static Ptr SR_GTYPES_NS::Framebuffer::Create (
    const std::list< ImageFormat > & colors,
    ImageFormat depth
) 
```




<hr>



### function Create [3/6]

```C++
static Ptr SR_GTYPES_NS::Framebuffer::Create (
    const std::list< ImageFormat > & colors,
    ImageFormat depth,
    const SR_MATH_NS::IVector2 & size
) 
```




<hr>



### function Create [4/6]

```C++
static Ptr SR_GTYPES_NS::Framebuffer::Create (
    const std::list< ImageFormat > & colors,
    ImageFormat depth,
    const SR_MATH_NS::IVector2 & size,
    uint8_t samples
) 
```




<hr>



### function Create [5/6]

```C++
static Ptr SR_GTYPES_NS::Framebuffer::Create (
    const std::list< ImageFormat > & colors,
    ImageFormat depth,
    const SR_MATH_NS::IVector2 & size,
    uint8_t samples,
    uint32_t layersCount
) 
```




<hr>



### function Create [6/6]

```C++
static Ptr SR_GTYPES_NS::Framebuffer::Create (
    const std::list< ImageFormat > & colors,
    ImageFormat depth,
    const SR_MATH_NS::IVector2 & size,
    uint8_t samples,
    uint32_t layersCount,
    ImageAspect depthAspect
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Types/Framebuffer.h`

