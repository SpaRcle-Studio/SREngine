

# Class SR\_UTILS\_NS::EntityRef

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EntityRef**](classSR__UTILS__NS_1_1EntityRef.md)








Inherits the following classes: [SR\_UTILS\_NS::EntityRefBase](classSR__UTILS__NS_1_1EntityRefBase.md)


















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Get**](#function-get) () noexcept const<br> |
| virtual SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetTypeName**](#function-gettypename) () noexcept override const<br> |


## Public Functions inherited from SR_UTILS_NS::EntityRefBase

See [SR\_UTILS\_NS::EntityRefBase](classSR__UTILS__NS_1_1EntityRefBase.md)

| Type | Name |
| ---: | :--- |
|   | [**EntityRefBase**](classSR__UTILS__NS_1_1EntityRefBase.md#function-entityrefbase) () <br> |
|  SR\_NODISCARD const Entity::Ptr & | [**GetEntity**](classSR__UTILS__NS_1_1EntityRefBase.md#function-getentity) () noexcept const<br> |
|  SR\_NODISCARD EntityId | [**GetEntityId**](classSR__UTILS__NS_1_1EntityRefBase.md#function-getentityid) () noexcept const<br> |
| virtual SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetTypeName**](classSR__UTILS__NS_1_1EntityRefBase.md#function-gettypename) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResolved**](classSR__UTILS__NS_1_1EntityRefBase.md#function-isresolved) () noexcept const<br> |
|  void | [**OnEntityIdReplaced**](classSR__UTILS__NS_1_1EntityRefBase.md#function-onentityidreplaced) (const EntityReplaceMap & replaceMap) <br> |
|  void | [**Resolve**](classSR__UTILS__NS_1_1EntityRefBase.md#function-resolve) () noexcept const<br> |
|  void | [**SetEntityId**](classSR__UTILS__NS_1_1EntityRefBase.md#function-setentityid) (EntityId entityId) noexcept<br> |
|  SR\_NODISCARD | [**operator bool**](classSR__UTILS__NS_1_1EntityRefBase.md#function-operator-bool) () noexcept const<br> |


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








## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |


































































































## Public Functions Documentation




### function Get 

```C++
inline SR_NODISCARD SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::EntityRef::Get () noexcept const
```




<hr>



### function GetTypeName 

```C++
inline virtual SR_NODISCARD StringAtom SR_UTILS_NS::EntityRef::GetTypeName () noexcept override const
```



Implements [*SR\_UTILS\_NS::EntityRefBase::GetTypeName*](classSR__UTILS__NS_1_1EntityRefBase.md#function-gettypename)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/EntityRef.h`

