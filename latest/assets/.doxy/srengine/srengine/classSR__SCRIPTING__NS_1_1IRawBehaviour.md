

# Class SR\_SCRIPTING\_NS::IRawBehaviour



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md)








Inherits the following classes: [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)


Inherited by the following classes: [SR\_SCRIPTING\_NS::EvoBehaviour](classSR__SCRIPTING__NS_1_1EvoBehaviour.md)














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
| virtual void | [**Awake**](#function-awake) () = 0<br> |
| virtual void | [**FixedUpdate**](#function-fixedupdate) () = 0<br> |
| virtual Properties | [**GetProperties**](#function-getproperties) () const = 0<br> |
| virtual std::any | [**GetProperty**](#function-getproperty) (const std::string & id) const = 0<br> |
|   | [**IRawBehaviour**](#function-irawbehaviour) (uint64\_t hashName) <br> |
| virtual bool | [**Load**](#function-load-12) () override<br> |
| virtual void | [**OnAttached**](#function-onattached) () = 0<br> |
| virtual void | [**OnCollisionEnter**](#function-oncollisionenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnCollisionExit**](#function-oncollisionexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnCollisionStay**](#function-oncollisionstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnDestroy**](#function-ondestroy) () = 0<br> |
| virtual void | [**OnDetached**](#function-ondetached) () = 0<br> |
| virtual void | [**OnDisable**](#function-ondisable) () = 0<br> |
| virtual void | [**OnEnable**](#function-onenable) () = 0<br> |
| virtual void | [**OnReloadDone**](#function-onreloaddone) () override<br> |
| virtual void | [**OnTransformSet**](#function-ontransformset) () = 0<br> |
| virtual void | [**OnTriggerEnter**](#function-ontriggerenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnTriggerExit**](#function-ontriggerexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnTriggerStay**](#function-ontriggerstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual bool | [**Reload**](#function-reload) () override<br> |
| virtual void | [**SetComponent**](#function-setcomponent) ([**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) \* pBehaviour) <br> |
| virtual void | [**SetProperty**](#function-setproperty) (const std::string & id, const std::any & val) = 0<br> |
| virtual void | [**Start**](#function-start) () = 0<br> |
| virtual bool | [**Unload**](#function-unload) () override<br> |
| virtual void | [**Update**](#function-update) (float\_t dt) = 0<br> |


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
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-12) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) <br> |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-22) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) & message) <br> |
|  SR\_NODISCARD bool | [**HasSubscriptions**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-hassubscriptions) () noexcept const<br> |
|  SR\_NODISCARD [**Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**Subscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscribe) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; && callback) <br> |
|  void | [**Unsubscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-unsubscribe) (const [**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md) \* pSubscription) <br> |
| virtual  | [**~SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md) \* | [**Load**](#function-load-22) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) path) <br> |






























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) \* | [**m\_component**](#variable-m_component)   = `nullptr`<br> |
|  bool | [**m\_hasErrors**](#variable-m_haserrors)   = `false`<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |














## Public Functions Documentation




### function Awake 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::Awake () = 0
```




<hr>



### function FixedUpdate 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::FixedUpdate () = 0
```




<hr>



### function GetProperties 

```C++
virtual Properties SR_SCRIPTING_NS::IRawBehaviour::GetProperties () const = 0
```




<hr>



### function GetProperty 

```C++
virtual std::any SR_SCRIPTING_NS::IRawBehaviour::GetProperty (
    const std::string & id
) const = 0
```




<hr>



### function IRawBehaviour 

```C++
inline explicit SR_SCRIPTING_NS::IRawBehaviour::IRawBehaviour (
    uint64_t hashName
) 
```




<hr>



### function Load [1/2]

```C++
inline virtual bool SR_SCRIPTING_NS::IRawBehaviour::Load () override
```



Implements [*SR\_UTILS\_NS::IResource::Load*](classSR__UTILS__NS_1_1IResource.md#function-load)


<hr>



### function OnAttached 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnAttached () = 0
```




<hr>



### function OnCollisionEnter 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnCollisionEnter (
    const SR_UTILS_NS::CollisionData & data
) = 0
```




<hr>



### function OnCollisionExit 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnCollisionExit (
    const SR_UTILS_NS::CollisionData & data
) = 0
```




<hr>



### function OnCollisionStay 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnCollisionStay (
    const SR_UTILS_NS::CollisionData & data
) = 0
```




<hr>



### function OnDestroy 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnDestroy () = 0
```




<hr>



### function OnDetached 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnDetached () = 0
```




<hr>



### function OnDisable 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnDisable () = 0
```




<hr>



### function OnEnable 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnEnable () = 0
```




<hr>



### function OnReloadDone 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnReloadDone () override
```



Implements [*SR\_UTILS\_NS::IResource::OnReloadDone*](classSR__UTILS__NS_1_1IResource.md#function-onreloaddone)


<hr>



### function OnTransformSet 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnTransformSet () = 0
```




<hr>



### function OnTriggerEnter 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnTriggerEnter (
    const SR_UTILS_NS::CollisionData & data
) = 0
```




<hr>



### function OnTriggerExit 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnTriggerExit (
    const SR_UTILS_NS::CollisionData & data
) = 0
```




<hr>



### function OnTriggerStay 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::OnTriggerStay (
    const SR_UTILS_NS::CollisionData & data
) = 0
```




<hr>



### function Reload 

```C++
virtual bool SR_SCRIPTING_NS::IRawBehaviour::Reload () override
```



Implements [*SR\_UTILS\_NS::IResource::Reload*](classSR__UTILS__NS_1_1IResource.md#function-reload)


<hr>



### function SetComponent 

```C++
inline virtual void SR_SCRIPTING_NS::IRawBehaviour::SetComponent (
    Behaviour * pBehaviour
) 
```




<hr>



### function SetProperty 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::SetProperty (
    const std::string & id,
    const std::any & val
) = 0
```




<hr>



### function Start 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::Start () = 0
```




<hr>



### function Unload 

```C++
inline virtual bool SR_SCRIPTING_NS::IRawBehaviour::Unload () override
```



Implements [*SR\_UTILS\_NS::IResource::Unload*](classSR__UTILS__NS_1_1IResource.md#function-unload)


<hr>



### function Update 

```C++
virtual void SR_SCRIPTING_NS::IRawBehaviour::Update (
    float_t dt
) = 0
```




<hr>
## Public Static Functions Documentation




### function Load [2/2]

```C++
static IRawBehaviour * SR_SCRIPTING_NS::IRawBehaviour::Load (
    SR_UTILS_NS::Path path
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_component 

```C++
Behaviour* SR_SCRIPTING_NS::IRawBehaviour::m_component;
```




<hr>



### variable m\_hasErrors 

```C++
bool SR_SCRIPTING_NS::IRawBehaviour::m_hasErrors;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Base/Behaviour.h`

