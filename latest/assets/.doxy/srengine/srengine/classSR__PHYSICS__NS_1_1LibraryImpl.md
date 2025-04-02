

# Class SR\_PHYSICS\_NS::LibraryImpl



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_PHYSICS\_NS::Box2DLibraryImpl](classSR__PHYSICS__NS_1_1Box2DLibraryImpl.md),  [SR\_PHYSICS\_NS::Bullet3LibraryImpl](classSR__PHYSICS__NS_1_1Bullet3LibraryImpl.md),  [SR\_PHYSICS\_NS::PhysXLibraryImpl](classSR__PHYSICS__NS_1_1PhysXLibraryImpl.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef SR\_UTILS\_NS::Measurement | [**Space**](#typedef-space)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**ConnectPVD**](#function-connectpvd) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**CreateCollisionShapeImpl**](#function-createcollisionshapeimpl) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::PhysicsMaterialImpl**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md) \* | [**CreatePhysicsMaterial**](#function-createphysicsmaterial) () <br> |
| virtual SR\_NODISCARD [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**CreatePhysicsWorld**](#function-createphysicsworld) (Space space) <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Rigidbody2DImpl**](classSR__PTYPES__NS_1_1Rigidbody2DImpl.md) \* | [**CreateRigidbody2DImpl**](#function-createrigidbody2dimpl) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Rigidbody3DImpl**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md) \* | [**CreateRigidbody3DImpl**](#function-createrigidbody3dimpl) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Vehicle4W3D**](classSR__PTYPES__NS_1_1Vehicle4W3D.md) \* | [**CreateVehicle4W3D**](#function-createvehicle4w3d) () <br> |
| virtual SR\_NODISCARD ShapeType | [**GetDefaultShape**](#function-getdefaultshape) () const<br> |
| virtual SR\_NODISCARD bool | [**Initialize**](#function-initialize) () <br> |
| virtual SR\_NODISCARD bool | [**IsShapeSupported**](#function-isshapesupported) (ShapeType type) const<br> |
|  SR\_NODISCARD bool | [**IsVehicleSupported**](#function-isvehiclesupported) () noexcept const<br> |
|   | [**LibraryImpl**](#function-libraryimpl) () <br> |
|   | [**~LibraryImpl**](#function-libraryimpl) () override<br> |


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




### typedef Space 

```C++
using SR_PHYSICS_NS::LibraryImpl::Space =  SR_UTILS_NS::Measurement;
```




<hr>



### typedef Super 

```C++
using SR_PHYSICS_NS::LibraryImpl::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Functions Documentation




### function ConnectPVD 

```C++
inline virtual void SR_PHYSICS_NS::LibraryImpl::ConnectPVD () 
```




<hr>



### function CreateCollisionShapeImpl 

```C++
inline virtual SR_NODISCARD SR_PTYPES_NS::CollisionShapeImpl * SR_PHYSICS_NS::LibraryImpl::CreateCollisionShapeImpl () 
```




<hr>



### function CreatePhysicsMaterial 

```C++
inline virtual SR_NODISCARD SR_PTYPES_NS::PhysicsMaterialImpl * SR_PHYSICS_NS::LibraryImpl::CreatePhysicsMaterial () 
```




<hr>



### function CreatePhysicsWorld 

```C++
inline virtual SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld * SR_PHYSICS_NS::LibraryImpl::CreatePhysicsWorld (
    Space space
) 
```




<hr>



### function CreateRigidbody2DImpl 

```C++
inline virtual SR_NODISCARD SR_PTYPES_NS::Rigidbody2DImpl * SR_PHYSICS_NS::LibraryImpl::CreateRigidbody2DImpl () 
```




<hr>



### function CreateRigidbody3DImpl 

```C++
inline virtual SR_NODISCARD SR_PTYPES_NS::Rigidbody3DImpl * SR_PHYSICS_NS::LibraryImpl::CreateRigidbody3DImpl () 
```




<hr>



### function CreateVehicle4W3D 

```C++
inline virtual SR_NODISCARD SR_PTYPES_NS::Vehicle4W3D * SR_PHYSICS_NS::LibraryImpl::CreateVehicle4W3D () 
```




<hr>



### function GetDefaultShape 

```C++
inline virtual SR_NODISCARD ShapeType SR_PHYSICS_NS::LibraryImpl::GetDefaultShape () const
```




<hr>



### function Initialize 

```C++
virtual SR_NODISCARD bool SR_PHYSICS_NS::LibraryImpl::Initialize () 
```




<hr>



### function IsShapeSupported 

```C++
inline virtual SR_NODISCARD bool SR_PHYSICS_NS::LibraryImpl::IsShapeSupported (
    ShapeType type
) const
```




<hr>



### function IsVehicleSupported 

```C++
inline SR_NODISCARD bool SR_PHYSICS_NS::LibraryImpl::IsVehicleSupported () noexcept const
```




<hr>



### function LibraryImpl 

```C++
SR_PHYSICS_NS::LibraryImpl::LibraryImpl () 
```




<hr>



### function ~LibraryImpl 

```C++
SR_PHYSICS_NS::LibraryImpl::~LibraryImpl () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/LibraryImpl.h`

