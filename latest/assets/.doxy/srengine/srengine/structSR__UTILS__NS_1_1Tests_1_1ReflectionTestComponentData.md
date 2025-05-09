

# Struct SR\_UTILS\_NS::Tests::ReflectionTestComponentData



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Tests**](namespaceSR__UTILS__NS_1_1Tests.md) **>** [**ReflectionTestComponentData**](structSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentData.md)








Inherits the following classes: [SR\_UTILS\_NS::Tests::ReflectionTestComponentDataBase](structSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentDataBase.md)


















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |












## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; float &gt; | [**m\_test**](#variable-m_test)  <br> |
|  int32\_t | [**m\_width**](#variable-m_width)   = `100`<br> |
|  bool | [**testField**](#variable-testfield)   = `false`<br> |
|  SR\_MATH\_NS::FVector3 | [**vector**](#variable-vector)  <br> |


## Public Attributes inherited from SR_UTILS_NS::Tests::ReflectionTestComponentDataBase

See [SR\_UTILS\_NS::Tests::ReflectionTestComponentDataBase](structSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentDataBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**baseField**](structSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentDataBase.md#variable-basefield)   = `false`<br> |


































































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




### variable m\_test 

```C++
std::vector<float> SR_UTILS_NS::Tests::ReflectionTestComponentData::m_test;
```




<hr>



### variable m\_width 

```C++
int32_t SR_UTILS_NS::Tests::ReflectionTestComponentData::m_width;
```




<hr>



### variable testField 

```C++
bool SR_UTILS_NS::Tests::ReflectionTestComponentData::testField;
```




<hr>



### variable vector 

```C++
SR_MATH_NS::FVector3 SR_UTILS_NS::Tests::ReflectionTestComponentData::vector;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Tests/ReflectionTestComponent.h`

