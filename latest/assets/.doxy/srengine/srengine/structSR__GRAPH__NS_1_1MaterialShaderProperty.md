

# Struct SR\_GRAPH\_NS::MaterialShaderProperty



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MaterialShaderProperty**](structSR__GRAPH__NS_1_1MaterialShaderProperty.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  ShaderPropertyVariant | [**data**](#variable-data)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**displayName**](#variable-displayname)  <br> |
|  uint32\_t | [**editorOrder**](#variable-editororder)   = `0`<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**id**](#variable-id)  <br> |
|  bool | [**pushConstant**](#variable-pushconstant)   = `false`<br> |
|  ShaderVarType | [**type**](#variable-type)   = `ShaderVarType::Unknown`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**Load**](#function-load) ([**SR\_UTILS\_NS::IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) override<br> |
| virtual void | [**Save**](#function-save) ([**SR\_UTILS\_NS::ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) override const<br> |


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










































































## Public Attributes Documentation




### variable data 

```C++
ShaderPropertyVariant SR_GRAPH_NS::MaterialShaderProperty::data;
```




<hr>



### variable displayName 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::MaterialShaderProperty::displayName;
```




<hr>



### variable editorOrder 

```C++
uint32_t SR_GRAPH_NS::MaterialShaderProperty::editorOrder;
```




<hr>



### variable id 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_NS::MaterialShaderProperty::id;
```




<hr>



### variable pushConstant 

```C++
bool SR_GRAPH_NS::MaterialShaderProperty::pushConstant;
```




<hr>



### variable type 

```C++
ShaderVarType SR_GRAPH_NS::MaterialShaderProperty::type;
```




<hr>
## Public Functions Documentation




### function Load 

```C++
virtual bool SR_GRAPH_NS::MaterialShaderProperty::Load (
    SR_UTILS_NS::IDeserializer & deserializer
) override
```



Implements [*SR\_UTILS\_NS::Serializable::Load*](classSR__UTILS__NS_1_1Serializable.md#function-load)


<hr>



### function Save 

```C++
virtual void SR_GRAPH_NS::MaterialShaderProperty::Save (
    SR_UTILS_NS::ISerializer & serializer
) override const
```



Implements [*SR\_UTILS\_NS::Serializable::Save*](classSR__UTILS__NS_1_1Serializable.md#function-save)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Material/MaterialData.h`

