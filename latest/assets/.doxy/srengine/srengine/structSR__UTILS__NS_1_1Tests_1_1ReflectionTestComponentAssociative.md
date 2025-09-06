

# Struct SR\_UTILS\_NS::Tests::ReflectionTestComponentAssociative



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Tests**](namespaceSR__UTILS__NS_1_1Tests.md) **>** [**ReflectionTestComponentAssociative**](structSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponentAssociative.md)








Inherits the following classes: [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
















## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |










## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; int, std::string &gt; | [**associativeMap2**](#variable-associativemap2)  <br> |
|  std::map&lt; SR\_UTILS\_NS::PlatformType, std::string &gt; | [**associativeMap3**](#variable-associativemap3)  <br> |
|  std::map&lt; SR\_UTILS\_NS::PlatformType, int &gt; | [**associativeMap33**](#variable-associativemap33)  <br> |
|  std::map&lt; SR\_UTILS\_NS::PlatformType, [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) &gt; | [**associativeMap4**](#variable-associativemap4)  <br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), int &gt; | [**associativeMapAtom**](#variable-associativemapatom)  <br> |
|  std::map&lt; std::string, int &gt; | [**associativeMapString**](#variable-associativemapstring)  <br> |


















































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




### variable associativeMap2 

```C++
std::map<int, std::string> SR_UTILS_NS::Tests::ReflectionTestComponentAssociative::associativeMap2;
```




<hr>



### variable associativeMap3 

```C++
std::map<SR_UTILS_NS::PlatformType, std::string> SR_UTILS_NS::Tests::ReflectionTestComponentAssociative::associativeMap3;
```




<hr>



### variable associativeMap33 

```C++
std::map<SR_UTILS_NS::PlatformType, int> SR_UTILS_NS::Tests::ReflectionTestComponentAssociative::associativeMap33;
```




<hr>



### variable associativeMap4 

```C++
std::map<SR_UTILS_NS::PlatformType, SR_UTILS_NS::Path> SR_UTILS_NS::Tests::ReflectionTestComponentAssociative::associativeMap4;
```




<hr>



### variable associativeMapAtom 

```C++
std::map<SR_UTILS_NS::StringAtom, int> SR_UTILS_NS::Tests::ReflectionTestComponentAssociative::associativeMapAtom;
```




<hr>



### variable associativeMapString 

```C++
std::map<std::string, int> SR_UTILS_NS::Tests::ReflectionTestComponentAssociative::associativeMapString;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Tests/ReflectionTestComponent.h`

