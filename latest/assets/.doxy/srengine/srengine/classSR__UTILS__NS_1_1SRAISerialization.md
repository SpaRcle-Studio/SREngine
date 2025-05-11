

# Class SR\_UTILS\_NS::SRAISerialization



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SRAISerialization**](classSR__UTILS__NS_1_1SRAISerialization.md)



_SpaRcle Assert serialization / deserialization._ 

* `#include <SRASerialization.h>`



Inherits the following classes: [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)


Inherited by the following classes: [SR\_UTILS\_NS::SRADeserializer](classSR__UTILS__NS_1_1SRADeserializer.md),  [SR\_UTILS\_NS::SRASerializer](classSR__UTILS__NS_1_1SRASerializer.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**IsNeedUseTabs**](#function-isneedusetabs) () noexcept const<br> |
|  void | [**SetUseTabs**](#function-setusetabs) (const bool value) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToStringBase**](#function-tostringbase) () noexcept override const<br> |


## Public Functions inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetCurrentNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getcurrentnode-12) () noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetCurrentNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getcurrentnode-22) () noexcept const<br> |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetWalkNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getwalknode-12) () noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetWalkNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getwalknode-22) () noexcept const<br> |
| virtual SR\_NODISCARD std::string | [**ToStringBase**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-tostringbase) () noexcept const = 0<br> |
















## Protected Attributes inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) | [**m\_root**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_root)  <br> |
|  std::vector&lt; uint64\_t &gt; | [**m\_stack**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_stack)  <br> |
|  std::vector&lt; uint64\_t &gt; | [**m\_walker**](classSR__UTILS__NS_1_1IBaseSerialization.md#variable-m_walker)  <br> |
































## Protected Functions inherited from SR_UTILS_NS::IBaseSerialization

See [SR\_UTILS\_NS::IBaseSerialization](classSR__UTILS__NS_1_1IBaseSerialization.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getnode-12) (const std::vector&lt; uint64\_t &gt; & stack) noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetNode**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-getnode-22) (const std::vector&lt; uint64\_t &gt; & stack) noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAllowEmptyElementsInArrayImpl**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-isallowemptyelementsinarrayimpl) () noexcept const<br> |
|  SR\_NODISCARD bool | [**SaveToFileImpl**](classSR__UTILS__NS_1_1IBaseSerialization.md#function-savetofileimpl) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |






## Public Functions Documentation




### function IsNeedUseTabs 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::SRAISerialization::IsNeedUseTabs () noexcept const
```




<hr>



### function SetUseTabs 

```C++
inline void SR_UTILS_NS::SRAISerialization::SetUseTabs (
    const bool value
) noexcept
```




<hr>



### function ToStringBase 

```C++
virtual SR_NODISCARD std::string SR_UTILS_NS::SRAISerialization::ToStringBase () noexcept override const
```



Implements [*SR\_UTILS\_NS::IBaseSerialization::ToStringBase*](classSR__UTILS__NS_1_1IBaseSerialization.md#function-tostringbase)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/SRASerialization.h`

