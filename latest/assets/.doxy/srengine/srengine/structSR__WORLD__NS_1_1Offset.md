

# Struct SR\_WORLD\_NS::Offset



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**Offset**](structSR__WORLD__NS_1_1Offset.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  Math::IVector3 | [**m\_chunk**](#variable-m_chunk)  <br> |
|  Math::IVector3 | [**m\_region**](#variable-m_region)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**Empty**](#function-empty) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector3 | [**GetChunk**](#function-getchunk) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector3 | [**GetRegion**](#function-getregion) () noexcept const<br> |
|   | [**Offset**](#function-offset-12) (const SR\_MATH\_NS::IVector3 & region, const SR\_MATH\_NS::IVector3 & chunk) <br> |
|   | [**Offset**](#function-offset-22) () <br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator) (const [**Offset**](structSR__WORLD__NS_1_1Offset.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Offset**](structSR__WORLD__NS_1_1Offset.md) | [**operator-**](#function-operator_1) (const [**Offset**](structSR__WORLD__NS_1_1Offset.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_2) (const [**Offset**](structSR__WORLD__NS_1_1Offset.md) & p\_v) const<br> |




























## Public Attributes Documentation




### variable m\_chunk 

```C++
Math::IVector3 SR_WORLD_NS::Offset::m_chunk;
```




<hr>



### variable m\_region 

```C++
Math::IVector3 SR_WORLD_NS::Offset::m_region;
```




<hr>
## Public Functions Documentation




### function Empty 

```C++
inline SR_NODISCARD bool SR_WORLD_NS::Offset::Empty () const
```




<hr>



### function GetChunk 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector3 SR_WORLD_NS::Offset::GetChunk () noexcept const
```




<hr>



### function GetRegion 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector3 SR_WORLD_NS::Offset::GetRegion () noexcept const
```




<hr>



### function Offset [1/2]

```C++
inline SR_WORLD_NS::Offset::Offset (
    const SR_MATH_NS::IVector3 & region,
    const SR_MATH_NS::IVector3 & chunk
) 
```




<hr>



### function Offset [2/2]

```C++
inline SR_WORLD_NS::Offset::Offset () 
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_WORLD_NS::Offset::ToString () const
```




<hr>



### function operator!= 

```C++
inline SR_FORCE_INLINE bool SR_WORLD_NS::Offset::operator!= (
    const Offset & p_v
) const
```




<hr>



### function operator- 

```C++
inline SR_FORCE_INLINE Offset SR_WORLD_NS::Offset::operator- (
    const Offset & p_v
) const
```




<hr>



### function operator== 

```C++
inline SR_FORCE_INLINE bool SR_WORLD_NS::Offset::operator== (
    const Offset & p_v
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/Observer.h`

