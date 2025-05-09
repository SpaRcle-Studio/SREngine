

# Class SR\_UTILS\_NS::SRClass



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRClass**](classSR__UTILS__NS_1_1SRClass.md)










Inherited by the following classes: [SR\_CORE\_GUI\_NS::PropertyDrawerBase](classSR__CORE__GUI__NS_1_1PropertyDrawerBase.md),  [SR\_GRAPH\_NS::IRenderer](classSR__GRAPH__NS_1_1IRenderer.md),  [SR\_UTILS\_NS::IMigrator](classSR__UTILS__NS_1_1IMigrator.md),  [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](#function-srclass) () = default<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](#function-registerpropertiescodegen) () <br> |


























## Public Functions Documentation




### function GetMeta 

```C++
virtual SR_NODISCARD const SR_UTILS_NS::SRClassMeta * SR_UTILS_NS::SRClass::GetMeta () noexcept const = 0
```




<hr>



### function ~SRClass 

```C++
virtual SR_UTILS_NS::SRClass::~SRClass () = default
```




<hr>
## Public Static Functions Documentation




### function AllocateStatic 

```C++
static SR_UTILS_NS::SRClass * SR_UTILS_NS::SRClass::AllocateStatic () noexcept
```




<hr>



### function GetBaseMetas 

```C++
static inline SR_NODISCARD std::span< const SRClassMeta * > SR_UTILS_NS::SRClass::GetBaseMetas () noexcept
```




<hr>



### function GetClassStaticName 

```C++
static SR_UTILS_NS::StringAtom SR_UTILS_NS::SRClass::GetClassStaticName () noexcept
```




<hr>



### function GetMetaStatic 

```C++
static const SR_UTILS_NS::SRClassMeta * SR_UTILS_NS::SRClass::GetMetaStatic () noexcept
```




<hr>



### function RegisterPropertiesCodegen 

```C++
static bool SR_UTILS_NS::SRClass::RegisterPropertiesCodegen () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/SRClass.h`

