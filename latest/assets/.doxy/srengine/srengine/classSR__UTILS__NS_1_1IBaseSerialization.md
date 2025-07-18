

# Class SR\_UTILS\_NS::IBaseSerialization



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IBaseSerialization**](classSR__UTILS__NS_1_1IBaseSerialization.md)










Inherited by the following classes: [SR\_UTILS\_NS::SRAISerialization](classSR__UTILS__NS_1_1SRAISerialization.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetCurrentNode**](#function-getcurrentnode-12) () noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetCurrentNode**](#function-getcurrentnode-22) () noexcept const<br> |
|  SR\_NODISCARD [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetWalkNode**](#function-getwalknode-12) () noexcept<br> |
|  SR\_NODISCARD const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & | [**GetWalkNode**](#function-getwalknode-22) () noexcept const<br> |
|   | [**IBaseSerialization**](#function-ibaseserialization) () <br> |
| virtual SR\_NODISCARD std::string | [**ToStringBase**](#function-tostringbase) () noexcept const = 0<br> |
|  void | [**WriteNode**](#function-writenode) (const [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) & node) noexcept<br> |
|   | [**~IBaseSerialization**](#function-ibaseserialization) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) | [**m\_root**](#variable-m_root)  <br> |
|  [**SR\_HTYPES\_NS::FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md)&lt; [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) \* &gt; | [**m\_stack**](#variable-m_stack)  <br> |
|  [**SR\_HTYPES\_NS::FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md)&lt; [**SerializationNode**](structSR__UTILS__NS_1_1SerializationNode.md) \* &gt; | [**m\_walker**](#variable-m_walker)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsAllowEmptyElementsInArrayImpl**](#function-isallowemptyelementsinarrayimpl) () noexcept const<br> |
|  SR\_NODISCARD bool | [**SaveToFileImpl**](#function-savetofileimpl) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) const<br> |




## Public Functions Documentation




### function GetCurrentNode [1/2]

```C++
inline SR_NODISCARD SerializationNode & SR_UTILS_NS::IBaseSerialization::GetCurrentNode () noexcept
```




<hr>



### function GetCurrentNode [2/2]

```C++
inline SR_NODISCARD const SerializationNode & SR_UTILS_NS::IBaseSerialization::GetCurrentNode () noexcept const
```




<hr>



### function GetWalkNode [1/2]

```C++
inline SR_NODISCARD SerializationNode & SR_UTILS_NS::IBaseSerialization::GetWalkNode () noexcept
```




<hr>



### function GetWalkNode [2/2]

```C++
inline SR_NODISCARD const SerializationNode & SR_UTILS_NS::IBaseSerialization::GetWalkNode () noexcept const
```




<hr>



### function IBaseSerialization 

```C++
SR_UTILS_NS::IBaseSerialization::IBaseSerialization () 
```




<hr>



### function ToStringBase 

```C++
virtual SR_NODISCARD std::string SR_UTILS_NS::IBaseSerialization::ToStringBase () noexcept const = 0
```




<hr>



### function WriteNode 

```C++
void SR_UTILS_NS::IBaseSerialization::WriteNode (
    const SerializationNode & node
) noexcept
```




<hr>



### function ~IBaseSerialization 

```C++
SR_UTILS_NS::IBaseSerialization::~IBaseSerialization () 
```




<hr>
## Protected Attributes Documentation




### variable m\_root 

```C++
SerializationNode SR_UTILS_NS::IBaseSerialization::m_root;
```




<hr>



### variable m\_stack 

```C++
SR_HTYPES_NS::FastMemoryArray<SerializationNode*> SR_UTILS_NS::IBaseSerialization::m_stack;
```




<hr>



### variable m\_walker 

```C++
SR_HTYPES_NS::FastMemoryArray<SerializationNode*> SR_UTILS_NS::IBaseSerialization::m_walker;
```




<hr>
## Protected Functions Documentation




### function IsAllowEmptyElementsInArrayImpl 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IBaseSerialization::IsAllowEmptyElementsInArrayImpl () noexcept const
```




<hr>



### function SaveToFileImpl 

```C++
SR_NODISCARD bool SR_UTILS_NS::IBaseSerialization::SaveToFileImpl (
    const SR_UTILS_NS::Path & path
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/BaseSerialization.h`

