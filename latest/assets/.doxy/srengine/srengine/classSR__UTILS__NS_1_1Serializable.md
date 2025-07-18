

# Class SR\_UTILS\_NS::Serializable



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Serializable**](classSR__UTILS__NS_1_1Serializable.md)








Inherits the following classes: [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)


Inherited by the following classes: [SR\_ANIMATIONS\_NS::Bone](structSR__ANIMATIONS__NS_1_1Bone.md),  [SR\_GRAPH\_NS::BaseMaterial](classSR__GRAPH__NS_1_1BaseMaterial.md),  [SR\_GRAPH\_NS::MaterialData](classSR__GRAPH__NS_1_1MaterialData.md),  [SR\_GRAPH\_NS::MaterialShaderData](structSR__GRAPH__NS_1_1MaterialShaderData.md),  [SR\_GRAPH\_NS::MaterialShaderProperty](structSR__GRAPH__NS_1_1MaterialShaderProperty.md),  [SR\_GRAPH\_UI\_NS::UILayout](structSR__GRAPH__UI__NS_1_1UILayout.md),  [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md),  [SR\_SCRIPTING\_NS::CppBehaviour](classSR__SCRIPTING__NS_1_1CppBehaviour.md),  [SR\_SCRIPTING\_NS::CppScriptModuleInfo](structSR__SCRIPTING__NS_1_1CppScriptModuleInfo.md),  [SR\_UTILS\_NS::EntityRefBase](classSR__UTILS__NS_1_1EntityRefBase.md),  [SR\_UTILS\_NS::EntityRefOld](classSR__UTILS__NS_1_1EntityRefOld.md),  [SR\_UTILS\_NS::EntityRefUtils::PathItem](structSR__UTILS__NS_1_1EntityRefUtils_1_1PathItem.md),  [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md),  [SR\_UTILS\_NS::ITestController](classSR__UTILS__NS_1_1ITestController.md),  [SR\_UTILS\_NS::Tests::ReflectionTestComponentDataBase](structSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentDataBase.md),  [SR\_UTILS\_NS::Tests::ReflectionTestComponentLogicBase](classSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentLogicBase.md),  [SR\_UTILS\_NS::Transform](classSR__UTILS__NS_1_1Transform.md),  [SR\_WORLD\_NS::SceneLogic](classSR__WORLD__NS_1_1SceneLogic.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](#typedef-origintype)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddSerializationFlags**](#function-addserializationflags) (SerializationFlags flags) noexcept<br> |
|  SR\_NODISCARD bool | [**HasSerializationFlags**](#function-hasserializationflags) (SerializationFlags flags) noexcept const<br> |
| virtual bool | [**Load**](#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) <br> |
| virtual void | [**OnPostLoad**](#function-onpostload) () <br> |
| virtual void | [**OnPostSave**](#function-onpostsave) () <br> |
| virtual void | [**OnPreLoad**](#function-onpreload) () <br> |
| virtual void | [**OnPreSave**](#function-onpresave) () <br> |
|  void | [**RemoveSerializationFlags**](#function-removeserializationflags) (SerializationFlags flags) noexcept<br> |
| virtual void | [**Save**](#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) const<br> |
| virtual void | [**VerifyAfterLoad**](#function-verifyafterload) (SerializableVerifyContext & context) noexcept const<br> |


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


















































## Public Types Documentation




### typedef OriginType 

```C++
using SR_UTILS_NS::Serializable::OriginType =  Serializable;
```




<hr>
## Public Functions Documentation




### function AddSerializationFlags 

```C++
inline void SR_UTILS_NS::Serializable::AddSerializationFlags (
    SerializationFlags flags
) noexcept
```




<hr>



### function HasSerializationFlags 

```C++
SR_NODISCARD bool SR_UTILS_NS::Serializable::HasSerializationFlags (
    SerializationFlags flags
) noexcept const
```




<hr>



### function Load 

```C++
virtual bool SR_UTILS_NS::Serializable::Load (
    IDeserializer & deserializer
) 
```




<hr>



### function OnPostLoad 

```C++
inline virtual void SR_UTILS_NS::Serializable::OnPostLoad () 
```




<hr>



### function OnPostSave 

```C++
inline virtual void SR_UTILS_NS::Serializable::OnPostSave () 
```




<hr>



### function OnPreLoad 

```C++
inline virtual void SR_UTILS_NS::Serializable::OnPreLoad () 
```




<hr>



### function OnPreSave 

```C++
inline virtual void SR_UTILS_NS::Serializable::OnPreSave () 
```




<hr>



### function RemoveSerializationFlags 

```C++
inline void SR_UTILS_NS::Serializable::RemoveSerializationFlags (
    SerializationFlags flags
) noexcept
```




<hr>



### function Save 

```C++
virtual void SR_UTILS_NS::Serializable::Save (
    ISerializer & serializer
) const
```




<hr>



### function VerifyAfterLoad 

```C++
inline virtual void SR_UTILS_NS::Serializable::VerifyAfterLoad (
    SerializableVerifyContext & context
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/Serializable.h`

