

# Class SR\_UTILS\_NS::IResource



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IResource**](classSR__UTILS__NS_1_1IResource.md)








Inherits the following classes: [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md),  [SR\_UTILS\_NS::SubscriptionHolder](classSR__UTILS__NS_1_1SubscriptionHolder.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::AnimationClip](classSR__ANIMATIONS__NS_1_1AnimationClip.md),  [SR\_AUDIO\_NS::RawSound](classSR__AUDIO__NS_1_1RawSound.md),  [SR\_AUDIO\_NS::Sound](classSR__AUDIO__NS_1_1Sound.md),  [SR\_GRAPH\_NS::FileMaterialResource](classSR__GRAPH__NS_1_1FileMaterialResource.md),  [SR\_GTYPES\_NS::Font](classSR__GTYPES__NS_1_1Font.md),  [SR\_GTYPES\_NS::Framebuffer](classSR__GTYPES__NS_1_1Framebuffer.md),  [SR\_GTYPES\_NS::Shader](classSR__GTYPES__NS_1_1Shader.md),  [SR\_GTYPES\_NS::Skybox](classSR__GTYPES__NS_1_1Skybox.md),  [SR\_GTYPES\_NS::Texture](classSR__GTYPES__NS_1_1Texture.md),  [SR\_PTYPES\_NS::PhysicsMaterial](classSR__PTYPES__NS_1_1PhysicsMaterial.md),  [SR\_SRLM\_NS::LogicalMachine](classSR__SRLM__NS_1_1LogicalMachine.md),  [SR\_UTILS\_NS::Prefab](classSR__UTILS__NS_1_1Prefab.md)












## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**LoadState**](#enum-loadstate)  <br> |
| typedef [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**Ptr**](#typedef-ptr)  <br> |
| enum uint8\_t | [**RemoveUPResult**](#enum-removeupresult)  <br> |
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**RELOAD\_BEGIN\_EVENT**](#variable-reload_begin_event)   = `"ReloadBegin"`<br> |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**RELOAD\_DONE\_EVENT**](#variable-reload_done_event)   = `"ReloadDone"`<br> |
































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddUsePoint**](#function-addusepoint) () <br> |
| virtual void | [**CheckResourceUsage**](#function-checkresourceusage) () <br> |
| virtual SR\_NODISCARD [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**CopyResource**](#function-copyresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* destination) const<br> |
| virtual void | [**DeleteResource**](#function-deleteresource) () <br> |
| virtual bool | [**Destroy**](#function-destroy) () <br> |
|  bool | [**Execute**](#function-execute) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; & fun) const<br> |
|  bool | [**ForceDestroy**](#function-forcedestroy) () <br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetAssociatedPath**](#function-getassociatedpath) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetCountUses**](#function-getcountuses) () noexcept const<br> |
| virtual SR\_NODISCARD uint64\_t | [**GetFileHash**](#function-getfilehash) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetLifetime**](#function-getlifetime) () noexcept const<br> |
|  SR\_NODISCARD uint16\_t | [**GetReloadCount**](#function-getreloadcount) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetResourceHash**](#function-getresourcehash) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetResourceHashName**](#function-getresourcehashname) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourceId**](#function-getresourceid) () noexcept const<br> |
|  SR\_NODISCARD ResourceInfoWeakPtr | [**GetResourceInfo**](#function-getresourceinfo) () noexcept const<br> |
|  SR\_NODISCARD LoadState | [**GetResourceLoadState**](#function-getresourceloadstate) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetResourceName**](#function-getresourcename) () const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourcePath**](#function-getresourcepath) () const<br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**InitializeResourcePath**](#function-initializeresourcepath) () const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](#function-isalive) () const<br> |
| virtual SR\_NODISCARD bool | [**IsAllowedToRevive**](#function-isallowedtorevive) () const<br> |
|  SR\_NODISCARD bool | [**IsDestroyed**](#function-isdestroyed) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFileResource**](#function-isfileresource) () noexcept const<br>_является ли ресурс файловым_  |
|  SR\_NODISCARD bool | [**IsForceDestroyed**](#function-isforcedestroyed) () const<br> |
|  SR\_NODISCARD bool | [**IsLoaded**](#function-isloaded) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](#function-isregistered) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceFromMemory**](#function-isresourcefrommemory) () noexcept const<br> |
|  bool | [**IsResourceType**](#function-isresourcetype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceWillBeDeleted**](#function-isresourcewillbedeleted) () const<br> |
|  bool | [**Kill**](#function-kill) () <br> |
| virtual bool | [**Load**](#function-load) () <br> |
| virtual void | [**OnReloadDone**](#function-onreloaddone) () <br> |
| virtual void | [**OnResourceRegistered**](#function-onresourceregistered) () <br> |
| virtual bool | [**Reload**](#function-reload) () <br> |
| virtual RemoveUPResult | [**RemoveUsePoint**](#function-removeusepoint) () <br> |
| virtual void | [**ReviveResource**](#function-reviveresource) () <br> |
|  void | [**SetId**](#function-setid) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, bool autoRegister=true) <br> |
|  void | [**SetLifetime**](#function-setlifetime) (int64\_t lifeTime) <br> |
|  void | [**SetResourceHash**](#function-setresourcehash) (uint64\_t hash) <br> |
|  void | [**SignalWatch**](#function-signalwatch) () <br> |
| virtual void | [**StartWatch**](#function-startwatch) () <br> |
| virtual void | [**StopWatch**](#function-stopwatch) () <br> |
| virtual bool | [**Unload**](#function-unload) () <br> |
|  void | [**UpdateResourceLifeTime**](#function-updateresourcelifetime) () <br> |


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


























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::atomic&lt; uint16\_t &gt; | [**m\_countUses**](#variable-m_countuses)   = `0`<br>_не рекомендуется вручную обращаться к счетчику при наследовании_  |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUnUseStackTraces**](#variable-m_debugunusestacktraces)  <br> |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUseStackTraces**](#variable-m_debugusestacktraces)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_isFromMemory**](#variable-m_isfrommemory)   = `false`<br> |
|  std::atomic&lt; LoadState &gt; | [**m\_loadState**](#variable-m_loadstate)   = `LoadState::Unknown`<br> |
|  const uint64\_t | [**m\_resourceHashName**](#variable-m_resourcehashname)   = `0`<br> |
|  std::list&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileWatcher**](classSR__UTILS__NS_1_1FileWatcher.md) &gt; &gt; | [**m\_watchers**](#variable-m_watchers)  <br> |
































































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**IResource**](#function-iresource) (uint64\_t hashName) <br> |
|   | [**~IResource**](#function-iresource) () override<br> |


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












## Public Types Documentation




### enum LoadState 

```C++
enum SR_UTILS_NS::IResource::LoadState {
    Unknown,
    Loaded,
    Reloading,
    Loading,
    Unloading,
    Unloaded,
    Error
};
```




<hr>



### typedef Ptr 

```C++
using SR_UTILS_NS::IResource::Ptr =  IResource*;
```




<hr>



### enum RemoveUPResult 

```C++
enum SR_UTILS_NS::IResource::RemoveUPResult {
    Delete,
    Destroy,
    Success,
    Error
};
```




<hr>
## Public Attributes Documentation




### variable RELOAD\_BEGIN\_EVENT 

```C++
SR_INLINE_STATIC const StringAtom SR_UTILS_NS::IResource::RELOAD_BEGIN_EVENT;
```




<hr>



### variable RELOAD\_DONE\_EVENT 

```C++
SR_INLINE_STATIC const StringAtom SR_UTILS_NS::IResource::RELOAD_DONE_EVENT;
```




<hr>
## Public Functions Documentation




### function AddUsePoint 

```C++
void SR_UTILS_NS::IResource::AddUsePoint () 
```



Add one point to count uses current resource 


        

<hr>



### function CheckResourceUsage 

```C++
virtual void SR_UTILS_NS::IResource::CheckResourceUsage () 
```




<hr>



### function CopyResource 

```C++
virtual SR_NODISCARD IResource * SR_UTILS_NS::IResource::CopyResource (
    IResource * destination
) const
```




<hr>



### function DeleteResource 

```C++
virtual void SR_UTILS_NS::IResource::DeleteResource () 
```



Вызывается только из [**ResourceManager**](classSR__UTILS__NS_1_1ResourceManager.md) и [**IResource**](classSR__UTILS__NS_1_1IResource.md), удаляет экземпляр класса, или не удаляет, но это уже не его проблема, а того, как он переопределен. Задача данного метода - сделать финальное оповещение что ресурс не нужен и не отслеживается более. 


        

<hr>



### function Destroy 

```C++
virtual bool SR_UTILS_NS::IResource::Destroy () 
```



Call only once \| Register resource to destroy in resource manager 


        

<hr>



### function Execute 

```C++
bool SR_UTILS_NS::IResource::Execute (
    const SR_HTYPES_NS::Function < bool()> & fun
) const
```




<hr>



### function ForceDestroy 

```C++
bool SR_UTILS_NS::IResource::ForceDestroy () 
```




<hr>



### function GetAssociatedPath 

```C++
virtual SR_NODISCARD Path SR_UTILS_NS::IResource::GetAssociatedPath () const
```




<hr>



### function GetCountUses 

```C++
SR_NODISCARD uint16_t SR_UTILS_NS::IResource::GetCountUses () noexcept const
```




<hr>



### function GetFileHash 

```C++
virtual SR_NODISCARD uint64_t SR_UTILS_NS::IResource::GetFileHash () const
```




<hr>



### function GetLifetime 

```C++
inline SR_NODISCARD uint64_t SR_UTILS_NS::IResource::GetLifetime () noexcept const
```




<hr>



### function GetReloadCount 

```C++
SR_NODISCARD uint16_t SR_UTILS_NS::IResource::GetReloadCount () noexcept const
```




<hr>



### function GetResourceHash 

```C++
inline SR_NODISCARD uint64_t SR_UTILS_NS::IResource::GetResourceHash () noexcept const
```




<hr>



### function GetResourceHashName 

```C++
inline SR_NODISCARD uint64_t SR_UTILS_NS::IResource::GetResourceHashName () noexcept const
```




<hr>



### function GetResourceId 

```C++
SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::IResource::GetResourceId () noexcept const
```




<hr>



### function GetResourceInfo 

```C++
inline SR_NODISCARD ResourceInfoWeakPtr SR_UTILS_NS::IResource::GetResourceInfo () noexcept const
```




<hr>



### function GetResourceLoadState 

```C++
inline SR_NODISCARD LoadState SR_UTILS_NS::IResource::GetResourceLoadState () const
```




<hr>



### function GetResourceName 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::IResource::GetResourceName () const
```




<hr>



### function GetResourcePath 

```C++
SR_NODISCARD StringAtom SR_UTILS_NS::IResource::GetResourcePath () const
```




<hr>



### function InitializeResourcePath 

```C++
virtual SR_NODISCARD Path SR_UTILS_NS::IResource::InitializeResourcePath () const
```




<hr>



### function IsAlive 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::IResource::IsAlive () const
```




<hr>



### function IsAllowedToRevive 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IResource::IsAllowedToRevive () const
```




<hr>



### function IsDestroyed 

```C++
SR_NODISCARD bool SR_UTILS_NS::IResource::IsDestroyed () noexcept const
```




<hr>



### function IsFileResource 

_является ли ресурс файловым_ 
```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IResource::IsFileResource () noexcept const
```




<hr>



### function IsForceDestroyed 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::IResource::IsForceDestroyed () const
```




<hr>



### function IsLoaded 

```C++
SR_NODISCARD bool SR_UTILS_NS::IResource::IsLoaded () noexcept const
```




<hr>



### function IsRegistered 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::IResource::IsRegistered () noexcept const
```




<hr>



### function IsResourceFromMemory 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::IResource::IsResourceFromMemory () noexcept const
```




<hr>



### function IsResourceType 

```C++
template<typename T>
inline bool SR_UTILS_NS::IResource::IsResourceType () noexcept const
```




<hr>



### function IsResourceWillBeDeleted 

```C++
SR_NODISCARD bool SR_UTILS_NS::IResource::IsResourceWillBeDeleted () const
```




<hr>



### function Kill 

```C++
bool SR_UTILS_NS::IResource::Kill () 
```




<hr>



### function Load 

```C++
virtual bool SR_UTILS_NS::IResource::Load () 
```




<hr>



### function OnReloadDone 

```C++
virtual void SR_UTILS_NS::IResource::OnReloadDone () 
```




<hr>



### function OnResourceRegistered 

```C++
inline virtual void SR_UTILS_NS::IResource::OnResourceRegistered () 
```




<hr>



### function Reload 

```C++
virtual bool SR_UTILS_NS::IResource::Reload () 
```




<hr>



### function RemoveUsePoint 

```C++
virtual RemoveUPResult SR_UTILS_NS::IResource::RemoveUsePoint () 
```



Remove one point from count uses current resource 


        

<hr>



### function ReviveResource 

```C++
virtual void SR_UTILS_NS::IResource::ReviveResource () 
```




<hr>



### function SetId 

```C++
void SR_UTILS_NS::IResource::SetId (
    SR_UTILS_NS::StringAtom id,
    bool autoRegister=true
) 
```




<hr>



### function SetLifetime 

```C++
inline void SR_UTILS_NS::IResource::SetLifetime (
    int64_t lifeTime
) 
```




<hr>



### function SetResourceHash 

```C++
void SR_UTILS_NS::IResource::SetResourceHash (
    uint64_t hash
) 
```




<hr>



### function SignalWatch 

```C++
void SR_UTILS_NS::IResource::SignalWatch () 
```




<hr>



### function StartWatch 

```C++
virtual void SR_UTILS_NS::IResource::StartWatch () 
```




<hr>



### function StopWatch 

```C++
virtual void SR_UTILS_NS::IResource::StopWatch () 
```




<hr>



### function Unload 

```C++
virtual bool SR_UTILS_NS::IResource::Unload () 
```




<hr>



### function UpdateResourceLifeTime 

```C++
void SR_UTILS_NS::IResource::UpdateResourceLifeTime () 
```




<hr>
## Protected Attributes Documentation




### variable m\_countUses 

_не рекомендуется вручную обращаться к счетчику при наследовании_ 
```C++
std::atomic<uint16_t> SR_UTILS_NS::IResource::m_countUses;
```




<hr>



### variable m\_debugUnUseStackTraces 

```C++
std::list<SR_UTILS_NS::StringAtom> SR_UTILS_NS::IResource::m_debugUnUseStackTraces;
```




<hr>



### variable m\_debugUseStackTraces 

```C++
std::list<SR_UTILS_NS::StringAtom> SR_UTILS_NS::IResource::m_debugUseStackTraces;
```




<hr>



### variable m\_isFromMemory 

```C++
std::atomic<bool> SR_UTILS_NS::IResource::m_isFromMemory;
```




<hr>



### variable m\_loadState 

```C++
std::atomic<LoadState> SR_UTILS_NS::IResource::m_loadState;
```




<hr>



### variable m\_resourceHashName 

```C++
const uint64_t SR_UTILS_NS::IResource::m_resourceHashName;
```




<hr>



### variable m\_watchers 

```C++
std::list<SR_HTYPES_NS::SharedPtr<FileWatcher> > SR_UTILS_NS::IResource::m_watchers;
```




<hr>
## Protected Functions Documentation




### function IResource 

```C++
explicit SR_UTILS_NS::IResource::IResource (
    uint64_t hashName
) 
```




<hr>



### function ~IResource 

```C++
SR_UTILS_NS::IResource::~IResource () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/IResource.h`

