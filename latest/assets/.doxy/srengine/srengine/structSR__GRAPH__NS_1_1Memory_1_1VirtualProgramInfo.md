

# Struct SR\_GRAPH\_NS::Memory::VirtualProgramInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**VirtualProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**ShaderProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo_1_1ShaderProgramInfo.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Identifier**](#typedef-identifier)  <br> |
| typedef int32\_t | [**ShaderProgram**](#typedef-shaderprogram)  <br> |








## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) | [**m\_createInfo**](#variable-m_createinfo)  <br> |
|  std::vector&lt; std::pair&lt; Identifier, [**ShaderProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo_1_1ShaderProgramInfo.md) &gt; &gt; | [**m\_data**](#variable-m_data)  <br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD int32\_t | [**GetProgramId**](#function-getprogramid) (Identifier identifier) noexcept const<br> |
|  SR\_NODISCARD [**ShaderProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo_1_1ShaderProgramInfo.md) \* | [**GetProgramInfo**](#function-getprograminfo-12) (Identifier identifier) <br> |
|  SR\_NODISCARD const [**ShaderProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo_1_1ShaderProgramInfo.md) \* | [**GetProgramInfo**](#function-getprograminfo-22) (Identifier identifier) noexcept const<br> |
|  SR\_NODISCARD bool | [**HasProgram**](#function-hasprogram) (Identifier identifier) const<br> |
|  [**ShaderProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo_1_1ShaderProgramInfo.md) \* | [**SetProgramInfo**](#function-setprograminfo) (Identifier identifier, const [**ShaderProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo_1_1ShaderProgramInfo.md) & info) <br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () const<br> |
|   | [**VirtualProgramInfo**](#function-virtualprograminfo-12) () = default<br> |
|   | [**VirtualProgramInfo**](#function-virtualprograminfo-22) ([**VirtualProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo.md) && ref) noexcept<br> |
|  [**VirtualProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo.md) & | [**operator=**](#function-operator) ([**VirtualProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo.md) && ref) noexcept<br> |
|   | [**~VirtualProgramInfo**](#function-virtualprograminfo) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef Identifier 

```C++
using SR_GRAPH_NS::Memory::VirtualProgramInfo::Identifier =  uint64_t;
```




<hr>



### typedef ShaderProgram 

```C++
using SR_GRAPH_NS::Memory::VirtualProgramInfo::ShaderProgram =  int32_t;
```




<hr>
## Public Attributes Documentation




### variable m\_createInfo 

```C++
SRShaderCreateInfo SR_GRAPH_NS::Memory::VirtualProgramInfo::m_createInfo;
```




<hr>



### variable m\_data 

```C++
std::vector<std::pair<Identifier, ShaderProgramInfo> > SR_GRAPH_NS::Memory::VirtualProgramInfo::m_data;
```




<hr>
## Public Functions Documentation




### function GetProgramId 

```C++
inline SR_NODISCARD int32_t SR_GRAPH_NS::Memory::VirtualProgramInfo::GetProgramId (
    Identifier identifier
) noexcept const
```




<hr>



### function GetProgramInfo [1/2]

```C++
inline SR_NODISCARD ShaderProgramInfo * SR_GRAPH_NS::Memory::VirtualProgramInfo::GetProgramInfo (
    Identifier identifier
) 
```




<hr>



### function GetProgramInfo [2/2]

```C++
inline SR_NODISCARD const ShaderProgramInfo * SR_GRAPH_NS::Memory::VirtualProgramInfo::GetProgramInfo (
    Identifier identifier
) noexcept const
```




<hr>



### function HasProgram 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Memory::VirtualProgramInfo::HasProgram (
    Identifier identifier
) const
```




<hr>



### function SetProgramInfo 

```C++
inline ShaderProgramInfo * SR_GRAPH_NS::Memory::VirtualProgramInfo::SetProgramInfo (
    Identifier identifier,
    const ShaderProgramInfo & info
) 
```




<hr>



### function Valid 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Memory::VirtualProgramInfo::Valid () const
```




<hr>



### function VirtualProgramInfo [1/2]

```C++
SR_GRAPH_NS::Memory::VirtualProgramInfo::VirtualProgramInfo () = default
```




<hr>



### function VirtualProgramInfo [2/2]

```C++
inline SR_GRAPH_NS::Memory::VirtualProgramInfo::VirtualProgramInfo (
    VirtualProgramInfo && ref
) noexcept
```




<hr>



### function operator= 

```C++
inline VirtualProgramInfo & SR_GRAPH_NS::Memory::VirtualProgramInfo::operator= (
    VirtualProgramInfo && ref
) noexcept
```




<hr>



### function ~VirtualProgramInfo 

```C++
SR_GRAPH_NS::Memory::VirtualProgramInfo::~VirtualProgramInfo () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/ShaderProgramManager.h`

