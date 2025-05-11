

# Class SR\_PHYSICS\_NS::Bullet3LibraryImpl



[**ClassList**](annotated.md) **>** [**SR\_PHYSICS\_NS**](namespaceSR__PHYSICS__NS.md) **>** [**Bullet3LibraryImpl**](classSR__PHYSICS__NS_1_1Bullet3LibraryImpl.md)








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
|   | [**Bullet3LibraryImpl**](#function-bullet3libraryimpl) () = default<br> |
|  SR\_NODISCARD [**SR\_PTYPES\_NS::CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) \* | [**CreateCollisionShape**](#function-createcollisionshape) () override<br> |
| virtual SR\_NODISCARD [**SR\_PHYSICS\_NS::PhysicsWorld**](classSR__PHYSICS__NS_1_1PhysicsWorld.md) \* | [**CreatePhysicsWorld**](#function-createphysicsworld) (Space space) override<br> |
|  SR\_NODISCARD [**SR\_PTYPES\_NS::Rigidbody3D**](classSR__PTYPES__NS_1_1Rigidbody3D.md) \* | [**CreateRigidbody3D**](#function-createrigidbody3d) () override<br> |
| virtual SR\_NODISCARD ShapeType | [**GetDefaultShape**](#function-getdefaultshape) () override const<br> |
| virtual SR\_NODISCARD bool | [**Initialize**](#function-initialize) () override<br> |
| virtual SR\_NODISCARD bool | [**IsShapeSupported**](#function-isshapesupported) (ShapeType type) override const<br> |
|   | [**~Bullet3LibraryImpl**](#function-bullet3libraryimpl) () override<br> |


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
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function Bullet3LibraryImpl 

```C++
SR_PHYSICS_NS::Bullet3LibraryImpl::Bullet3LibraryImpl () = default
```




<hr>



### function CreateCollisionShape 

```C++
SR_NODISCARD SR_PTYPES_NS::CollisionShape * SR_PHYSICS_NS::Bullet3LibraryImpl::CreateCollisionShape () override
```




<hr>



### function CreatePhysicsWorld 

```C++
virtual SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld * SR_PHYSICS_NS::Bullet3LibraryImpl::CreatePhysicsWorld (
    Space space
) override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::CreatePhysicsWorld*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-createphysicsworld)


<hr>



### function CreateRigidbody3D 

```C++
SR_NODISCARD SR_PTYPES_NS::Rigidbody3D * SR_PHYSICS_NS::Bullet3LibraryImpl::CreateRigidbody3D () override
```




<hr>



### function GetDefaultShape 

```C++
inline virtual SR_NODISCARD ShapeType SR_PHYSICS_NS::Bullet3LibraryImpl::GetDefaultShape () override const
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::GetDefaultShape*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-getdefaultshape)


<hr>



### function Initialize 

```C++
inline virtual SR_NODISCARD bool SR_PHYSICS_NS::Bullet3LibraryImpl::Initialize () override
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::Initialize*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-initialize)


<hr>



### function IsShapeSupported 

```C++
virtual SR_NODISCARD bool SR_PHYSICS_NS::Bullet3LibraryImpl::IsShapeSupported (
    ShapeType type
) override const
```



Implements [*SR\_PHYSICS\_NS::LibraryImpl::IsShapeSupported*](classSR__PHYSICS__NS_1_1LibraryImpl.md#function-isshapesupported)


<hr>



### function ~Bullet3LibraryImpl 

```C++
SR_PHYSICS_NS::Bullet3LibraryImpl::~Bullet3LibraryImpl () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/Bullet3/Bullet3LibraryImpl.h`

