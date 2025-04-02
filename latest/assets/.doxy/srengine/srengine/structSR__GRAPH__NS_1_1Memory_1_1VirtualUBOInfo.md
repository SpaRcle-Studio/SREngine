

# Struct SR\_GRAPH\_NS::Memory::VirtualUBOInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**VirtualUBOInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Data**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo_1_1Data.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef int32\_t | [**UBO**](#typedef-ubo)  <br> |








## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**Data**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo_1_1Data.md) &gt; | [**data**](#variable-data)  <br> |
|  bool | [**shared**](#variable-shared)   = `false`<br>_UBO используется в нескольких шейдерах. Если выключен, то UBO будет создан для каждого шейдера_  |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Reset**](#function-reset) () noexcept<br> |
|  SR\_NODISCARD bool | [**Valid**](#function-valid) () noexcept const<br> |
|   | [**VirtualUBOInfo**](#function-virtualuboinfo-12) () = default<br> |
|   | [**VirtualUBOInfo**](#function-virtualuboinfo-22) ([**VirtualUBOInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo.md) && ref) noexcept<br> |
|  [**VirtualUBOInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo.md) & | [**operator=**](#function-operator) ([**VirtualUBOInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo.md) && ref) noexcept<br> |
|   | [**~VirtualUBOInfo**](#function-virtualuboinfo) () override<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef UBO 

```C++
using SR_GRAPH_NS::Memory::VirtualUBOInfo::UBO =  int32_t;
```




<hr>
## Public Attributes Documentation




### variable data 

```C++
std::vector<Data> SR_GRAPH_NS::Memory::VirtualUBOInfo::data;
```




<hr>



### variable shared 

_UBO используется в нескольких шейдерах. Если выключен, то UBO будет создан для каждого шейдера_ 
```C++
bool SR_GRAPH_NS::Memory::VirtualUBOInfo::shared;
```




<hr>
## Public Functions Documentation




### function Reset 

```C++
inline void SR_GRAPH_NS::Memory::VirtualUBOInfo::Reset () noexcept
```




<hr>



### function Valid 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Memory::VirtualUBOInfo::Valid () noexcept const
```




<hr>



### function VirtualUBOInfo [1/2]

```C++
SR_GRAPH_NS::Memory::VirtualUBOInfo::VirtualUBOInfo () = default
```




<hr>



### function VirtualUBOInfo [2/2]

```C++
inline SR_GRAPH_NS::Memory::VirtualUBOInfo::VirtualUBOInfo (
    VirtualUBOInfo && ref
) noexcept
```




<hr>



### function operator= 

```C++
inline VirtualUBOInfo & SR_GRAPH_NS::Memory::VirtualUBOInfo::operator= (
    VirtualUBOInfo && ref
) noexcept
```




<hr>



### function ~VirtualUBOInfo 

```C++
SR_GRAPH_NS::Memory::VirtualUBOInfo::~VirtualUBOInfo () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/UBOManager.h`

