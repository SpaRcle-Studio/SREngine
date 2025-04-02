

# Class SR\_PHYSICS\_NS::PhysXLibraryImpl



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**PhysXLibraryImpl**](classSR__PHYSICS__NS_1_1PhysXLibraryImpl.md)








Inherits the following classes: [SR\_PHYSICS\_NS::LibraryImpl](classSR__PHYSICS__NS_1_1LibraryImpl.md)
















## Public Types inherited from SR_PHYSICS_NS::LibraryImpl

See [SR\_PHYSICS\_NS::LibraryImpl](classSR__PHYSICS__NS_1_1LibraryImpl.md)

| Type | Name |
| ---: | :--- |
| typedef SR\_UTILS\_NS::Measurement | [**Space**](classSR__PHYSICS__NS_1_1LibraryImpl.md#typedef-space)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](classSR__PHYSICS__NS_1_1LibraryImpl.md#typedef-super)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**ConnectPVD**](#function-connectpvd) () override<br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**CreateCollisionShapeImpl**](#function-createcollisionshapeimpl) () override<br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::PhysicsMaterialImpl**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md) \* | [**CreatePhysicsMaterial**](#function-createphysicsmaterial) () override<br> |
| virtual SR\_NODISCARD [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**CreatePhysicsWorld**](#function-createphysicsworld) (Space space) override<br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Rigidbody3DImpl**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md) \* | [**CreateRigidbody3DImpl**](#function-createrigidbody3dimpl) () override<br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Vehicle4W3D**](classSR__PTYPES__NS_1_1Vehicle4W3D.md) \* | [**CreateVehicle4W3D**](#function-createvehicle4w3d) () override<br> |
| virtual SR\_NODISCARD ShapeType | [**GetDefaultShape**](#function-getdefaultshape) () override const<br> |
|  SR\_NODISCARD physx::PxPhysics \* | [**GetPxPhysics**](#function-getpxphysics) () const<br> |
| virtual SR\_NODISCARD bool | [**Initialize**](#function-initialize) () override<br> |
| virtual SR\_NODISCARD bool | [**IsShapeSupported**](#function-isshapesupported) (ShapeType type) override const<br> |
|   | [**PhysXLibraryImpl**](#function-physxlibraryimpl) () = default<br> |
|   | [**~PhysXLibraryImpl**](#function-physxlibraryimpl) () override<br> |


## Public Functions inherited from SR_PHYSICS_NS::LibraryImpl

See [SR\_PHYSICS\_NS::LibraryImpl](classSR__PHYSICS__NS_1_1LibraryImpl.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**ConnectPVD**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-connectpvd) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**CreateCollisionShapeImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createcollisionshapeimpl) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::PhysicsMaterialImpl**](classSR__PTYPES__NS_1_1PhysicsMaterialImpl.md) \* | [**CreatePhysicsMaterial**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createphysicsmaterial) () <br> |
| virtual SR\_NODISCARD [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**CreatePhysicsWorld**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createphysicsworld) (Space space) <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Rigidbody2DImpl**](classSR__PTYPES__NS_1_1Rigidbody2DImpl.md) \* | [**CreateRigidbody2DImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createrigidbody2dimpl) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Rigidbody3DImpl**](classSR__PTYPES__NS_1_1Rigidbody3DImpl.md) \* | [**CreateRigidbody3DImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createrigidbody3dimpl) () <br> |
| virtual SR\_NODISCARD [**SR\_PTYPES\_NS::Vehicle4W3D**](classSR__PTYPES__NS_1_1Vehicle4W3D.md) \* | [**CreateVehicle4W3D**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createvehicle4w3d) () <br> |
| virtual SR\_NODISCARD ShapeType | [**GetDefaultShape**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-getdefaultshape) () const<br> |
| virtual SR\_NODISCARD bool | [**Initialize**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-initialize) () <br> |
| virtual SR\_NODISCARD bool | [**IsShapeSupported**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-isshapesupported) (ShapeType type) const<br> |
|  SR\_NODISCARD bool | [**IsVehicleSupported**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-isvehiclesupported) () noexcept const<br> |
|   | [**LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-libraryimpl) () <br> |
|   | [**~LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-libraryimpl) () override<br> |


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








## Public Functions Documentation




### function ConnectPVD 

```C++
virtual void SR_PHYSICS_NS::PhysXLibraryImpl::ConnectPVD () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::ConnectPVD*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-connectpvd)


<hr>



### function CreateCollisionShapeImpl 

```C++
virtual SR_NODISCARD SR_PTYPES_NS::CollisionShapeImpl * SR_PHYSICS_NS::PhysXLibraryImpl::CreateCollisionShapeImpl () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::CreateCollisionShapeImpl*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createcollisionshapeimpl)


<hr>



### function CreatePhysicsMaterial 

```C++
virtual SR_NODISCARD SR_PTYPES_NS::PhysicsMaterialImpl * SR_PHYSICS_NS::PhysXLibraryImpl::CreatePhysicsMaterial () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::CreatePhysicsMaterial*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createphysicsmaterial)


<hr>



### function CreatePhysicsWorld 

```C++
virtual SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld * SR_PHYSICS_NS::PhysXLibraryImpl::CreatePhysicsWorld (
    Space space
) override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::CreatePhysicsWorld*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createphysicsworld)


<hr>



### function CreateRigidbody3DImpl 

```C++
virtual SR_NODISCARD SR_PTYPES_NS::Rigidbody3DImpl * SR_PHYSICS_NS::PhysXLibraryImpl::CreateRigidbody3DImpl () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::CreateRigidbody3DImpl*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createrigidbody3dimpl)


<hr>



### function CreateVehicle4W3D 

```C++
virtual SR_NODISCARD SR_PTYPES_NS::Vehicle4W3D * SR_PHYSICS_NS::PhysXLibraryImpl::CreateVehicle4W3D () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::CreateVehicle4W3D*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createvehicle4w3d)


<hr>



### function GetDefaultShape 

```C++
inline virtual SR_NODISCARD ShapeType SR_PHYSICS_NS::PhysXLibraryImpl::GetDefaultShape () override const
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::GetDefaultShape*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-getdefaultshape)


<hr>



### function GetPxPhysics 

```C++
inline SR_NODISCARD physx::PxPhysics * SR_PHYSICS_NS::PhysXLibraryImpl::GetPxPhysics () const
```




<hr>



### function Initialize 

```C++
virtual SR_NODISCARD bool SR_PHYSICS_NS::PhysXLibraryImpl::Initialize () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::Initialize*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-initialize)


<hr>



### function IsShapeSupported 

```C++
virtual SR_NODISCARD bool SR_PHYSICS_NS::PhysXLibraryImpl::IsShapeSupported (
    ShapeType type
) override const
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::IsShapeSupported*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-isshapesupported)


<hr>



### function PhysXLibraryImpl 

```C++
SR_PHYSICS_NS::PhysXLibraryImpl::PhysXLibraryImpl () = default
```




<hr>



### function ~PhysXLibraryImpl 

```C++
SR_PHYSICS_NS::PhysXLibraryImpl::~PhysXLibraryImpl () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/PhysX/PhysXLibraryImpl.h`

