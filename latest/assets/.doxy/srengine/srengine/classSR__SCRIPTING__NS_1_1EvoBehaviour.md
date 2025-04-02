

# Class SR\_SCRIPTING\_NS::EvoBehaviour



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**EvoBehaviour**](classSR__SCRIPTING__NS_1_1EvoBehaviour.md)








Inherits the following classes: [SR\_SCRIPTING\_NS::IRawBehaviour](classSR__SCRIPTING__NS_1_1IRawBehaviour.md)


















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
|   | [**EvoBehaviour**](#function-evobehaviour) () <br> |
| virtual Properties | [**GetProperties**](#function-getproperties) () override const<br> |
| virtual std::any | [**GetProperty**](#function-getproperty) (const std::string & id) override const<br> |
| virtual void | [**SetComponent**](#function-setcomponent) ([**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) \* pBehaviour) override<br> |
| virtual void | [**SetProperty**](#function-setproperty) (const std::string & id, const std::any & val) override<br> |


## Public Functions inherited from SR_SCRIPTING_NS::IRawBehaviour

See [SR\_SCRIPTING\_NS::IRawBehaviour](classSR__SCRIPTING__NS_1_1IRawBehaviour.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Awake**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-awake) () = 0<br> |
| virtual void | [**FixedUpdate**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-fixedupdate) () = 0<br> |
| virtual Properties | [**GetProperties**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-getproperties) () const = 0<br> |
| virtual std::any | [**GetProperty**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-getproperty) (const std::string & id) const = 0<br> |
|   | [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-irawbehaviour) (uint64\_t hashName) <br> |
| virtual bool | [**Load**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-load-12) () override<br> |
| virtual void | [**OnAttached**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-onattached) () = 0<br> |
| virtual void | [**OnCollisionEnter**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-oncollisionenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnCollisionExit**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-oncollisionexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnCollisionStay**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-oncollisionstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnDestroy**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ondestroy) () = 0<br> |
| virtual void | [**OnDetached**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ondetached) () = 0<br> |
| virtual void | [**OnDisable**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ondisable) () = 0<br> |
| virtual void | [**OnEnable**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-onenable) () = 0<br> |
| virtual void | [**OnReloadDone**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-onreloaddone) () override<br> |
| virtual void | [**OnTransformSet**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontransformset) () = 0<br> |
| virtual void | [**OnTriggerEnter**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontriggerenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnTriggerExit**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontriggerexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual void | [**OnTriggerStay**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontriggerstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) = 0<br> |
| virtual bool | [**Reload**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-reload) () override<br> |
| virtual void | [**SetComponent**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-setcomponent) ([**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) \* pBehaviour) <br> |
| virtual void | [**SetProperty**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-setproperty) (const std::string & id, const std::any & val) = 0<br> |
| virtual void | [**Start**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-start) () = 0<br> |
| virtual bool | [**Unload**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-unload) () override<br> |
| virtual void | [**Update**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-update) (float\_t dt) = 0<br> |


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




## Public Static Functions inherited from SR_SCRIPTING_NS::IRawBehaviour

See [SR\_SCRIPTING\_NS::IRawBehaviour](classSR__SCRIPTING__NS_1_1IRawBehaviour.md)

| Type | Name |
| ---: | :--- |
|  [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md) \* | [**Load**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-load-22) ([**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) path) <br> |




































## Protected Attributes inherited from SR_SCRIPTING_NS::IRawBehaviour

See [SR\_SCRIPTING\_NS::IRawBehaviour](classSR__SCRIPTING__NS_1_1IRawBehaviour.md)

| Type | Name |
| ---: | :--- |
|  [**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md) \* | [**m\_component**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#variable-m_component)   = `nullptr`<br> |
|  bool | [**m\_hasErrors**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#variable-m_haserrors)   = `false`<br> |


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




























































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Awake**](#function-awake) () override<br> |
| virtual void | [**FixedUpdate**](#function-fixedupdate) () override<br> |
| virtual SR\_NODISCARD uint64\_t | [**GetFileHash**](#function-getfilehash) () override const<br> |
| virtual bool | [**Load**](#function-load) () override<br> |
| virtual void | [**OnAttached**](#function-onattached) () override<br> |
| virtual void | [**OnCollisionEnter**](#function-oncollisionenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnCollisionExit**](#function-oncollisionexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnCollisionStay**](#function-oncollisionstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br> |
| virtual void | [**OnDetached**](#function-ondetached) () override<br> |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |
| virtual void | [**OnTransformSet**](#function-ontransformset) () override<br> |
| virtual void | [**OnTriggerEnter**](#function-ontriggerenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnTriggerExit**](#function-ontriggerexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnTriggerStay**](#function-ontriggerstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**Start**](#function-start) () override<br> |
| virtual bool | [**Unload**](#function-unload) () override<br> |
| virtual void | [**Update**](#function-update) (float\_t dt) override<br> |




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




### function EvoBehaviour 

```C++
inline SR_SCRIPTING_NS::EvoBehaviour::EvoBehaviour () 
```




<hr>



### function GetProperties 

```C++
virtual Properties SR_SCRIPTING_NS::EvoBehaviour::GetProperties () override const
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::GetProperties*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-getproperties)


<hr>



### function GetProperty 

```C++
virtual std::any SR_SCRIPTING_NS::EvoBehaviour::GetProperty (
    const std::string & id
) override const
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::GetProperty*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-getproperty)


<hr>



### function SetComponent 

```C++
inline virtual void SR_SCRIPTING_NS::EvoBehaviour::SetComponent (
    Behaviour * pBehaviour
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::SetComponent*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-setcomponent)


<hr>



### function SetProperty 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::SetProperty (
    const std::string & id,
    const std::any & val
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::SetProperty*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-setproperty)


<hr>
## Protected Functions Documentation




### function Awake 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::Awake () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::Awake*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-awake)


<hr>



### function FixedUpdate 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::FixedUpdate () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::FixedUpdate*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-fixedupdate)


<hr>



### function GetFileHash 

```C++
virtual SR_NODISCARD uint64_t SR_SCRIPTING_NS::EvoBehaviour::GetFileHash () override const
```



Implements [*SR\_UTILS\_NS::IResource::GetFileHash*](classSR__UTILS__NS_1_1IResource.md#function-getfilehash)


<hr>



### function Load 

```C++
virtual bool SR_SCRIPTING_NS::EvoBehaviour::Load () override
```



Implements [*SR\_UTILS\_NS::IResource::Load*](classSR__UTILS__NS_1_1IResource.md#function-load)


<hr>



### function OnAttached 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnAttached () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnAttached*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-onattached)


<hr>



### function OnCollisionEnter 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnCollisionEnter (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnCollisionEnter*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-oncollisionenter)


<hr>



### function OnCollisionExit 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnCollisionExit (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnCollisionExit*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-oncollisionexit)


<hr>



### function OnCollisionStay 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnCollisionStay (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnCollisionStay*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-oncollisionstay)


<hr>



### function OnDestroy 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnDestroy () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnDestroy*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ondestroy)


<hr>



### function OnDetached 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnDetached () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnDetached*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ondetached)


<hr>



### function OnDisable 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnDisable () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnDisable*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnEnable () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnEnable*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-onenable)


<hr>



### function OnTransformSet 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnTransformSet () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnTransformSet*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontransformset)


<hr>



### function OnTriggerEnter 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnTriggerEnter (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnTriggerEnter*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontriggerenter)


<hr>



### function OnTriggerExit 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnTriggerExit (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnTriggerExit*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontriggerexit)


<hr>



### function OnTriggerStay 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::OnTriggerStay (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::OnTriggerStay*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-ontriggerstay)


<hr>



### function Start 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::Start () override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::Start*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-start)


<hr>



### function Unload 

```C++
virtual bool SR_SCRIPTING_NS::EvoBehaviour::Unload () override
```



Implements [*SR\_UTILS\_NS::IResource::Unload*](classSR__UTILS__NS_1_1IResource.md#function-unload)


<hr>



### function Update 

```C++
virtual void SR_SCRIPTING_NS::EvoBehaviour::Update (
    float_t dt
) override
```



Implements [*SR\_SCRIPTING\_NS::IRawBehaviour::Update*](classSR__SCRIPTING__NS_1_1IRawBehaviour.md#function-update)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Impl/EvoBehaviour.h`

