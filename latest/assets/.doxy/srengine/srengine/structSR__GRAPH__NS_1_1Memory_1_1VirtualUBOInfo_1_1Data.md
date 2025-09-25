

# Struct SR\_GRAPH\_NS::Memory::VirtualUBOInfo::Data



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**VirtualUBOInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo.md) **>** [**Data**](structSR__GRAPH__NS_1_1Memory_1_1VirtualUBOInfo_1_1Data.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  void \* | [**pShaderHandle**](#variable-pshaderhandle)   = `nullptr`<br> |
|  uint16\_t | [**uboSize**](#variable-ubosize)   = `0`<br> |
|  std::array&lt; UBO, SR\_MAX\_FRAMES\_IN\_FLIGHT &gt; | [**ubos**](#variable-ubos)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Validate**](#function-validate) () const<br> |




























## Public Attributes Documentation




### variable pShaderHandle 

```C++
void* SR_GRAPH_NS::Memory::VirtualUBOInfo::Data::pShaderHandle;
```




<hr>



### variable uboSize 

```C++
uint16_t SR_GRAPH_NS::Memory::VirtualUBOInfo::Data::uboSize;
```




<hr>



### variable ubos 

```C++
std::array<UBO, SR_MAX_FRAMES_IN_FLIGHT> SR_GRAPH_NS::Memory::VirtualUBOInfo::Data::ubos;
```




<hr>
## Public Functions Documentation




### function Validate 

```C++
inline void SR_GRAPH_NS::Memory::VirtualUBOInfo::Data::Validate () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Memory/UBOManager.h`

