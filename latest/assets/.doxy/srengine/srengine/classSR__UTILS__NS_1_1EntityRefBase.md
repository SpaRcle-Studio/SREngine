

# Class SR\_UTILS\_NS::EntityRefBase



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EntityRefBase**](classSR__UTILS__NS_1_1EntityRefBase.md)



_@inspector(EntityRefPropertyDrawer)_ 

* `#include <EntityRef.h>`



Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)


Inherited by the following classes: [SR\_UTILS\_NS::EntityRef](classSR__UTILS__NS_1_1EntityRef.md),  [SR\_UTILS\_NS::EntityRef](classSR__UTILS__NS_1_1EntityRef.md),  [SR\_UTILS\_NS::EntityRef](classSR__UTILS__NS_1_1EntityRef.md)














## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EntityRefBase**](#function-entityrefbase) () <br> |
|  SR\_NODISCARD const Entity::Ptr & | [**GetEntity**](#function-getentity) () noexcept const<br> |
|  SR\_NODISCARD EntityId | [**GetEntityId**](#function-getentityid) () noexcept const<br> |
| virtual SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetTypeName**](#function-gettypename) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResolved**](#function-isresolved) () noexcept const<br> |
|  void | [**OnEntityIdReplaced**](#function-onentityidreplaced) (const EntityReplaceMap & replaceMap) <br> |
|  void | [**Resolve**](#function-resolve) () noexcept const<br> |
|  void | [**SetEntityId**](#function-setentityid) (EntityId entityId) noexcept<br> |
|  SR\_NODISCARD | [**operator bool**](#function-operator-bool) () noexcept const<br> |


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










































































## Public Functions Documentation




### function EntityRefBase 

```C++
SR_UTILS_NS::EntityRefBase::EntityRefBase () 
```




<hr>



### function GetEntity 

```C++
SR_NODISCARD const Entity::Ptr & SR_UTILS_NS::EntityRefBase::GetEntity () noexcept const
```




<hr>



### function GetEntityId 

```C++
inline SR_NODISCARD EntityId SR_UTILS_NS::EntityRefBase::GetEntityId () noexcept const
```




<hr>



### function GetTypeName 

```C++
virtual SR_NODISCARD StringAtom SR_UTILS_NS::EntityRefBase::GetTypeName () noexcept const
```




<hr>



### function IsResolved 

```C++
SR_NODISCARD bool SR_UTILS_NS::EntityRefBase::IsResolved () noexcept const
```




<hr>



### function OnEntityIdReplaced 

```C++
void SR_UTILS_NS::EntityRefBase::OnEntityIdReplaced (
    const EntityReplaceMap & replaceMap
) 
```




<hr>



### function Resolve 

```C++
void SR_UTILS_NS::EntityRefBase::Resolve () noexcept const
```




<hr>



### function SetEntityId 

```C++
void SR_UTILS_NS::EntityRefBase::SetEntityId (
    EntityId entityId
) noexcept
```




<hr>



### function operator bool 

```C++
SR_NODISCARD SR_UTILS_NS::EntityRefBase::operator bool () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/EntityRef.h`

