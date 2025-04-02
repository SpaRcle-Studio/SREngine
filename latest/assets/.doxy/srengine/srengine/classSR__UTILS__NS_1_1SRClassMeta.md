

# Class SR\_UTILS\_NS::SRClassMeta



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md)










Inherited by the following classes: [Codegen::SRClassMetaTemplate](structCodegen_1_1SRClassMetaTemplate.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**Allocate**](#function-allocate) () noexcept const<br> |
|  void | [**ForEachProperty**](#function-foreachproperty) (const std::function&lt; void(const [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) &property, uint64\_t index)&gt; & func, uint64\_t \* pIndex=nullptr) const<br> |
| virtual SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](#function-getbasemetas) () noexcept const<br> |
| virtual SR\_NODISCARD std::span&lt; const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetCategory**](#function-getcategory) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetFactoryName**](#function-getfactoryname) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetInspectorName**](#function-getinspectorname) () noexcept const<br> |
| virtual SR\_NODISCARD std::span&lt; const [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) &gt; | [**GetProperties**](#function-getproperties) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetVersion**](#function-getversion) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAbstract**](#function-isabstract) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEditorOnly**](#function-iseditoronly) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsHidden**](#function-ishidden) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsInherited**](#function-isinherited) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) baseClass) noexcept const<br> |
| virtual bool | [**Load**](#function-load) ([**SR\_UTILS\_NS::IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, [**SR\_UTILS\_NS::Serializable**](classSR__UTILS__NS_1_1Serializable.md) & obj) const<br> |
| virtual void | [**Save**](#function-save) ([**SR\_UTILS\_NS::ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const [**SR\_UTILS\_NS::Serializable**](classSR__UTILS__NS_1_1Serializable.md) & obj) const<br> |
| virtual  | [**~SRClassMeta**](#function-srclassmeta) () = default<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD uint64\_t | [**GetVersionImpl**](#function-getversionimpl) () noexcept const<br> |




## Public Functions Documentation




### function Allocate 

```C++
inline virtual SR_NODISCARD SRClass * SR_UTILS_NS::SRClassMeta::Allocate () noexcept const
```




<hr>



### function ForEachProperty 

```C++
void SR_UTILS_NS::SRClassMeta::ForEachProperty (
    const std::function< void(const SR_UTILS_NS::Reflection::Property &property, uint64_t index)> & func,
    uint64_t * pIndex=nullptr
) const
```




<hr>



### function GetBaseMetas 

```C++
inline virtual SR_NODISCARD std::span< const SRClassMeta * > SR_UTILS_NS::SRClassMeta::GetBaseMetas () noexcept const
```




<hr>



### function GetCategory 

```C++
virtual SR_NODISCARD std::span< const SR_UTILS_NS::StringAtom > SR_UTILS_NS::SRClassMeta::GetCategory () noexcept const
```




<hr>



### function GetFactoryName 

```C++
inline virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::SRClassMeta::GetFactoryName () noexcept const
```




<hr>



### function GetInspectorName 

```C++
inline virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::SRClassMeta::GetInspectorName () noexcept const
```




<hr>



### function GetProperties 

```C++
inline virtual SR_NODISCARD std::span< const SR_UTILS_NS::Reflection::Property > SR_UTILS_NS::SRClassMeta::GetProperties () noexcept const
```




<hr>



### function GetVersion 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::SRClassMeta::GetVersion () noexcept const
```




<hr>



### function IsAbstract 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRClassMeta::IsAbstract () noexcept const
```




<hr>



### function IsEditorOnly 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRClassMeta::IsEditorOnly () noexcept const
```




<hr>



### function IsHidden 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::SRClassMeta::IsHidden () noexcept const
```




<hr>



### function IsInherited 

```C++
SR_NODISCARD bool SR_UTILS_NS::SRClassMeta::IsInherited (
    SR_UTILS_NS::StringAtom baseClass
) noexcept const
```




<hr>



### function Load 

```C++
virtual bool SR_UTILS_NS::SRClassMeta::Load (
    SR_UTILS_NS::IDeserializer & deserializer,
    SR_UTILS_NS::Serializable & obj
) const
```




<hr>



### function Save 

```C++
virtual void SR_UTILS_NS::SRClassMeta::Save (
    SR_UTILS_NS::ISerializer & serializer,
    const SR_UTILS_NS::Serializable & obj
) const
```




<hr>



### function ~SRClassMeta 

```C++
virtual SR_UTILS_NS::SRClassMeta::~SRClassMeta () = default
```




<hr>
## Protected Functions Documentation




### function GetVersionImpl 

```C++
inline virtual SR_NODISCARD uint64_t SR_UTILS_NS::SRClassMeta::GetVersionImpl () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/SRClassMeta.h`

