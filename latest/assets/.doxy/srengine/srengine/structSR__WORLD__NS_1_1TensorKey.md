

# Struct SR\_WORLD\_NS::TensorKey



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**TensorKey**](structSR__WORLD__NS_1_1TensorKey.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::IVector3 | [**chunk**](#variable-chunk)  <br> |
|  SR\_MATH\_NS::IVector3 | [**region**](#variable-region)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TensorKey**](#function-tensorkey-12) () = default<br> |
|   | [**TensorKey**](#function-tensorkey-22) (const SR\_MATH\_NS::IVector3 & \_region, const SR\_MATH\_NS::IVector3 & \_chunk) <br> |
|  bool | [**operator==**](#function-operator) (const [**TensorKey**](structSR__WORLD__NS_1_1TensorKey.md) & other) noexcept const<br> |




























## Public Attributes Documentation




### variable chunk 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::TensorKey::chunk;
```




<hr>



### variable region 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::TensorKey::region;
```




<hr>
## Public Functions Documentation




### function TensorKey [1/2]

```C++
SR_WORLD_NS::TensorKey::TensorKey () = default
```




<hr>



### function TensorKey [2/2]

```C++
inline SR_WORLD_NS::TensorKey::TensorKey (
    const SR_MATH_NS::IVector3 & _region,
    const SR_MATH_NS::IVector3 & _chunk
) 
```




<hr>



### function operator== 

```C++
inline bool SR_WORLD_NS::TensorKey::operator== (
    const TensorKey & other
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/TensorKey.h`

