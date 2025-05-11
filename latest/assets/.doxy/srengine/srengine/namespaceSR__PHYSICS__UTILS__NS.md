

# Namespace SR\_PHYSICS\_UTILS\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_PHYSICS\_UTILS\_NS**](namespaceSR__PHYSICS__UTILS__NS.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  PhysXPvdConnection \* | [**CreatePvdConnection**](#function-createpvdconnection) (physx::PxFoundation \* pFoundation, const std::string & ip, uint16\_t port, uint32\_t timeout) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED SR\_MATH\_NS::FVector3 | [**BtV33ToFV**](#function-btv33tofv) (const btVector3 & vector3) <br> |
|  physx::PxCombineMode::Enum | [**CombineToPxCombine**](#function-combinetopxcombine) (const Combine mode) <br> |
|  SR\_MAYBE\_UNUSED btVector3 | [**FV3ToBtV3**](#function-fv3tobtv3) (const SR\_MATH\_NS::FVector3 & vector3) <br> |
|  SR\_MAYBE\_UNUSED physx::PxVec3 | [**FV3ToPxV3**](#function-fv3topxv3) (const SR\_MATH\_NS::FVector3 & vector3) <br> |
|  SR\_MAYBE\_UNUSED bool | [**Is2DShape**](#function-is2dshape) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED bool | [**Is3DShape**](#function-is3dshape) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsBox**](#function-isbox) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsCapsule**](#function-iscapsule) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsConvex**](#function-isconvex) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsCylinder**](#function-iscylinder) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsPlane**](#function-isplane) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsShapeHasGeometry**](#function-isshapehasgeometry) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsShapeHasHeight**](#function-isshapehasheight) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsShapeHasRadius**](#function-isshapehasradius) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsShapeHasSize**](#function-isshapehassize) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsSphere**](#function-issphere) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED constexpr bool | [**IsTriangleMesh**](#function-istrianglemesh) (ShapeType type) <br> |
|  SR\_MAYBE\_UNUSED SR\_MATH\_NS::FVector3 | [**PxV3ToFV3**](#function-pxv3tofv3) (const physx::PxVec3 & vector3) <br> |


























## Public Functions Documentation




### function CreatePvdConnection 

```C++
PhysXPvdConnection * SR_PHYSICS_UTILS_NS::CreatePvdConnection (
    physx::PxFoundation * pFoundation,
    const std::string & ip,
    uint16_t port,
    uint32_t timeout
) 
```




<hr>
## Public Static Functions Documentation




### function BtV33ToFV 

```C++
static SR_MAYBE_UNUSED SR_MATH_NS::FVector3 SR_PHYSICS_UTILS_NS::BtV33ToFV (
    const btVector3 & vector3
) 
```




<hr>



### function CombineToPxCombine 

```C++
static physx::PxCombineMode::Enum SR_PHYSICS_UTILS_NS::CombineToPxCombine (
    const Combine mode
) 
```




<hr>



### function FV3ToBtV3 

```C++
static SR_MAYBE_UNUSED btVector3 SR_PHYSICS_UTILS_NS::FV3ToBtV3 (
    const SR_MATH_NS::FVector3 & vector3
) 
```




<hr>



### function FV3ToPxV3 

```C++
static SR_MAYBE_UNUSED physx::PxVec3 SR_PHYSICS_UTILS_NS::FV3ToPxV3 (
    const SR_MATH_NS::FVector3 & vector3
) 
```




<hr>



### function Is2DShape 

```C++
static SR_MAYBE_UNUSED bool SR_PHYSICS_UTILS_NS::Is2DShape (
    ShapeType type
) 
```




<hr>



### function Is3DShape 

```C++
static SR_MAYBE_UNUSED bool SR_PHYSICS_UTILS_NS::Is3DShape (
    ShapeType type
) 
```




<hr>



### function IsBox 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsBox (
    ShapeType type
) 
```




<hr>



### function IsCapsule 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsCapsule (
    ShapeType type
) 
```




<hr>



### function IsConvex 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsConvex (
    ShapeType type
) 
```




<hr>



### function IsCylinder 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsCylinder (
    ShapeType type
) 
```




<hr>



### function IsPlane 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsPlane (
    ShapeType type
) 
```




<hr>



### function IsShapeHasGeometry 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsShapeHasGeometry (
    ShapeType type
) 
```




<hr>



### function IsShapeHasHeight 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsShapeHasHeight (
    ShapeType type
) 
```




<hr>



### function IsShapeHasRadius 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsShapeHasRadius (
    ShapeType type
) 
```




<hr>



### function IsShapeHasSize 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsShapeHasSize (
    ShapeType type
) 
```




<hr>



### function IsSphere 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsSphere (
    ShapeType type
) 
```




<hr>



### function IsTriangleMesh 

```C++
static SR_MAYBE_UNUSED constexpr bool SR_PHYSICS_UTILS_NS::IsTriangleMesh (
    ShapeType type
) 
```




<hr>



### function PxV3ToFV3 

```C++
static SR_MAYBE_UNUSED SR_MATH_NS::FVector3 SR_PHYSICS_UTILS_NS::PxV3ToFV3 (
    const physx::PxVec3 & vector3
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/Bullet3/Bullet3PhysicsLib.h`

