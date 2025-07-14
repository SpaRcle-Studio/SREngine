

# Class SR\_UTILS\_NS::IResource



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IResource**](classSR__UTILS__NS_1_1IResource.md)








Inherits the following classes: [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md),  [SR\_UTILS\_NS::SubscriptionHolder](classSR__UTILS__NS_1_1SubscriptionHolder.md),  [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::AnimationClip](classSR__ANIMATIONS__NS_1_1AnimationClip.md),  [SR\_AUDIO\_NS::RawSound](classSR__AUDIO__NS_1_1RawSound.md),  [SR\_AUDIO\_NS::Sound](classSR__AUDIO__NS_1_1Sound.md),  [SR\_GRAPH\_NS::FileMaterialResource](classSR__GRAPH__NS_1_1FileMaterialResource.md),  [SR\_GTYPES\_NS::Font](classSR__GTYPES__NS_1_1Font.md),  [SR\_GTYPES\_NS::Framebuffer](classSR__GTYPES__NS_1_1Framebuffer.md),  [SR\_GTYPES\_NS::Shader](classSR__GTYPES__NS_1_1Shader.md),  [SR\_GTYPES\_NS::Skybox](classSR__GTYPES__NS_1_1Skybox.md),  [SR\_GTYPES\_NS::Texture](classSR__GTYPES__NS_1_1Texture.md),  [SR\_SRLM\_NS::LogicalMachine](classSR__SRLM__NS_1_1LogicalMachine.md),  [SR\_UTILS\_NS::Asset](classSR__UTILS__NS_1_1Asset.md),  [SR\_UTILS\_NS::Prefab](classSR__UTILS__NS_1_1Prefab.md)












## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**LoadState**](#enum-loadstate)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IResource**](classSR__UTILS__NS_1_1IResource.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| enum uint8\_t | [**RemoveUPResult**](#enum-removeupresult)  <br> |


## Public Types inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1ResourceContainer.md#typedef-ptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |






## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |


















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
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourceId**](#function-getresourceid) () noexcept const<br> |
|  SR\_NODISCARD ResourceInfoWeakPtr | [**GetResourceInfo**](#function-getresourceinfo) () noexcept const<br> |
|  SR\_NODISCARD LoadState | [**GetResourceLoadState**](#function-getresourceloadstate) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetResourcePath**](#function-getresourcepath) () const<br> |
|   | [**IResource**](#function-iresource) () <br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**InitializeResourcePath**](#function-initializeresourcepath) () const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](#function-isalive) () const<br> |
| virtual SR\_NODISCARD bool | [**IsAllowedToRevive**](#function-isallowedtorevive) () const<br> |
|  SR\_NODISCARD bool | [**IsDestroyed**](#function-isdestroyed) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFileResource**](#function-isfileresource) () noexcept const<br>_является ли ресурс файловым_  |
|  SR\_NODISCARD bool | [**IsForceDestroyed**](#function-isforcedestroyed) () const<br> |
|  SR\_NODISCARD bool | [**IsLoaded**](#function-isloaded) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](#function-isregistered) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceFromMemory**](#function-isresourcefrommemory) () noexcept const<br> |
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
|   | [**~IResource**](#function-iresource) () override<br> |


## Public Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-adddependency) (const ResourceContainer::Ptr & pContainer) <br> |
|  SR\_NODISCARD const std::unordered\_set&lt; ResourceContainer::Ptr &gt; & | [**GetContainerParents**](classSR__UTILS__NS_1_1ResourceContainer.md#function-getcontainerparents) () const<br> |
|  void | [**RemoveDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-removedependency) (const ResourceContainer::Ptr & pContainer) <br> |
|   | [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () <br> |
|   | [**~ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtr.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SharedPtr.md#function-unlock) () noexcept const<br> |
|  bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer) () = 0<br> |
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer) () = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () <br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |


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
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |






## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |








## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |






























## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::atomic&lt; uint16\_t &gt; | [**m\_countUses**](#variable-m_countuses)   = `0`<br>_не рекомендуется вручную обращаться к счетчику при наследовании_  |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUnUseStackTraces**](#variable-m_debugunusestacktraces)  <br> |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUseStackTraces**](#variable-m_debugusestacktraces)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_isFromMemory**](#variable-m_isfrommemory)   = `false`<br> |
|  std::atomic&lt; LoadState &gt; | [**m\_loadState**](#variable-m_loadstate)   = `LoadState::Unknown`<br> |
|  std::list&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileWatcher**](classSR__UTILS__NS_1_1FileWatcher.md) &gt; &gt; | [**m\_watchers**](#variable-m_watchers)  <br> |






## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |












































































































## Protected Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnResourceUpdated**](classSR__UTILS__NS_1_1ResourceContainer.md#function-onresourceupdated) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer, int32\_t depth) <br> |
|  void | [**UpdateResources**](classSR__UTILS__NS_1_1ResourceContainer.md#function-updateresources) (int32\_t depth=0) <br> |


























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
using SR_UTILS_NS::IResource::Ptr =  SR_HTYPES_NS::SharedPtr<IResource>;
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



### function GetResourcePath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_UTILS_NS::IResource::GetResourcePath () const
```




<hr>



### function IResource 

```C++
SR_UTILS_NS::IResource::IResource () 
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



### function ~IResource 

```C++
SR_UTILS_NS::IResource::~IResource () override
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



### variable m\_watchers 

```C++
std::list<SR_HTYPES_NS::SharedPtr<FileWatcher> > SR_UTILS_NS::IResource::m_watchers;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Resources/IResource.h`

