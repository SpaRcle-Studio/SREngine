

# Class SR\_WORLD\_NS::ScenePrefabLogic



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**ScenePrefabLogic**](classSR__WORLD__NS_1_1ScenePrefabLogic.md)








Inherits the following classes: [SR\_WORLD\_NS::SceneLogic](classSR__WORLD__NS_1_1SceneLogic.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**ScenePrefabLogic**](classSR__WORLD__NS_1_1ScenePrefabLogic.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_WORLD_NS::SceneLogic

See [SR\_WORLD\_NS::SceneLogic](classSR__WORLD__NS_1_1SceneLogic.md)

| Type | Name |
| ---: | :--- |
| typedef [**SceneLogic**](classSR__WORLD__NS_1_1SceneLogic.md) | [**OriginType**](classSR__WORLD__NS_1_1SceneLogic.md#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SceneLogic**](classSR__WORLD__NS_1_1SceneLogic.md) &gt; | [**Ptr**](classSR__WORLD__NS_1_1SceneLogic.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**SceneObjectPtr**](classSR__WORLD__NS_1_1SceneLogic.md#typedef-sceneobjectptr)  <br> |
| typedef std::vector&lt; SceneObjectPtr &gt; | [**SceneObjects**](classSR__WORLD__NS_1_1SceneLogic.md#typedef-sceneobjects)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**ScenePtr**](classSR__WORLD__NS_1_1SceneLogic.md#typedef-sceneptr)  <br> |


## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |




## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |
















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**GetPrefabRoot**](#function-getprefabroot) () noexcept const<br> |
| virtual SR\_NODISCARD StringAtom | [**GetSceneExtension**](#function-getsceneextension) () noexcept override const<br> |
| virtual SR\_NODISCARD SceneLogicType | [**GetType**](#function-gettype) () noexcept override const<br> |
| virtual void | [**InitLogic**](#function-initlogic) () override<br> |
| virtual SR\_NODISCARD bool | [**IsAllowedRootSave**](#function-isallowedrootsave) () noexcept override const<br> |
| virtual bool | [**LoadLogic**](#function-loadlogic) (IDeserializer & deserializer, const Path & path) override<br> |
| virtual bool | [**SaveLogic**](#function-savelogic) (ISerializer & serializer, const Path & path) override<br> |
|  void | [**SetCustomSOData**](#function-setcustomsodata) (IDeserializer::UniquePtr pCustomData) <br> |


## Public Functions inherited from SR_WORLD_NS::SceneLogic

See [SR\_WORLD\_NS::SceneLogic](classSR__WORLD__NS_1_1SceneLogic.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Destroy**](classSR__WORLD__NS_1_1SceneLogic.md#function-destroy) () <br> |
|  SR\_NODISCARD const ScenePtr & | [**GetScene**](classSR__WORLD__NS_1_1SceneLogic.md#function-getscene) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetSceneDataPath**](classSR__WORLD__NS_1_1SceneLogic.md#function-getscenedatapath) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |
| virtual SR\_NODISCARD StringAtom | [**GetSceneExtension**](classSR__WORLD__NS_1_1SceneLogic.md#function-getsceneextension) () noexcept const = 0<br> |
| virtual SR\_NODISCARD SceneLogicType | [**GetType**](classSR__WORLD__NS_1_1SceneLogic.md#function-gettype) () noexcept const = 0<br> |
| virtual void | [**InitLogic**](classSR__WORLD__NS_1_1SceneLogic.md#function-initlogic) () <br> |
| virtual SR\_NODISCARD bool | [**IsAllowedRootSave**](classSR__WORLD__NS_1_1SceneLogic.md#function-isallowedrootsave) () noexcept const<br> |
| virtual bool | [**LoadLogic**](classSR__WORLD__NS_1_1SceneLogic.md#function-loadlogic) (IDeserializer & deserializer, const Path & path) <br> |
| virtual void | [**Prepare**](classSR__WORLD__NS_1_1SceneLogic.md#function-prepare) () <br> |
| virtual bool | [**Reload**](classSR__WORLD__NS_1_1SceneLogic.md#function-reload) () <br> |
| virtual bool | [**SaveLogic**](classSR__WORLD__NS_1_1SceneLogic.md#function-savelogic) (ISerializer & serializer, const Path & path) <br> |
|   | [**SceneLogic**](classSR__WORLD__NS_1_1SceneLogic.md#function-scenelogic) () <br> |
| virtual void | [**SetScene**](classSR__WORLD__NS_1_1SceneLogic.md#function-setscene) (const ScenePtr & pScene) <br> |
| virtual void | [**Update**](classSR__WORLD__NS_1_1SceneLogic.md#function-update) (float\_t dt) <br> |


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


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**SaveSOAsPrefab**](#function-savesoasprefab) (ISerializer & serializer, const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; & pSO) <br> |






## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |


## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |






























## Protected Attributes inherited from SR_WORLD_NS::SceneLogic

See [SR\_WORLD\_NS::SceneLogic](classSR__WORLD__NS_1_1SceneLogic.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__WORLD__NS_1_1SceneLogic.md#variable-m_mutex)  <br> |
|  ScenePtr | [**m\_scene**](classSR__WORLD__NS_1_1SceneLogic.md#variable-m_scene)  <br> |








## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |














































































































## Public Types Documentation




### typedef Ptr 

```C++
using SR_WORLD_NS::ScenePrefabLogic::Ptr =  SR_HTYPES_NS::SharedPtr<ScenePrefabLogic>;
```




<hr>
## Public Functions Documentation




### function GetPrefabRoot 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < SceneObject > SR_WORLD_NS::ScenePrefabLogic::GetPrefabRoot () noexcept const
```




<hr>



### function GetSceneExtension 

```C++
inline virtual SR_NODISCARD StringAtom SR_WORLD_NS::ScenePrefabLogic::GetSceneExtension () noexcept override const
```



Implements [*SR\_WORLD\_NS::SceneLogic::GetSceneExtension*](classSR__WORLD__NS_1_1SceneLogic.md#function-getsceneextension)


<hr>



### function GetType 

```C++
inline virtual SR_NODISCARD SceneLogicType SR_WORLD_NS::ScenePrefabLogic::GetType () noexcept override const
```



Implements [*SR\_WORLD\_NS::SceneLogic::GetType*](classSR__WORLD__NS_1_1SceneLogic.md#function-gettype)


<hr>



### function InitLogic 

```C++
virtual void SR_WORLD_NS::ScenePrefabLogic::InitLogic () override
```



Implements [*SR\_WORLD\_NS::SceneLogic::InitLogic*](classSR__WORLD__NS_1_1SceneLogic.md#function-initlogic)


<hr>



### function IsAllowedRootSave 

```C++
inline virtual SR_NODISCARD bool SR_WORLD_NS::ScenePrefabLogic::IsAllowedRootSave () noexcept override const
```



Implements [*SR\_WORLD\_NS::SceneLogic::IsAllowedRootSave*](classSR__WORLD__NS_1_1SceneLogic.md#function-isallowedrootsave)


<hr>



### function LoadLogic 

```C++
virtual bool SR_WORLD_NS::ScenePrefabLogic::LoadLogic (
    IDeserializer & deserializer,
    const Path & path
) override
```



Implements [*SR\_WORLD\_NS::SceneLogic::LoadLogic*](classSR__WORLD__NS_1_1SceneLogic.md#function-loadlogic)


<hr>



### function SaveLogic 

```C++
virtual bool SR_WORLD_NS::ScenePrefabLogic::SaveLogic (
    ISerializer & serializer,
    const Path & path
) override
```



Implements [*SR\_WORLD\_NS::SceneLogic::SaveLogic*](classSR__WORLD__NS_1_1SceneLogic.md#function-savelogic)


<hr>



### function SetCustomSOData 

```C++
void SR_WORLD_NS::ScenePrefabLogic::SetCustomSOData (
    IDeserializer::UniquePtr pCustomData
) 
```




<hr>
## Public Static Functions Documentation




### function SaveSOAsPrefab 

```C++
static bool SR_WORLD_NS::ScenePrefabLogic::SaveSOAsPrefab (
    ISerializer & serializer,
    const SR_HTYPES_NS::SharedPtr < SceneObject > & pSO
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/World/ScenePrefabLogic.h`

