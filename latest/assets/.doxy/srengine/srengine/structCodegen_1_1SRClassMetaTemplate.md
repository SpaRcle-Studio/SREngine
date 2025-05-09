

# Struct Codegen::SRClassMetaTemplate

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SRClassMetaTemplate**](structCodegen_1_1SRClassMetaTemplate.md)








Inherits the following classes: [SR\_UTILS\_NS::SRClassMeta](classSR__UTILS__NS_1_1SRClassMeta.md)
























































## Public Functions inherited from SR_UTILS_NS::SRClassMeta

See [SR\_UTILS\_NS::SRClassMeta](classSR__UTILS__NS_1_1SRClassMeta.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**Allocate**](classSR__UTILS__NS_1_1SRClassMeta.md#function-allocate) () noexcept const<br> |
|  void | [**ForEachProperty**](classSR__UTILS__NS_1_1SRClassMeta.md#function-foreachproperty) (const std::function&lt; void(const [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) &property, uint64\_t index)&gt; & func, uint64\_t \* pIndex=nullptr) const<br> |
| virtual SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getbasemetas) () noexcept const<br> |
| virtual SR\_NODISCARD std::span&lt; const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetCategory**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getcategory) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetFactoryName**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getfactoryname) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetInspectorName**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getinspectorname) () noexcept const<br> |
| virtual SR\_NODISCARD std::span&lt; const [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) &gt; | [**GetProperties**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getproperties) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetVersion**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getversion) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAbstract**](classSR__UTILS__NS_1_1SRClassMeta.md#function-isabstract) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEditorOnly**](classSR__UTILS__NS_1_1SRClassMeta.md#function-iseditoronly) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsHidden**](classSR__UTILS__NS_1_1SRClassMeta.md#function-ishidden) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsInherited**](classSR__UTILS__NS_1_1SRClassMeta.md#function-isinherited) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) baseClass) noexcept const<br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1SRClassMeta.md#function-load) ([**SR\_UTILS\_NS::IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, [**SR\_UTILS\_NS::Serializable**](classSR__UTILS__NS_1_1Serializable.md) & obj) const<br> |
| virtual void | [**Save**](classSR__UTILS__NS_1_1SRClassMeta.md#function-save) ([**SR\_UTILS\_NS::ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const [**SR\_UTILS\_NS::Serializable**](classSR__UTILS__NS_1_1Serializable.md) & obj) const<br> |
| virtual  | [**~SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md#function-srclassmeta) () <br> |
















































## Protected Functions inherited from SR_UTILS_NS::SRClassMeta

See [SR\_UTILS\_NS::SRClassMeta](classSR__UTILS__NS_1_1SRClassMeta.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD uint64\_t | [**GetVersionImpl**](classSR__UTILS__NS_1_1SRClassMeta.md#function-getversionimpl) () noexcept const<br> |







------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/SRClassMeta.h`

