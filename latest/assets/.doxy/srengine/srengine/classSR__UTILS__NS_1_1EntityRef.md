

# Class SR\_UTILS\_NS::EntityRef



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EntityRef**](classSR__UTILS__NS_1_1EntityRef.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**EntityRef**](classSR__UTILS__NS_1_1EntityRef.md) | [**Copy**](#function-copy) (const [**EntityRefUtils::OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) const<br> |
|   | [**EntityRef**](#function-entityref-12) () = default<br> |
|   | [**EntityRef**](#function-entityref-22) ([**EntityRefUtils::OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) owner) <br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetComponent**](#function-getcomponent-12) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Component**](classSR__UTILS__NS_1_1Component.md) &gt; | [**GetComponent**](#function-getcomponent-22) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**GetGameObject**](#function-getgameobject) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**GetSceneObject**](#function-getsceneobject) () const<br> |
|  SR\_NODISCARD const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; Entity &gt; & | [**GetTarget**](#function-gettarget) () const<br> |
|  SR\_NODISCARD bool | [**IsRelative**](#function-isrelative) () const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
| virtual void | [**OnPreSave**](#function-onpresave) () override<br> |
|  void | [**SetOwner**](#function-setowner) (const [**EntityRefUtils::OwnerRef**](structSR__UTILS__NS_1_1EntityRefUtils_1_1OwnerRef.md) & owner) <br> |
|  [**EntityRef**](classSR__UTILS__NS_1_1EntityRef.md) & | [**SetPathTo**](#function-setpathto) (const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; Entity &gt; & pEntity) <br> |
|  void | [**SetRelative**](#function-setrelative) (bool relative) <br> |
|  void | [**UpdateTarget**](#function-updatetarget) () const<br> |


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




### function Copy 

```C++
SR_NODISCARD EntityRef SR_UTILS_NS::EntityRef::Copy (
    const EntityRefUtils::OwnerRef & owner
) const
```




<hr>



### function EntityRef [1/2]

```C++
SR_UTILS_NS::EntityRef::EntityRef () = default
```




<hr>



### function EntityRef [2/2]

```C++
explicit SR_UTILS_NS::EntityRef::EntityRef (
    EntityRefUtils::OwnerRef owner
) 
```




<hr>



### function GetComponent [1/2]

```C++
template<typename T>
inline SR_NODISCARD SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::EntityRef::GetComponent () const
```




<hr>



### function GetComponent [2/2]

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < Component > SR_UTILS_NS::EntityRef::GetComponent () const
```




<hr>



### function GetGameObject 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < GameObject > SR_UTILS_NS::EntityRef::GetGameObject () const
```




<hr>



### function GetSceneObject 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < SceneObject > SR_UTILS_NS::EntityRef::GetSceneObject () const
```




<hr>



### function GetTarget 

```C++
inline SR_NODISCARD const SR_HTYPES_NS::SharedPtr < Entity > & SR_UTILS_NS::EntityRef::GetTarget () const
```




<hr>



### function IsRelative 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::EntityRef::IsRelative () const
```




<hr>



### function IsValid 

```C++
SR_NODISCARD bool SR_UTILS_NS::EntityRef::IsValid () const
```




<hr>



### function OnPreSave 

```C++
virtual void SR_UTILS_NS::EntityRef::OnPreSave () override
```



Implements [*SR\_UTILS\_NS::Serializable::OnPreSave*](classSR__UTILS__NS_1_1Serializable.md#function-onpresave)


<hr>



### function SetOwner 

```C++
void SR_UTILS_NS::EntityRef::SetOwner (
    const EntityRefUtils::OwnerRef & owner
) 
```




<hr>



### function SetPathTo 

```C++
EntityRef & SR_UTILS_NS::EntityRef::SetPathTo (
    const SR_HTYPES_NS::SharedPtr < Entity > & pEntity
) 
```




<hr>



### function SetRelative 

```C++
void SR_UTILS_NS::EntityRef::SetRelative (
    bool relative
) 
```




<hr>



### function UpdateTarget 

```C++
void SR_UTILS_NS::EntityRef::UpdateTarget () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/ECS/EntityRef.h`

