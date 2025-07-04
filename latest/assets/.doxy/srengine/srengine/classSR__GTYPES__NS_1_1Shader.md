

# Class SR\_GTYPES\_NS::Shader



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**Shader**](classSR__GTYPES__NS_1_1Shader.md)








Inherits the following classes: [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md),  Memory::IGraphicsResource














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**Ptr**](#typedef-ptr)  <br> |


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
|  bool | [**AttachDescriptorSets**](#function-attachdescriptorsets) () <br> |
|  bool | [**BeginSharedUBO**](#function-beginsharedubo) () <br> |
|  void | [**BindSSBO**](#function-bindssbo) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, uint32\_t ssbo) noexcept<br> |
|  void | [**Dispatch**](#function-dispatch-12) (uint32\_t x, uint32\_t y, uint32\_t z) <br> |
|  void | [**Dispatch**](#function-dispatch-22) () <br> |
|  void | [**EndSharedUBO**](#function-endsharedubo) () <br> |
|  bool | [**Flush**](#function-flush) () const<br> |
|  void | [**FlushConstants**](#function-flushconstants) () <br> |
|  void | [**FlushSamplers**](#function-flushsamplers) () <br> |
|  void | [**FreeVideoMemory**](#function-freevideomemory) () override<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetAssociatedPath**](#function-getassociatedpath) () override const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::UVector3 & | [**GetComputeWorkGroupSize**](#function-getcomputeworkgroupsize) () noexcept const<br> |
|  SR\_DEPRECATED SR\_NODISCARD int32\_t | [**GetID**](#function-getid) () <br> |
|  SR\_NODISCARD int32\_t | [**GetId**](#function-getid) () noexcept<br> |
|  SR\_NODISCARD ShaderProperties | [**GetProperties**](#function-getproperties) () <br> |
|  SR\_NODISCARD const ShaderSamplers & | [**GetSamplers**](#function-getsamplers) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetSamplersCount**](#function-getsamplerscount) () const<br> |
|  SR\_NODISCARD SR\_SRSL\_NS::ShaderType | [**GetType**](#function-gettype) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetUBOBlockSize**](#function-getuboblocksize) () const<br> |
|  SR\_NODISCARD ShaderProgram | [**GetVirtualProgram**](#function-getvirtualprogram) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasErrors**](#function-haserrors) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasSSBOBindings**](#function-hasssbobindings) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasSharedUBO**](#function-hassharedubo) () noexcept const<br> |
|  bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsAvailable**](#function-isavailable) () const<br> |
|  SR\_NODISCARD bool | [**IsBlendEnabled**](#function-isblendenabled) () const<br> |
|  SR\_NODISCARD bool | [**IsSamplersValid**](#function-issamplersvalid) () const<br> |
|  SR\_NODISCARD bool | [**Ready**](#function-ready) () const<br> |
|  void | [**ResetUBOToDefaults**](#function-resetubotodefaults) () <br> |
|  void SR\_FASTCALL | [**SetBool**](#function-setbool) (uint64\_t hashId, bool v) noexcept<br> |
|  void SR\_FASTCALL | [**SetColor**](#function-setcolor) (uint64\_t hashId, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstBool**](#function-setconstbool) (uint64\_t hashId, bool v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstColor**](#function-setconstcolor) (uint64\_t hashId, const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstFloat**](#function-setconstfloat) (uint64\_t hashId, float\_t v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstIVec2**](#function-setconstivec2) (uint64\_t hashId, const SR\_MATH\_NS::IVector2 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstInt**](#function-setconstint) (uint64\_t hashId, int32\_t v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstMat4**](#function-setconstmat4) (uint64\_t hashId, const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstVec2**](#function-setconstvec2) (uint64\_t hashId, const SR\_MATH\_NS::FVector2 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstVec3**](#function-setconstvec3) (uint64\_t hashId, const SR\_MATH\_NS::FVector3 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetConstVec4**](#function-setconstvec4) (uint64\_t hashId, const SR\_MATH\_NS::FVector4 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetFloat**](#function-setfloat) (uint64\_t hashId, float\_t v) noexcept<br> |
|  void SR\_FASTCALL | [**SetIVec2**](#function-setivec2) (uint64\_t hashId, const SR\_MATH\_NS::IVector2 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetInt**](#function-setint) (uint64\_t hashId, int32\_t v) noexcept<br> |
|  void SR\_FASTCALL | [**SetMat4**](#function-setmat4) (uint64\_t hashId, const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetRect**](#function-setrect) (uint64\_t hashId, const SR\_MATH\_NS::FRect & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetSampler2D**](#function-setsampler2d-12) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, [**Texture**](classSR__GTYPES__NS_1_1Texture.md) \* sampler) noexcept<br> |
|  void SR\_FASTCALL | [**SetSampler2D**](#function-setsampler2d-22) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, int32\_t sampler) noexcept<br> |
|  void SR\_FASTCALL | [**SetSamplerCube**](#function-setsamplercube) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, int32\_t sampler) noexcept<br> |
|  void | [**SetValue**](#function-setvalue) (uint64\_t hashId, const T \* v) noexcept<br> |
|  void SR\_FASTCALL | [**SetVec2**](#function-setvec2) (uint64\_t hashId, const SR\_MATH\_NS::FVector2 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetVec3**](#function-setvec3) (uint64\_t hashId, const SR\_MATH\_NS::FVector3 & v) noexcept<br> |
|  void SR\_FASTCALL | [**SetVec4**](#function-setvec4) (uint64\_t hashId, const SR\_MATH\_NS::FVector4 & v) noexcept<br> |
| virtual void | [**StartWatch**](#function-startwatch) () override<br> |
|  void | [**UnUse**](#function-unuse) () noexcept<br> |
|  ShaderBindResult | [**Use**](#function-use) () noexcept<br> |


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
|  [**Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**Load**](#function-load-12) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & rawPath) <br> |
































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
| virtual bool | [**IsAllowedToRevive**](#function-isallowedtorevive) () override const<br> |
| virtual bool | [**Load**](#function-load-22) () override<br> |
|  void | [**LoadDefaultSampler**](#function-loaddefaultsampler) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual void | [**OnReloadDone**](#function-onreloaddone) () override<br> |
| virtual void | [**ReviveResource**](#function-reviveresource) () override<br> |
| virtual bool | [**Unload**](#function-unload) () override<br> |
|  void | [**UnloadDefaultSamplers**](#function-unloaddefaultsamplers) () <br> |


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














## Public Types Documentation




### typedef Ptr 

```C++
using SR_GTYPES_NS::Shader::Ptr =  Shader*;
```




<hr>
## Public Functions Documentation




### function AttachDescriptorSets 

```C++
bool SR_GTYPES_NS::Shader::AttachDescriptorSets () 
```




<hr>



### function BeginSharedUBO 

```C++
bool SR_GTYPES_NS::Shader::BeginSharedUBO () 
```




<hr>



### function BindSSBO 

```C++
void SR_GTYPES_NS::Shader::BindSSBO (
    SR_UTILS_NS::StringAtom name,
    uint32_t ssbo
) noexcept
```




<hr>



### function Dispatch [1/2]

```C++
void SR_GTYPES_NS::Shader::Dispatch (
    uint32_t x,
    uint32_t y,
    uint32_t z
) 
```




<hr>



### function Dispatch [2/2]

```C++
void SR_GTYPES_NS::Shader::Dispatch () 
```




<hr>



### function EndSharedUBO 

```C++
void SR_GTYPES_NS::Shader::EndSharedUBO () 
```




<hr>



### function Flush 

```C++
bool SR_GTYPES_NS::Shader::Flush () const
```




<hr>



### function FlushConstants 

```C++
void SR_GTYPES_NS::Shader::FlushConstants () 
```




<hr>



### function FlushSamplers 

```C++
void SR_GTYPES_NS::Shader::FlushSamplers () 
```




<hr>



### function FreeVideoMemory 

```C++
void SR_GTYPES_NS::Shader::FreeVideoMemory () override
```




<hr>



### function GetAssociatedPath 

```C++
virtual SR_NODISCARD SR_UTILS_NS::Path SR_GTYPES_NS::Shader::GetAssociatedPath () override const
```



Implements [*SR\_UTILS\_NS::IResource::GetAssociatedPath*](classSR__UTILS__NS_1_1IResource.md#function-getassociatedpath)


<hr>



### function GetComputeWorkGroupSize 

```C++
inline SR_NODISCARD const SR_MATH_NS::UVector3 & SR_GTYPES_NS::Shader::GetComputeWorkGroupSize () noexcept const
```




<hr>



### function GetID 

```C++
SR_DEPRECATED SR_NODISCARD int32_t SR_GTYPES_NS::Shader::GetID () 
```




<hr>



### function GetId 

```C++
SR_NODISCARD int32_t SR_GTYPES_NS::Shader::GetId () noexcept
```




<hr>



### function GetProperties 

```C++
SR_NODISCARD ShaderProperties SR_GTYPES_NS::Shader::GetProperties () 
```




<hr>



### function GetSamplers 

```C++
inline SR_NODISCARD const ShaderSamplers & SR_GTYPES_NS::Shader::GetSamplers () noexcept const
```




<hr>



### function GetSamplersCount 

```C++
SR_NODISCARD uint32_t SR_GTYPES_NS::Shader::GetSamplersCount () const
```




<hr>



### function GetType 

```C++
SR_NODISCARD SR_SRSL_NS::ShaderType SR_GTYPES_NS::Shader::GetType () noexcept const
```




<hr>



### function GetUBOBlockSize 

```C++
SR_NODISCARD uint64_t SR_GTYPES_NS::Shader::GetUBOBlockSize () const
```




<hr>



### function GetVirtualProgram 

```C++
inline SR_NODISCARD ShaderProgram SR_GTYPES_NS::Shader::GetVirtualProgram () noexcept const
```




<hr>



### function HasErrors 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Shader::HasErrors () noexcept const
```




<hr>



### function HasSSBOBindings 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Shader::HasSSBOBindings () noexcept const
```




<hr>



### function HasSharedUBO 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Shader::HasSharedUBO () noexcept const
```




<hr>



### function Init 

```C++
bool SR_GTYPES_NS::Shader::Init () 
```




<hr>



### function IsAvailable 

```C++
SR_NODISCARD bool SR_GTYPES_NS::Shader::IsAvailable () const
```




<hr>



### function IsBlendEnabled 

```C++
SR_NODISCARD bool SR_GTYPES_NS::Shader::IsBlendEnabled () const
```




<hr>



### function IsSamplersValid 

```C++
SR_NODISCARD bool SR_GTYPES_NS::Shader::IsSamplersValid () const
```




<hr>



### function Ready 

```C++
SR_NODISCARD bool SR_GTYPES_NS::Shader::Ready () const
```




<hr>



### function ResetUBOToDefaults 

```C++
void SR_GTYPES_NS::Shader::ResetUBOToDefaults () 
```




<hr>



### function SetBool 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetBool (
    uint64_t hashId,
    bool v
) noexcept
```




<hr>



### function SetColor 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetColor (
    uint64_t hashId,
    const SR_MATH_NS::FColor & v
) noexcept
```




<hr>



### function SetConstBool 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstBool (
    uint64_t hashId,
    bool v
) noexcept
```




<hr>



### function SetConstColor 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstColor (
    uint64_t hashId,
    const SR_MATH_NS::FColor & v
) noexcept
```




<hr>



### function SetConstFloat 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstFloat (
    uint64_t hashId,
    float_t v
) noexcept
```




<hr>



### function SetConstIVec2 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstIVec2 (
    uint64_t hashId,
    const SR_MATH_NS::IVector2 & v
) noexcept
```




<hr>



### function SetConstInt 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstInt (
    uint64_t hashId,
    int32_t v
) noexcept
```




<hr>



### function SetConstMat4 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstMat4 (
    uint64_t hashId,
    const SR_MATH_NS::Matrix4x4 & v
) noexcept
```




<hr>



### function SetConstVec2 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstVec2 (
    uint64_t hashId,
    const SR_MATH_NS::FVector2 & v
) noexcept
```




<hr>



### function SetConstVec3 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstVec3 (
    uint64_t hashId,
    const SR_MATH_NS::FVector3 & v
) noexcept
```




<hr>



### function SetConstVec4 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetConstVec4 (
    uint64_t hashId,
    const SR_MATH_NS::FVector4 & v
) noexcept
```




<hr>



### function SetFloat 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetFloat (
    uint64_t hashId,
    float_t v
) noexcept
```




<hr>



### function SetIVec2 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetIVec2 (
    uint64_t hashId,
    const SR_MATH_NS::IVector2 & v
) noexcept
```




<hr>



### function SetInt 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetInt (
    uint64_t hashId,
    int32_t v
) noexcept
```




<hr>



### function SetMat4 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetMat4 (
    uint64_t hashId,
    const SR_MATH_NS::Matrix4x4 & v
) noexcept
```




<hr>



### function SetRect 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetRect (
    uint64_t hashId,
    const SR_MATH_NS::FRect & v
) noexcept
```




<hr>



### function SetSampler2D [1/2]

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetSampler2D (
    SR_UTILS_NS::StringAtom name,
    Texture * sampler
) noexcept
```




<hr>



### function SetSampler2D [2/2]

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetSampler2D (
    SR_UTILS_NS::StringAtom name,
    int32_t sampler
) noexcept
```




<hr>



### function SetSamplerCube 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetSamplerCube (
    SR_UTILS_NS::StringAtom name,
    int32_t sampler
) noexcept
```




<hr>



### function SetValue 

```C++
template<bool constant, typename T>
inline void SR_GTYPES_NS::Shader::SetValue (
    uint64_t hashId,
    const T * v
) noexcept
```




<hr>



### function SetVec2 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetVec2 (
    uint64_t hashId,
    const SR_MATH_NS::FVector2 & v
) noexcept
```




<hr>



### function SetVec3 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetVec3 (
    uint64_t hashId,
    const SR_MATH_NS::FVector3 & v
) noexcept
```




<hr>



### function SetVec4 

```C++
void SR_FASTCALL SR_GTYPES_NS::Shader::SetVec4 (
    uint64_t hashId,
    const SR_MATH_NS::FVector4 & v
) noexcept
```




<hr>



### function StartWatch 

```C++
virtual void SR_GTYPES_NS::Shader::StartWatch () override
```



Implements [*SR\_UTILS\_NS::IResource::StartWatch*](classSR__UTILS__NS_1_1IResource.md#function-startwatch)


<hr>



### function UnUse 

```C++
void SR_GTYPES_NS::Shader::UnUse () noexcept
```




<hr>



### function Use 

```C++
ShaderBindResult SR_GTYPES_NS::Shader::Use () noexcept
```




<hr>
## Public Static Functions Documentation




### function Load [1/2]

```C++
static Shader * SR_GTYPES_NS::Shader::Load (
    const SR_UTILS_NS::Path & rawPath
) 
```




<hr>
## Protected Functions Documentation




### function IsAllowedToRevive 

```C++
virtual bool SR_GTYPES_NS::Shader::IsAllowedToRevive () override const
```



Implements [*SR\_UTILS\_NS::IResource::IsAllowedToRevive*](classSR__UTILS__NS_1_1IResource.md#function-isallowedtorevive)


<hr>



### function Load [2/2]

```C++
virtual bool SR_GTYPES_NS::Shader::Load () override
```



Implements [*SR\_UTILS\_NS::IResource::Load*](classSR__UTILS__NS_1_1IResource.md#function-load)


<hr>



### function LoadDefaultSampler 

```C++
void SR_GTYPES_NS::Shader::LoadDefaultSampler (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function OnReloadDone 

```C++
virtual void SR_GTYPES_NS::Shader::OnReloadDone () override
```



Implements [*SR\_UTILS\_NS::IResource::OnReloadDone*](classSR__UTILS__NS_1_1IResource.md#function-onreloaddone)


<hr>



### function ReviveResource 

```C++
virtual void SR_GTYPES_NS::Shader::ReviveResource () override
```



Implements [*SR\_UTILS\_NS::IResource::ReviveResource*](classSR__UTILS__NS_1_1IResource.md#function-reviveresource)


<hr>



### function Unload 

```C++
virtual bool SR_GTYPES_NS::Shader::Unload () override
```



Implements [*SR\_UTILS\_NS::IResource::Unload*](classSR__UTILS__NS_1_1IResource.md#function-unload)


<hr>



### function UnloadDefaultSamplers 

```C++
void SR_GTYPES_NS::Shader::UnloadDefaultSamplers () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Types/Shader.h`

