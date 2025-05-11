

# Class SR\_WORLD\_NS::CameraData



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**CameraData**](classSR__WORLD__NS_1_1CameraData.md)








Inherits the following classes: NonCopyable


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::IVector3 | [**m\_chunk**](#variable-m_chunk)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_chunkOffset**](#variable-m_chunkoffset)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_position**](#variable-m_position)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_region**](#variable-m_region)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_regionOffset**](#variable-m_regionoffset)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) | [**Save**](#function-save) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**CameraData**](classSR__WORLD__NS_1_1CameraData.md) \* | [**Load**](#function-load) ([**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) & marshal) <br> |


























## Public Attributes Documentation




### variable m\_chunk 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::CameraData::m_chunk;
```




<hr>



### variable m\_chunkOffset 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::CameraData::m_chunkOffset;
```




<hr>



### variable m\_position 

```C++
SR_MATH_NS::FVector3 SR_WORLD_NS::CameraData::m_position;
```




<hr>



### variable m\_region 

```C++
SR_MATH_NS::IVector2 SR_WORLD_NS::CameraData::m_region;
```




<hr>



### variable m\_regionOffset 

```C++
SR_MATH_NS::IVector2 SR_WORLD_NS::CameraData::m_regionOffset;
```




<hr>
## Public Functions Documentation




### function Save 

```C++
inline SR_NODISCARD SR_HTYPES_NS::Marshal SR_WORLD_NS::CameraData::Save () const
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static inline CameraData * SR_WORLD_NS::CameraData::Load (
    SR_HTYPES_NS::Marshal & marshal
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/World/CameraData.h`

