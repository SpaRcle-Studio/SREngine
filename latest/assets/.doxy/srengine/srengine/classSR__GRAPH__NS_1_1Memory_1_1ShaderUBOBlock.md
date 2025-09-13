

# Class SR\_GRAPH\_NS::Memory::ShaderUBOBlock



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**ShaderUBOBlock**](classSR__GRAPH__NS_1_1Memory_1_1ShaderUBOBlock.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Append**](#function-append-12) (uint64\_t hashId, uint64\_t size, bool hidden) <br> |
|  void | [**Append**](#function-append-22) (uint64\_t hashId, uint64\_t size, uint64\_t alignedSize, bool hidden) <br> |
|  void | [**DeInit**](#function-deinit) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetBinding**](#function-getbinding) () const<br> |
|  SR\_NODISCARD bool | [**HasField**](#function-hasfield) (uint64\_t hashId) noexcept const<br> |
|  void | [**Init**](#function-init) () <br> |
|  void | [**ResetDefaultValues**](#function-resetdefaultvalues) () <br> |
|  void | [**SetDefault**](#function-setdefault) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const ShaderPropertyVariant & value) <br> |
|  void SR\_FASTCALL | [**SetField**](#function-setfield-12) (uint64\_t hashId, const void \* data) noexcept<br> |
|  void SR\_FASTCALL | [**SetField**](#function-setfield-22) (uint64\_t hashId, const ShaderPropertyVariant & property) noexcept<br> |
|   | [**ShaderUBOBlock**](#function-shaderuboblock) () <br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () noexcept const<br> |
|   | [**~ShaderUBOBlock**](#function-shaderuboblock) () override<br> |


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






## Public Functions Documentation




### function Append [1/2]

```C++
void SR_GRAPH_NS::Memory::ShaderUBOBlock::Append (
    uint64_t hashId,
    uint64_t size,
    bool hidden
) 
```




<hr>



### function Append [2/2]

```C++
void SR_GRAPH_NS::Memory::ShaderUBOBlock::Append (
    uint64_t hashId,
    uint64_t size,
    uint64_t alignedSize,
    bool hidden
) 
```




<hr>



### function DeInit 

```C++
void SR_GRAPH_NS::Memory::ShaderUBOBlock::DeInit () 
```




<hr>



### function GetBinding 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::Memory::ShaderUBOBlock::GetBinding () const
```




<hr>



### function HasField 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Memory::ShaderUBOBlock::HasField (
    uint64_t hashId
) noexcept const
```




<hr>



### function Init 

```C++
void SR_GRAPH_NS::Memory::ShaderUBOBlock::Init () 
```




<hr>



### function ResetDefaultValues 

```C++
void SR_GRAPH_NS::Memory::ShaderUBOBlock::ResetDefaultValues () 
```




<hr>



### function SetDefault 

```C++
void SR_GRAPH_NS::Memory::ShaderUBOBlock::SetDefault (
    const SR_UTILS_NS::StringAtom & name,
    const ShaderPropertyVariant & value
) 
```




<hr>



### function SetField [1/2]

```C++
void SR_FASTCALL SR_GRAPH_NS::Memory::ShaderUBOBlock::SetField (
    uint64_t hashId,
    const void * data
) noexcept
```




<hr>



### function SetField [2/2]

```C++
void SR_FASTCALL SR_GRAPH_NS::Memory::ShaderUBOBlock::SetField (
    uint64_t hashId,
    const ShaderPropertyVariant & property
) noexcept
```




<hr>



### function ShaderUBOBlock 

```C++
SR_GRAPH_NS::Memory::ShaderUBOBlock::ShaderUBOBlock () 
```




<hr>



### function Valid 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Memory::ShaderUBOBlock::Valid () noexcept const
```




<hr>



### function ~ShaderUBOBlock 

```C++
SR_GRAPH_NS::Memory::ShaderUBOBlock::~ShaderUBOBlock () override
```




<hr>## Friends Documentation





### friend ShaderCache 

```C++
class SR_GRAPH_NS::Memory::ShaderUBOBlock::ShaderCache (
    SR_GRAPH_NS::ShaderCache
) 
```




<hr>



### friend Shader 

```C++
class SR_GRAPH_NS::Memory::ShaderUBOBlock::Shader (
    SR_GRAPH_NS::Types::Shader
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Memory/ShaderUBOBlock.h`

