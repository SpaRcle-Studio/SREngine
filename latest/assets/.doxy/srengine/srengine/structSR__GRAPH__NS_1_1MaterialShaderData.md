

# Struct SR\_GRAPH\_NS::MaterialShaderData



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MaterialShaderData**](structSR__GRAPH__NS_1_1MaterialShaderData.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**MaterialData**](classSR__GRAPH__NS_1_1MaterialData.md) \* | [**pOwnedMaterialData**](#variable-pownedmaterialdata)   = `nullptr`<br> |
|  SR\_GTYPES\_NS::Shader::Ptr | [**pShader**](#variable-pshader)   = `nullptr`<br> |
|  std::vector&lt; [**MaterialShaderProperty**](structSR__GRAPH__NS_1_1MaterialShaderProperty.md) &gt; | [**samplers**](#variable-samplers)  <br> |
|  std::vector&lt; [**MaterialShaderProperty**](structSR__GRAPH__NS_1_1MaterialShaderProperty.md) &gt; | [**uniforms**](#variable-uniforms)  <br> |
|  MaterialStageUseType | [**useType**](#variable-usetype)   = `MaterialStageUseType::Full`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ForEachProperty**](#function-foreachproperty) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**MaterialShaderProperty**](structSR__GRAPH__NS_1_1MaterialShaderProperty.md) &)&gt; & func) <br> |
| virtual void | [**OnPostLoad**](#function-onpostload) () override<br> |
| virtual void | [**OnPreLoad**](#function-onpreload) () override<br> |
|  MaterialPropertyChangeResult SR\_FASTCALL | [**SetData**](#function-setdata) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const ShaderPropertyVariant & v, ShaderVarType type) noexcept<br> |
|  void | [**UpdateProperties**](#function-updateproperties) () <br> |


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
|  void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
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




### variable pOwnedMaterialData 

```C++
MaterialData* SR_GRAPH_NS::MaterialShaderData::pOwnedMaterialData;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader::Ptr SR_GRAPH_NS::MaterialShaderData::pShader;
```




<hr>



### variable samplers 

```C++
std::vector<MaterialShaderProperty> SR_GRAPH_NS::MaterialShaderData::samplers;
```




<hr>



### variable uniforms 

```C++
std::vector<MaterialShaderProperty> SR_GRAPH_NS::MaterialShaderData::uniforms;
```




<hr>



### variable useType 

```C++
MaterialStageUseType SR_GRAPH_NS::MaterialShaderData::useType;
```




<hr>
## Public Functions Documentation




### function ForEachProperty 

```C++
void SR_GRAPH_NS::MaterialShaderData::ForEachProperty (
    const SR_HTYPES_NS::Function < void( MaterialShaderProperty &)> & func
) 
```




<hr>



### function OnPostLoad 

```C++
virtual void SR_GRAPH_NS::MaterialShaderData::OnPostLoad () override
```



Implements [*SR\_UTILS\_NS::Serializable::OnPostLoad*](classSR__UTILS__NS_1_1Serializable.md#function-onpostload)


<hr>



### function OnPreLoad 

```C++
virtual void SR_GRAPH_NS::MaterialShaderData::OnPreLoad () override
```



Implements [*SR\_UTILS\_NS::Serializable::OnPreLoad*](classSR__UTILS__NS_1_1Serializable.md#function-onpreload)


<hr>



### function SetData 

```C++
MaterialPropertyChangeResult SR_FASTCALL SR_GRAPH_NS::MaterialShaderData::SetData (
    SR_UTILS_NS::StringAtom id,
    const ShaderPropertyVariant & v,
    ShaderVarType type
) noexcept
```




<hr>



### function UpdateProperties 

```C++
void SR_GRAPH_NS::MaterialShaderData::UpdateProperties () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Material/MaterialData.h`

